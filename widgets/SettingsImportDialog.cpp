#include "SettingsImportDialog.hpp"

#include <algorithm>

#include <QCoreApplication>
#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHeaderView>
#include <QLabel>
#include <QList>
#include <QLocale>
#include <QMessageBox>
#include <QMetaEnum>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QSplitter>
#include <QStringList>
#include <QTextBrowser>
#include <QTreeWidget>
#include <QVBoxLayout>

#include "Transceiver/TransceiverFactory.hpp"

namespace
{
  // A settings file of WSJT-X or WSJT-SWISS found on this PC.
  struct FoundSettings
  {
    QString path;
    QString program;
    QString profile;
    QDateTime last_used;
    QString callsign;
    QString grid;
    QString radio;
    QString ptt;
    QString sound_in;
    QString sound_out;
    QString mode;
    QString frequency;
    QStringList configurations;
    QString current_configuration;
  };

  class SettingsImport
  {
    Q_DECLARE_TR_FUNCTIONS (SettingsImport)

  public:
    static QString describe_radio (QSettings const& s)
    {
      auto rig = s.value ("Configuration/Rig").toString ();
      if (rig.isEmpty () || rig == "None") return tr ("No radio control");
      auto port = s.value ("Configuration/CATNetworkPort").toString ();
      if (port.isEmpty ()) port = s.value ("Configuration/CATUSBPort").toString ();
      if (port.isEmpty ()) port = s.value ("Configuration/CATSerialPort").toString ();
      return port.isEmpty () ? rig : tr ("%1 via %2").arg (rig, port);
    }

    static QString describe_ptt (QSettings const& s)
    {
      auto method = s.value ("Configuration/PTTMethod")
        .value<TransceiverFactory::PTTMethod> ();
      auto port = s.value ("Configuration/PTTport").toString ();
      switch (method)
        {
        case TransceiverFactory::PTT_method_CAT: return tr ("CAT");
        case TransceiverFactory::PTT_method_DTR: return tr ("DTR on %1").arg (port);
        case TransceiverFactory::PTT_method_RTS: return tr ("RTS on %1").arg (port);
        default: return tr ("VOX");
        }
    }

    static FoundSettings read (QFileInfo const& ini, QString const& folder)
    {
      // Read only: no value is ever set, so QSettings never writes.
      QSettings s {ini.absoluteFilePath (), QSettings::IniFormat};
      FoundSettings f;
      f.path = QDir::toNativeSeparators (ini.absoluteFilePath ());
      auto parts = folder.split (" - ");
      f.program = parts.takeFirst ();
      if (f.program == "WSJT-SWISS") f.program = tr ("WSJT-SWISS (version 2)");
      else if (f.program == "WSJT-SWISS3") f.program = "WSJT-SWISS 3";
      f.profile = parts.join (" - ");
      f.last_used = ini.lastModified ();
      f.callsign = s.value ("Configuration/MyCall").toString ();
      f.grid = s.value ("Configuration/MyGrid").toString ();
      f.radio = describe_radio (s);
      f.ptt = describe_ptt (s);
      f.sound_in = s.value ("Configuration/SoundInName").toString ();
      f.sound_out = s.value ("Configuration/SoundOutName").toString ();
      f.mode = s.value ("Common/Mode").toString ();
      auto dial = s.value ("Common/DialFreq").toLongLong ();
      if (dial > 0) f.frequency = QString::number (dial / 1e6, 'f', 3) + " MHz";
      s.beginGroup ("MultiSettings");
      f.current_configuration = s.value ("CurrentName").toString ();
      f.configurations = s.childGroups ();
      s.endGroup ();
      if (!f.current_configuration.isEmpty ()
          && !f.configurations.contains (f.current_configuration))
        {
          f.configurations.prepend (f.current_configuration);
        }
      return f;
    }

    // Settings folders of the WSJT-X family beside our own, e.g.
    // "WSJT-X", "WSJT-X - IC7300", "WSJT-SWISS".
    static QList<FoundSettings> search (QString const& target_ini)
    {
      QFileInfo target {target_ini};
      QDir local {target.absolutePath ()};
      local.cdUp ();
      QRegularExpression family {R"(^(WSJT-X|WSJT-SWISS\d*)( - .+)?$)"};
      QList<FoundSettings> found;
      for (auto const& folder : local.entryList (QDir::Dirs | QDir::NoDotAndDotDot))
        {
          if (!family.match (folder).hasMatch ()) continue;
          QFileInfo ini {local.absoluteFilePath (folder + '/' + folder + ".ini")};
          if (!ini.isFile () || ini.absoluteFilePath () == target.absoluteFilePath ()) continue;
          found << read (ini, folder);
        }
      std::sort (found.begin (), found.end (), [] (FoundSettings const& a, FoundSettings const& b) {
          return a.last_used > b.last_used;
        });
      return found;
    }

