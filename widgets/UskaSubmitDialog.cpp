#include "UskaSubmitDialog.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QDialogButtonBox>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QHttpMultiPart>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QRegularExpression>
#include <QTextBrowser>
#include <QTextDocumentFragment>
#include <QUrl>
#include <QVBoxLayout>

#include "pimpl_impl.hpp"

namespace
{
  // The portal is a plain PHP form (contestlog.uska.ch, by HB9DQM):
  //   GET  submit          step 1, lists the open contests
  //   POST submit?step=2   contest + log file; parses and checks the log
  //   POST submit?step=3   callsign, email, category
  //   POST submit?step=4   declaration=1; stores the log, mails a
  //                        confirmation and redirects to soapbox?submitted=1
  // Only step 4 stores anything. The parsing below follows the markup of
  // its step*.inc.php templates.

  // the portal's own wording (step3.inc.php)
  char const * const declaration =
    "I declare that I have adhered strictly to the contest rules and "
    "regulations as well as the provisions of my license.";

  struct Response
  {
    int status {0};
    QString location;
    QString body;
    QString error;              // set when no HTTP response arrived
  };

  struct Option
  {
    QString value;
    QString text;
    bool selected;
  };

  QString plain (QString const& html)
  {
    return QTextDocumentFragment::fromHtml (html).toPlainText ().simplified ();
  }

  // the step heading, e.g. "Step 2: Check and Correct Information"; the
  // page header carries another title ("Contest Log Submission") first
  QString page_title (QString const& html)
  {
    auto it = QRegularExpression {R"(<h1 class="title">([^<]*)</h1>)"}.globalMatch (html);
    while (it.hasNext ())
      {
        auto const& title = plain (it.next ().captured (1));
        if (title.startsWith ("Step")) return title;
      }
    return {};
  }

  // the list items of a message box, kind e.g. "is-danger" or "is-warning"
  QStringList messages (QString const& html, QString const& kind)
  {
    QStringList result;
    QRegularExpression box {"<article class=\"message " + kind + "\">(.*?)</article>"
        , QRegularExpression::DotMatchesEverythingOption};
    auto const& m = box.match (html);
    if (!m.hasMatch ()) return result;
    QRegularExpression item {"<li>(.*?)</li>", QRegularExpression::DotMatchesEverythingOption};
    auto it = item.globalMatch (m.captured (1));
    while (it.hasNext ()) result << plain (it.next ().captured (1));
    return result;
  }

