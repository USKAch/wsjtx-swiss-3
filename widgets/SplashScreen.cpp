#include "SplashScreen.hpp"

#include <QPixmap>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QCoreApplication>

#include "revision_utils.hpp"
#include "pimpl_impl.hpp"

#include "moc_SplashScreen.cpp"

class SplashScreen::impl
{
public:
  impl ()
    : checkbox_ {"Do not show this again"}
  {
    main_layout_.addStretch ();
    main_layout_.addWidget (&checkbox_, 0, Qt::AlignRight);
    // keep the check box above the 34 pixel canton strip at the bottom
    // of artwork/splash.png (see artwork/swiss/make_swiss_graphics.py)
    main_layout_.setContentsMargins (11, 11, 11, 34 + 8);
  }

  QVBoxLayout main_layout_;
  QCheckBox checkbox_;
};

SplashScreen::SplashScreen ()
  : QSplashScreen {QPixmap {":/splash.png"}, Qt::WindowStaysOnTopHint}
{
  setLayout (&m_->main_layout_);
  showMessage ("<h2>" + QString {"WSJT-SWISS 3 v" +
        QCoreApplication::applicationVersion() + " " +
        revision ()}.simplified () + "</h2>"
    "Swiss XMAS Contest edition of WSJT-X by K1JT et al.<br />"
    "Swiss adaptation by HB9BLA<br /><br />"
    "Send WSJT-SWISS issue reports to<br />"
    "https://github.com/USKAch/wsjtx-swiss-3/issues<br /><br />"
    "<img src=\":/icon_128x128.png\" height=\"96\" />"
    "<img src=\":/gpl-v3-logo.svg\" height=\"64\" />", Qt::AlignCenter);
  connect (&m_->checkbox_, &QCheckBox::stateChanged, [this] (int s) {
      if (Qt::Checked == s) Q_EMIT disabled ();
    });
}

SplashScreen::~SplashScreen ()
{
}