    static QString details (FoundSettings const& f)
    {
      auto row = [] (QString const& label, QString const& value) {
        return "<tr><td><b>" + label.toHtmlEscaped () + "</b>&nbsp;&nbsp;</td><td>"
          + (value.isEmpty () ? "&ndash;" : value.toHtmlEscaped ()) + "</td></tr>";
      };
      QStringList configurations;
      for (auto const& name : f.configurations)
        {
          configurations << (name == f.current_configuration ? tr ("%1 (in use)").arg (name) : name);
        }
      return "<table>"
        + row (tr ("Program"), f.profile.isEmpty () ? f.program : tr ("%1, profile \"%2\"").arg (f.program, f.profile))
        + row (tr ("Settings file"), f.path)
        + row (tr ("Last used"), QLocale {}.toString (f.last_used, QLocale::ShortFormat))
        + row (tr ("Callsign"), f.callsign)
        + row (tr ("Locator"), f.grid)
        + row (tr ("Radio"), f.radio)
        + row (tr ("PTT"), f.ptt)
        + row (tr ("Sound card in"), f.sound_in)
        + row (tr ("Sound card out"), f.sound_out)
        + row (tr ("Last mode"), f.mode)
        + row (tr ("Last frequency"), f.frequency)
        + row (tr ("Configurations"), configurations.join (", "))
        + "</table>";
    }

    static bool ask_to_search ()
    {
      QMessageBox box {QMessageBox::Question, tr ("WSJT-SWISS 3 - first start"),
          tr ("WSJT-SWISS 3 has no settings yet.\n\n"
              "Should it search this PC for the settings of WSJT-X or an "
              "earlier WSJT-SWISS? You can then take over your callsign, "
              "radio and sound card setup.\n\n"
              "Nothing is copied without your confirmation, and the settings "
              "of the other programs are not changed.")};
      auto search_button = box.addButton (tr ("Search"), QMessageBox::AcceptRole);
      box.addButton (tr ("Start with empty settings"), QMessageBox::RejectRole);
      box.setDefaultButton (search_button);
      box.exec ();
      return box.clickedButton () == search_button;
    }

    // Returns the chosen settings, or nullptr to start empty.
    static FoundSettings const * choose (QList<FoundSettings> const& found)
    {
      QDialog dialog;
      dialog.setWindowTitle (tr ("WSJT-SWISS 3 - import settings"));
      dialog.resize (900, 560);
      auto layout = new QVBoxLayout {&dialog};
      auto intro = new QLabel {tr ("These settings were found on this PC. Select the one you "
                                   "use for your station and check its details below, then "
                                   "click \"Import selected\". It is copied for WSJT-SWISS 3; "
                                   "the original stays unchanged.")};
      intro->setWordWrap (true);
      layout->addWidget (intro);

      auto splitter = new QSplitter {Qt::Vertical};
      auto list = new QTreeWidget;
      list->setRootIsDecorated (false);
      list->setHeaderLabels ({tr ("Program / profile"), tr ("Callsign"), tr ("Radio"), tr ("Last used")});
      for (auto const& f : found)
        {
          auto name = f.profile.isEmpty () ? f.program : f.program + " - " + f.profile;
          new QTreeWidgetItem {list, {name, f.callsign, f.radio,
                QLocale {}.toString (f.last_used, QLocale::ShortFormat)}};
        }
      list->header ()->setSectionResizeMode (QHeaderView::ResizeToContents);
      auto details_view = new QTextBrowser;
      details_view->setPlaceholderText (tr ("Select an entry above to see its details."));
      splitter->addWidget (list);
      splitter->addWidget (details_view);
      layout->addWidget (splitter, 1);

      auto buttons = new QDialogButtonBox;
      auto import_button = buttons->addButton (tr ("Import selected"), QDialogButtonBox::AcceptRole);
      buttons->addButton (tr ("Start with empty settings"), QDialogButtonBox::RejectRole);
      import_button->setEnabled (false); // no preselection: the operator chooses
      layout->addWidget (buttons);

      // Follow the selection, not the current item: a view may make its
      // first row current on focus, which must not count as a choice.
      auto selected_row = [list] {
        auto items = list->selectedItems ();
        return items.isEmpty () ? -1 : list->indexOfTopLevelItem (items.first ());
      };
      QObject::connect (list, &QTreeWidget::itemSelectionChanged, [&] {
          auto row = selected_row ();
          import_button->setEnabled (row >= 0);
          details_view->setHtml (row >= 0 ? details (found[row]) : QString {});
        });
      QObject::connect (buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
      QObject::connect (buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

      if (QDialog::Accepted != dialog.exec ()) return nullptr;
      auto row = selected_row ();
      return row >= 0 ? &found[row] : nullptr;
    }

    static void run (QString const& target_ini)
    {
      if (QFileInfo::exists (target_ini) || !ask_to_search ()) return;

      auto found = search (target_ini);
      if (found.isEmpty ())
        {
          QMessageBox::information (nullptr, tr ("WSJT-SWISS 3 - import settings"),
                                    tr ("No settings of WSJT-X or WSJT-SWISS were found on this PC.\n"
                                        "WSJT-SWISS 3 starts with empty settings."));
          return;
        }

      auto chosen = choose (found);
      if (!chosen) return;

      QDir {}.mkpath (QFileInfo {target_ini}.absolutePath ());
      if (QFile::copy (chosen->path, target_ini))
        {
          QFile {target_ini}.setPermissions (QFile::ReadOwner | QFile::WriteOwner);
          QMessageBox::information (nullptr, tr ("WSJT-SWISS 3 - import settings"),
                                    tr ("The settings were imported from\n%1\n\n"
                                        "Before transmitting, check File > Settings, "
                                        "tabs Radio and Audio.").arg (chosen->path));
        }
      else
        {
          QMessageBox::warning (nullptr, tr ("WSJT-SWISS 3 - import settings"),
                                tr ("The settings could not be copied from\n%1\n\n"
                                    "WSJT-SWISS 3 starts with empty settings.").arg (chosen->path));
        }
    }
  };
}

void offer_settings_import (QString const& target_ini)
{
  SettingsImport::run (target_ini);
}