  QList<Option> select_options (QString const& html, QString const& id)
  {
    QList<Option> result;
    QRegularExpression select {"<select id=\"" + id + "\"[^>]*>(.*?)</select>"
        , QRegularExpression::DotMatchesEverythingOption};
    auto const& m = select.match (html);
    if (!m.hasMatch ()) return result;
    QRegularExpression option {R"re(<option value="([^"]*)"( selected)?>([^<]*)</option>)re"};
    auto it = option.globalMatch (m.captured (1));
    while (it.hasNext ())
      {
        auto const& o = it.next ();
        if (o.captured (1).isEmpty ()) continue; // "(choose one)"
        result << Option {plain (o.captured (1)), plain (o.captured (3)), !o.captured (2).isEmpty ()};
      }
    return result;
  }

  QByteArray form_field (QString const& name, QString const& value)
  {
    return name.toUtf8 () + '=' + QUrl::toPercentEncoding (value);
  }
}

class UskaSubmitDialog::impl final
{
  Q_DECLARE_TR_FUNCTIONS (UskaSubmitDialog)

public:
  impl (UskaSubmitDialog * self, QString const& portal_url, QString const& file
        , QString const& callsign, QString const& email, QDate const& qso_date, int qso_count);

  void load_contests ();
  void submit ();
  void update_buttons ();

  QNetworkRequest request (QString const& step) const;
  Response wait (QNetworkReply *);
  void report (QString const& html);
  bool fail (QString const& what, Response const& = {});

  UskaSubmitDialog * self_;
  QString portal_url_;
  QString file_;
  QString callsign_;
  QDate qso_date_;
  QNetworkAccessManager network_;
  QComboBox contest_;
  QLineEdit email_;
  QCheckBox declared_;
  QTextBrowser status_;
  QPushButton * submit_button_;
  QPushButton * browser_button_;
  bool busy_ {false};
  bool submitted_ {false};
};

UskaSubmitDialog::impl::impl (UskaSubmitDialog * self, QString const& portal_url, QString const& file
                              , QString const& callsign, QString const& email
                              , QDate const& qso_date, int qso_count)
  : self_ {self}
  , portal_url_ {portal_url}
  , file_ {file}
  , callsign_ {callsign}
  , qso_date_ {qso_date}
{
  self_->setWindowTitle (tr ("Submit log to USKA"));
  self_->resize (640, 520);
  auto layout = new QVBoxLayout {self_};

  auto form = new QFormLayout;
  form->addRow (tr ("Log file:"), new QLabel {QDir::toNativeSeparators (file_)});
  form->addRow (tr ("Callsign:"), new QLabel {callsign_});
  form->addRow (tr ("QSOs:"), new QLabel {QString::number (qso_count)});
  form->addRow (tr ("Contest:"), &contest_);
  email_.setText (email);
  email_.setPlaceholderText ("you@example.com");
  form->addRow (tr ("Email for the confirmation:"), &email_);
  layout->addLayout (form);

  auto declaration_text = new QLabel {QString::fromUtf8 (declaration)};
  declaration_text->setWordWrap (true);
  layout->addWidget (declaration_text);
  declared_.setText (tr ("I make this declaration"));
  layout->addWidget (&declared_);

  layout->addWidget (&status_, 1);

  auto buttons = new QDialogButtonBox;
  submit_button_ = buttons->addButton (tr ("Submit log"), QDialogButtonBox::AcceptRole);
  browser_button_ = buttons->addButton (tr ("Use the web page instead"), QDialogButtonBox::ActionRole);
  buttons->addButton (QDialogButtonBox::Close);
  layout->addWidget (buttons);

  QObject::connect (&contest_, QOverload<int>::of (&QComboBox::currentIndexChanged), [this] {update_buttons ();});
  QObject::connect (&email_, &QLineEdit::textChanged, [this] {update_buttons ();});
  QObject::connect (&declared_, &QCheckBox::toggled, [this] {update_buttons ();});
  QObject::connect (submit_button_, &QPushButton::clicked, [this] {submit ();});
  QObject::connect (browser_button_, &QPushButton::clicked, [this] {
      QDesktopServices::openUrl (QUrl {portal_url_});
    });
  QObject::connect (buttons, &QDialogButtonBox::rejected, self_, &QDialog::reject);
  update_buttons ();
}

void UskaSubmitDialog::impl::update_buttons ()
{
  submit_button_->setEnabled (!busy_ && !submitted_ && contest_.currentIndex () >= 0
                              && email_.text ().contains ('@') && declared_.isChecked ());
  contest_.setEnabled (!busy_ && !submitted_);
  email_.setEnabled (!busy_ && !submitted_);
  declared_.setEnabled (!busy_ && !submitted_);
}

QNetworkRequest UskaSubmitDialog::impl::request (QString const& step) const
{
  QUrl url {portal_url_};
  if (step.size ()) url.setQuery ("step=" + step);
  QNetworkRequest request {url};
  // step 4 answers with a redirect, which is the success signal
  request.setAttribute (QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::ManualRedirectPolicy);
  request.setHeader (QNetworkRequest::UserAgentHeader
                     , "WSJT-SWISS3/" + QCoreApplication::applicationVersion ());
#if QT_VERSION >= QT_VERSION_CHECK (5, 15, 0)
  request.setTransferTimeout (30000);
#endif
  return request;
}

Response UskaSubmitDialog::impl::wait (QNetworkReply * reply)
{
  QEventLoop loop;
  QObject::connect (reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec ();
  Response r;
  r.status = reply->attribute (QNetworkRequest::HttpStatusCodeAttribute).toInt ();
  // raw header: the portal redirects relatively ("soapbox?submitted=1"),
  // which QNetworkRequest::LocationHeader drops for lack of a scheme
  r.location = QString::fromUtf8 (reply->rawHeader ("Location"));
  r.body = QString::fromUtf8 (reply->readAll ());
  if (!r.status) r.error = reply->errorString ();
  reply->deleteLater ();
  return r;
}

void UskaSubmitDialog::impl::report (QString const& html)
{
  status_.append (html);
}

bool UskaSubmitDialog::impl::fail (QString const& what, Response const& r)
{
  auto detail = r.error;
  if (detail.isEmpty () && r.status) detail = tr ("HTTP status %1").arg (r.status);
  report ("<p style=\"color:#b00020\"><b>" + what.toHtmlEscaped () + "</b>"
          + (detail.isEmpty () ? QString {} : "<br />" + detail.toHtmlEscaped ())
          + "</p><p>" + tr ("Nothing was submitted. You can try again, or use the web page.").toHtmlEscaped ()
          + "</p>");
  busy_ = false;
  update_buttons ();
  return false;
}

void UskaSubmitDialog::impl::load_contests ()
{
  busy_ = true;
  update_buttons ();
  report (tr ("Fetching the open contests from %1 ...").arg (portal_url_).toHtmlEscaped ());
  auto const& r = wait (network_.get (request ({})));
  busy_ = false;
  if (200 != r.status)
    {
      fail (tr ("The USKA log portal could not be reached."), r);
      return;
    }
  auto const& contests = select_options (r.body, "contest");
  if (contests.isEmpty ())
    {
      report (tr ("The portal has no open contest at the moment. Each contest opens for "
                  "submissions after it has taken place.").toHtmlEscaped ());
      update_buttons ();
      return;
    }
  for (auto const& c : contests) contest_.addItem (c.text, c.value);

  // The digital part runs on the first and second Saturday of December,
  // listed as "Christmas Contest Digital 1 <year>" and "... Digital 2 <year>".
  contest_.setCurrentIndex (-1);
  if (qso_date_.isValid () && 12 == qso_date_.month () && qso_date_.day () <= 14)
    {
      contest_.setCurrentIndex (contest_.findText (QString {"Christmas Contest Digital %1 %2"}
                                                   .arg (qso_date_.day () <= 7 ? 1 : 2)
                                                   .arg (qso_date_.year ())));
    }
  report ((contest_.currentIndex () >= 0
           ? tr ("Contest preselected from the QSO date; check it.")
           : tr ("Choose the contest of this log.")).toHtmlEscaped ());
  update_buttons ();
}

void UskaSubmitDialog::impl::submit ()
{
  busy_ = true;
  update_buttons ();
  auto const& contest = contest_.currentData ().toString ();

  // step 2: upload the log for the portal's check
  QFile f {file_};
  if (!f.open (QIODevice::ReadOnly))
    {
      fail (tr ("Cannot read %1: %2").arg (QDir::toNativeSeparators (file_), f.errorString ()));
      return;
    }
  auto multi = new QHttpMultiPart {QHttpMultiPart::FormDataType};
  QHttpPart contest_part;
  contest_part.setHeader (QNetworkRequest::ContentDispositionHeader, "form-data; name=\"contest\"");
  contest_part.setBody (contest.toUtf8 ());
  multi->append (contest_part);
  QHttpPart log_part;
  log_part.setHeader (QNetworkRequest::ContentDispositionHeader
                      , "form-data; name=\"log\"; filename=\"" + QFileInfo {file_}.fileName () + "\"");
  log_part.setHeader (QNetworkRequest::ContentTypeHeader, "application/octet-stream");
  log_part.setBody (f.readAll ());
  multi->append (log_part);
  report (tr ("Uploading the log for checking ...").toHtmlEscaped ());
  auto reply = network_.post (request ("2"), multi);
  multi->setParent (reply);
  auto r = wait (reply);
  if (200 != r.status) return (void)fail (tr ("The log could not be uploaded."), r);
  if (page_title (r.body).startsWith ("Step 1"))
    {
      auto const& errors = messages (r.body, "is-danger");
      report ("<p style=\"color:#b00020\"><b>" + tr ("The portal rejected the log:").toHtmlEscaped ()
              + "</b><br />" + errors.join ("<br />").toHtmlEscaped () + "</p>");
      return (void)fail (tr ("Please correct the log and export it again."));
    }
  if (!page_title (r.body).startsWith ("Step 2"))
    {
      return (void)fail (tr ("Unexpected answer from the portal (%1).").arg (page_title (r.body)), r);
    }

  auto const& warnings = messages (r.body, "is-warning");
  if (warnings.size ())
    {
      report ("<p><b>" + tr ("The portal found these issues:").toHtmlEscaped () + "</b><br />"
              + warnings.join ("<br />").toHtmlEscaped () + "</p>");
      if (QMessageBox::Yes != QMessageBox::question (self_, tr ("Submit log to USKA")
                                                     , tr ("The portal found %1 issue(s) in the log, "
                                                           "listed in the window. Invalid QSOs may "
                                                           "reduce the score.\n\nSubmit the log anyway?")
                                                     .arg (warnings.size ())))
        {
          return (void)fail (tr ("Submission cancelled."));
        }
    }

  QString category;
  auto const& categories = select_options (r.body, "category");
  for (auto const& c : categories) if (c.selected) category = c.value;
  if (category.isEmpty ())
    {
      for (auto const& c : categories) if ("SOAB-Digital-HP" == c.value) category = c.value;
    }
  if (category.isEmpty ())
    {
      return (void)fail (tr ("The portal suggests no category for this log; please submit it on the web page."));
    }

  // step 3: callsign, email and category
  auto form = request ("3");
  form.setHeader (QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  r = wait (network_.post (form, form_field ("category", category) + '&'
                           + form_field ("callsign", callsign_) + '&'
                           + form_field ("email", email_.text ().trimmed ())));
  if (200 != r.status) return (void)fail (tr ("The portal did not accept the details."), r);
  if (!page_title (r.body).startsWith ("Step 3"))
    {
      auto const& errors = messages (r.body, "is-danger");
      return (void)fail (errors.size () ? errors.join ("; ")
                         : tr ("Unexpected answer from the portal (%1).").arg (page_title (r.body)));
    }

  // step 4: the operator's declaration; the portal stores the log
  report (tr ("Submitting the log ...").toHtmlEscaped ());
  form = request ("4");
  form.setHeader (QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  r = wait (network_.post (form, form_field ("declaration", "1")));
  if (!(302 == r.status || 303 == r.status) || !r.location.contains ("submitted=1"))
    {
      return (void)fail (tr ("The portal did not confirm the submission."), r);
    }

  submitted_ = true;
  busy_ = false;
  update_buttons ();
  auto const& done = tr ("USKA has received your log for \"%1\" (category %2).\n\n"
                         "A confirmation with the log attached is sent to %3; it is the "
                         "official receipt. If it does not arrive, check your spam folder.")
    .arg (contest_.currentText (), category, email_.text ().trimmed ());
  report ("<p style=\"color:#006400\"><b>" + done.toHtmlEscaped ().replace ("\n", "<br />") + "</b></p>");
  QMessageBox::information (self_, tr ("Submit log to USKA"), done);
}

UskaSubmitDialog::UskaSubmitDialog (QString const& portal_url, QString const& cabrillo_file
                                    , QString const& callsign, QString const& email
                                    , QDate const& qso_date, int qso_count, QWidget * parent)
  : QDialog {parent}
  , m_ {this, portal_url, cabrillo_file, callsign, email, qso_date, qso_count}
{
  // fetch the contest list once the window is up
  QMetaObject::invokeMethod (this, [this] {m_->load_contests ();}, Qt::QueuedConnection);
}

UskaSubmitDialog::~UskaSubmitDialog ()
{
}

QString UskaSubmitDialog::email () const
{
  return m_->email_.text ().trimmed ();
}
