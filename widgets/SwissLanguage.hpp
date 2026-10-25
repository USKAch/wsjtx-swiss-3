#ifndef SWISS_LANGUAGE_HPP___
#define SWISS_LANGUAGE_HPP___

#include <QList>
#include <QLocale>
#include <QString>

class QSettings;

//
// The language of the texts WSJT-SWISS adds to WSJT-X (dialogs, messages,
// splash). The participants of the Swiss contests read German, French,
// Italian or English; until the operator chooses, the Windows language is
// used if it is one of these, German otherwise.
// The rest of the WSJT-X interface is not affected.
//
namespace swiss
{
  enum class Language {German, French, Italian, English};

  QList<Language> languages ();
  QString name (Language);      // "Deutsch", "Français", ...
  Language language ();         // the current choice
  void set_language (Language);
  QLocale locale ();            // for dates in the current language

  // The choice is kept under Swiss/Language in the settings file.
  void load_language (QSettings *);
  void save_language (QSettings *);

  // The text in the current language. The key is the English text, which
  // is also the fallback; placeholders (%1 ...) are kept.
  QString t (char const * english);
}

#endif
