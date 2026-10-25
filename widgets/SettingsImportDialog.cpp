#include "SettingsImportDialog.hpp"

#include <algorithm>

#include <QComboBox>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QList>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QSplitter>
#include <QStackedWidget>
#include <QStringList>
#include <QTextBrowser>
#include <QTreeWidget>
#include <QVBoxLayout>

#include "Transceiver/TransceiverFactory.hpp"
#include "SwissLanguage.hpp"

namespace
{
  //
  // The dialog speaks the four languages of the Swiss contest
  // participants. It starts in swiss::language () (the Windows language,
  // or German), and the
  // choice made here becomes the language of all WSJT-SWISS texts.
  //
  using Language = swiss::Language;

  struct Texts
  {
    char const * name;          // shown in the language selector
    char const * locale;        // dates and times
    char const * language;
    char const * title_first;
    char const * title_import;
    char const * question;
    char const * search;
    char const * start_empty;
    char const * intro;
    char const * col_program;
    char const * col_callsign;
    char const * col_radio;
    char const * col_last_used;
    char const * placeholder;
    char const * import_selected;
    char const * none_found;
    char const * imported;
    char const * copy_failed;
    char const * no_radio;
    char const * radio_via;     // %1 radio, %2 port
    char const * ptt_dtr;       // %1 port
    char const * ptt_rts;
    char const * version_2;
    char const * with_profile;  // %1 program, %2 profile
    char const * in_use;        // %1 configuration
    char const * program;
    char const * settings_file;
    char const * last_used;
    char const * callsign;
    char const * locator;
    char const * radio;
    char const * sound_in;
    char const * sound_out;
    char const * last_mode;
    char const * last_frequency;
    char const * configurations;
  };

  Texts const german {
    "Deutsch", "de_CH", "Sprache",
    "WSJT-SWISS 3 – erster Start",
    "WSJT-SWISS 3 – Einstellungen übernehmen",
    "WSJT-SWISS 3 hat noch keine Einstellungen.\n\n"
    "Soll auf diesem PC nach Einstellungen von WSJT-X oder einer früheren "
    "WSJT-SWISS-Version gesucht werden? Du kannst dann Rufzeichen, "
    "Funkgerät und Soundkarte übernehmen.\n\n"
    "Ohne deine Bestätigung wird nichts kopiert, und die Einstellungen der "
    "anderen Programme werden nicht verändert.",
    "Suchen",
    "Ohne Einstellungen starten",
    "Diese Einstellungen wurden auf diesem PC gefunden. Wähle diejenige "
    "aus, die du für deine Station verwendest, prüfe unten die Details "
    "und klicke dann auf «Auswahl übernehmen». Die Einstellungen "
    "werden für WSJT-SWISS 3 kopiert; das Original bleibt unverändert.",
    "Programm / Profil", "Rufzeichen", "Funkgerät", "Zuletzt verwendet",
    "Wähle oben einen Eintrag aus, um die Details zu sehen.",
    "Auswahl übernehmen",
    "Auf diesem PC wurden keine Einstellungen von WSJT-X oder WSJT-SWISS "
    "gefunden.\nWSJT-SWISS 3 startet ohne Einstellungen.",
    "Die Einstellungen wurden übernommen aus\n%1\n\n"
    "Prüfe vor dem Senden unter «File > Settings» die Register "
    "«Radio» und «Audio».",
    "Die Einstellungen konnten nicht kopiert werden aus\n%1\n\n"
    "WSJT-SWISS 3 startet ohne Einstellungen.",
    "Keine Gerätesteuerung", "%1 über %2", "DTR an %1", "RTS an %1",
    "WSJT-SWISS (frühere Version)", "%1, Profil «%2»", "%1 (aktiv)",
    "Programm", "Einstellungsdatei", "Zuletzt verwendet", "Rufzeichen",
    "Locator", "Funkgerät", "Soundkarte Eingang", "Soundkarte Ausgang",
    "Letzte Betriebsart", "Letzte Frequenz", "Konfigurationen"
  };

  Texts const french {
    "Français", "fr_CH", "Langue",
    "WSJT-SWISS 3 – premier démarrage",
    "WSJT-SWISS 3 – reprendre les réglages",
    "WSJT-SWISS 3 n'a pas encore de réglages.\n\n"
    "Faut-il rechercher sur ce PC les réglages de WSJT-X ou d'une version "
    "précédente de WSJT-SWISS ? Tu pourras ensuite reprendre ton "
    "indicatif, ton transceiver et ta carte son.\n\n"
    "Rien n'est copié sans ta confirmation, et les réglages des autres "
    "programmes ne sont pas modifiés.",
    "Rechercher",
    "Démarrer sans réglages",
    "Ces réglages ont été trouvés sur ce PC. Sélectionne celui que "
    "tu utilises pour ta station, vérifie les détails ci-dessous, puis "
    "clique sur « Reprendre la sélection ». Il est copié pour "
    "WSJT-SWISS 3 ; l'original reste inchangé.",
    "Programme / profil", "Indicatif", "Transceiver", "Dernière utilisation",
    "Sélectionne une entrée ci-dessus pour voir ses détails.",
    "Reprendre la sélection",
    "Aucun réglage de WSJT-X ou de WSJT-SWISS n'a été trouvé sur ce PC.\n"
    "WSJT-SWISS 3 démarre sans réglages.",
    "Les réglages ont été repris de\n%1\n\n"
    "Avant d'émettre, vérifie dans « File > Settings » les onglets "
    "« Radio » et « Audio ».",
    "Les réglages n'ont pas pu être copiés depuis\n%1\n\n"
    "WSJT-SWISS 3 démarre sans réglages.",
    "Pas de commande du transceiver", "%1 via %2", "DTR sur %1", "RTS sur %1",
    "WSJT-SWISS (version précédente)", "%1, profil « %2 »", "%1 (actif)",
    "Programme", "Fichier de réglages", "Dernière utilisation", "Indicatif",
    "Locator", "Transceiver", "Carte son entrée", "Carte son sortie",
    "Dernier mode", "Dernière fréquence", "Configurations"
  };

  Texts const italian {
    "Italiano", "it_CH", "Lingua",
    "WSJT-SWISS 3 – primo avvio",
    "WSJT-SWISS 3 – importare le impostazioni",
    "WSJT-SWISS 3 non ha ancora impostazioni.\n\n"
    "Cercare su questo PC le impostazioni di WSJT-X o di una versione "
    "precedente di WSJT-SWISS? Potrai poi riprendere il tuo nominativo, il "
    "ricetrasmettitore e la scheda audio.\n\n"
    "Nulla viene copiato senza la tua conferma e le impostazioni degli altri "
    "programmi non vengono modificate.",
    "Cerca",
    "Avvia senza impostazioni",
    "Queste impostazioni sono state trovate su questo PC. Seleziona quella che "
    "usi per la tua stazione, controlla i dettagli qui sotto e poi clicca su "
    "«Importa la selezione». Viene copiata per WSJT-SWISS 3; l'originale "
    "resta invariato.",
    "Programma / profilo", "Nominativo", "Ricetrasmettitore", "Ultimo utilizzo",
    "Seleziona una voce qui sopra per vederne i dettagli.",
    "Importa la selezione",
    "Su questo PC non sono state trovate impostazioni di WSJT-X o WSJT-SWISS.\n"
    "WSJT-SWISS 3 si avvia senza impostazioni.",
    "Le impostazioni sono state importate da\n%1\n\n"
    "Prima di trasmettere, controlla in «File > Settings» le schede "
    "«Radio» e «Audio».",
    "Non è stato possibile copiare le impostazioni da\n%1\n\n"
    "WSJT-SWISS 3 si avvia senza impostazioni.",
    "Nessun controllo del ricetrasmettitore", "%1 tramite %2", "DTR su %1", "RTS su %1",
    "WSJT-SWISS (versione precedente)", "%1, profilo «%2»", "%1 (in uso)",
    "Programma", "File delle impostazioni", "Ultimo utilizzo", "Nominativo",
    "Locator", "Ricetrasmettitore", "Scheda audio ingresso", "Scheda audio uscita",
    "Ultimo modo", "Ultima frequenza", "Configurazioni"
  };

  Texts const english {
    "English", "en_GB", "Language",
    "WSJT-SWISS 3 – first start",
    "WSJT-SWISS 3 – import settings",
    "WSJT-SWISS 3 has no settings yet.\n\n"
    "Should it search this PC for the settings of WSJT-X or an earlier "
    "WSJT-SWISS? You can then take over your callsign, radio and sound card "
    "setup.\n\n"
    "Nothing is copied without your confirmation, and the settings of the "
    "other programs are not changed.",
    "Search",
    "Start with empty settings",
    "These settings were found on this PC. Select the one you use for your "
    "station and check its details below, then click \"Import selected\". It "
    "is copied for WSJT-SWISS 3; the original stays unchanged.",
    "Program / profile", "Callsign", "Radio", "Last used",
    "Select an entry above to see its details.",
    "Import selected",
    "No settings of WSJT-X or WSJT-SWISS were found on this PC.\n"
    "WSJT-SWISS 3 starts with empty settings.",
    "The settings were imported from\n%1\n\n"
    "Before transmitting, check File > Settings, tabs Radio and Audio.",
    "The settings could not be copied from\n%1\n\n"
    "WSJT-SWISS 3 starts with empty settings.",
    "No radio control", "%1 via %2", "DTR on %1", "RTS on %1",
    "WSJT-SWISS (earlier version)", "%1, profile \"%2\"", "%1 (in use)",
    "Program", "Settings file", "Last used", "Callsign",
    "Locator", "Radio", "Sound card in", "Sound card out",
    "Last mode", "Last frequency", "Configurations"
  };

  Texts const& texts (Language l)
  {
    switch (l)
      {
      case Language::German: return german;
      case Language::French: return french;
      case Language::Italian: return italian;
      default: return english;
      }
  }

  QString t (char const * text) {return QString::fromUtf8 (text);}

  // A settings file of WSJT-X or WSJT-SWISS found on this PC; values
  // are kept raw and worded in the chosen language when shown.
  struct FoundSettings
  {
    QString path;
    QString folder_program;
    QString profile;
    QDateTime last_used;
    QString callsign;
    QString grid;
    QString rig;
    QString cat_port;
    TransceiverFactory::PTTMethod ptt_method;
    QString ptt_port;
    QString sound_in;
    QString sound_out;
    QString mode;
    QString frequency;
    QStringList configurations;
    QString current_configuration;
  };

  FoundSettings read (QFileInfo const& ini, QString const& folder)
  {
    // Read only: no value is ever set, so QSettings never writes.
    QSettings s {ini.absoluteFilePath (), QSettings::IniFormat};
    FoundSettings f;
    f.path = QDir::toNativeSeparators (ini.absoluteFilePath ());
    auto parts = folder.split (" - ");
    f.folder_program = parts.takeFirst ();
    f.profile = parts.join (" - ");
    f.last_used = ini.lastModified ();
    f.callsign = s.value ("Configuration/MyCall").toString ();
    f.grid = s.value ("Configuration/MyGrid").toString ();
    f.rig = s.value ("Configuration/Rig").toString ();
    f.cat_port = s.value ("Configuration/CATNetworkPort").toString ();
    if (f.cat_port.isEmpty ()) f.cat_port = s.value ("Configuration/CATUSBPort").toString ();
    if (f.cat_port.isEmpty ()) f.cat_port = s.value ("Configuration/CATSerialPort").toString ();
    f.ptt_method = s.value ("Configuration/PTTMethod").value<TransceiverFactory::PTTMethod> ();
    f.ptt_port = s.value ("Configuration/PTTport").toString ();
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
  QList<FoundSettings> search (QString const& target_ini)
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

  QString program_name (FoundSettings const& f, Texts const& tx)
  {
    if (f.folder_program == "WSJT-SWISS") return t (tx.version_2);
    if (f.folder_program == "WSJT-SWISS3") return "WSJT-SWISS 3";
    return f.folder_program;
  }

  QString radio_text (FoundSettings const& f, Texts const& tx)
  {
    if (f.rig.isEmpty () || f.rig == "None") return t (tx.no_radio);
    return f.cat_port.isEmpty () ? f.rig : t (tx.radio_via).arg (f.rig, f.cat_port);
  }

  QString ptt_text (FoundSettings const& f, Texts const& tx)
  {
    switch (f.ptt_method)
      {
      case TransceiverFactory::PTT_method_CAT: return "CAT";
      case TransceiverFactory::PTT_method_DTR: return t (tx.ptt_dtr).arg (f.ptt_port);
      case TransceiverFactory::PTT_method_RTS: return t (tx.ptt_rts).arg (f.ptt_port);
      default: return "VOX";
      }
  }

  QString date_text (QDateTime const& d, Texts const& tx)
  {
    return QLocale {tx.locale}.toString (d, QLocale::ShortFormat);
  }

  QString details (FoundSettings const& f, Texts const& tx)
  {
    auto row = [] (char const * label, QString const& value) {
      return "<tr><td><b>" + t (label).toHtmlEscaped () + "</b>&nbsp;&nbsp;</td><td>"
        + (value.isEmpty () ? "&ndash;" : value.toHtmlEscaped ()) + "</td></tr>";
    };
    QStringList configurations;
    for (auto const& name : f.configurations)
      {
        configurations << (name == f.current_configuration ? t (tx.in_use).arg (name) : name);
      }
    auto program = program_name (f, tx);
    if (!f.profile.isEmpty ()) program = t (tx.with_profile).arg (program, f.profile);
    return "<table>"
      + row (tx.program, program)
      + row (tx.settings_file, f.path)
      + row (tx.last_used, date_text (f.last_used, tx))
      + row (tx.callsign, f.callsign)
      + row (tx.locator, f.grid)
      + row (tx.radio, radio_text (f, tx))
      + row ("PTT", ptt_text (f, tx))
      + row (tx.sound_in, f.sound_in)
      + row (tx.sound_out, f.sound_out)
      + row (tx.last_mode, f.mode)
      + row (tx.last_frequency, f.frequency)
      + row (tx.configurations, configurations.join (", "))
      + "</table>";
  }

  //
  // One window, two pages: the question whether to search, then the
  // settings found. The language selector stays on top of both.
  //
  class ImportDialog final
    : public QDialog
  {
  public:
    explicit ImportDialog (QString const& target_ini)
      : target_ini_ {target_ini}
      , language_ {swiss::language ()}
    {
      resize (900, 560);
      auto layout = new QVBoxLayout {this};

      auto language_row = new QHBoxLayout;
      language_row->addStretch ();
      language_row->addWidget (&language_label_);
      for (auto l : {Language::German, Language::French, Language::Italian, Language::English})
        {
          language_box_.addItem (t (texts (l).name), static_cast<int> (l));
        }
      language_box_.setCurrentIndex (language_box_.findData (static_cast<int> (language_)));
      language_row->addWidget (&language_box_);
      layout->addLayout (language_row);

      // page 0: may we search?
      auto question_page = new QWidget;
      auto question_layout = new QVBoxLayout {question_page};
      question_.setWordWrap (true);
      question_layout->addWidget (&question_);
      question_layout->addStretch ();
      auto question_buttons = new QHBoxLayout;
      question_buttons->addStretch ();
      question_buttons->addWidget (&search_button_);
      question_buttons->addWidget (&empty_button_1_);
      question_layout->addLayout (question_buttons);
      pages_.addWidget (question_page);

      // page 1: the settings found
      auto list_page = new QWidget;
      auto list_layout = new QVBoxLayout {list_page};
      intro_.setWordWrap (true);
      list_layout->addWidget (&intro_);
      auto splitter = new QSplitter {Qt::Vertical};
      list_.setRootIsDecorated (false);
      splitter->addWidget (&list_);
      splitter->addWidget (&details_);
      list_layout->addWidget (splitter, 1);
      auto list_buttons = new QHBoxLayout;
      list_buttons->addStretch ();
      list_buttons->addWidget (&import_button_);
      list_buttons->addWidget (&empty_button_2_);
      list_layout->addLayout (list_buttons);
      pages_.addWidget (list_page);

      layout->addWidget (&pages_, 1);
      search_button_.setDefault (true);
      import_button_.setEnabled (false); // no preselection: the operator chooses

      connect (&language_box_, QOverload<int>::of (&QComboBox::currentIndexChanged), [this] {
          language_ = static_cast<Language> (language_box_.currentData ().toInt ());
          swiss::set_language (language_);
          retranslate ();
        });
      connect (&search_button_, &QPushButton::clicked, [this] {
          found_ = search (target_ini_);
          if (found_.isEmpty ())
            {
              QMessageBox::information (this, t (tx ().title_import), t (tx ().none_found));
              reject ();
              return;
            }
          pages_.setCurrentIndex (1);
          retranslate ();
        });
      connect (&empty_button_1_, &QPushButton::clicked, this, &QDialog::reject);
      connect (&empty_button_2_, &QPushButton::clicked, this, &QDialog::reject);
      // Follow the selection, not the current item: a view may make its
      // first row current on focus, which must not count as a choice.
      connect (&list_, &QTreeWidget::itemSelectionChanged, [this] {
          import_button_.setEnabled (selected_row () >= 0);
          show_details ();
        });
      connect (&import_button_, &QPushButton::clicked, [this] {
          if (selected_row () >= 0) accept ();
        });

      retranslate ();
    }

    Texts const& tx () const {return texts (language_);}

    FoundSettings const * chosen () const
    {
      auto row = selected_row ();
      return row >= 0 ? &found_[row] : nullptr;
    }

  private:
    int selected_row () const
    {
      auto items = list_.selectedItems ();
      return items.isEmpty () ? -1 : list_.indexOfTopLevelItem (items.first ());
    }

    void show_details ()
    {
      auto row = selected_row ();
      details_.setHtml (row >= 0 ? details (found_[row], tx ()) : QString {});
    }

    void retranslate ()
    {
      auto const& x = tx ();
      setWindowTitle (t (pages_.currentIndex () ? x.title_import : x.title_first));
      language_label_.setText (t (x.language) + ':');
      question_.setText (t (x.question));
      search_button_.setText (t (x.search));
      empty_button_1_.setText (t (x.start_empty));
      empty_button_2_.setText (t (x.start_empty));
      intro_.setText (t (x.intro));
      import_button_.setText (t (x.import_selected));
      details_.setPlaceholderText (t (x.placeholder));
      list_.setHeaderLabels ({t (x.col_program), t (x.col_callsign), t (x.col_radio), t (x.col_last_used)});

      // Rewrite the rows in place so the operator's selection is kept.
      for (int row = 0; row < found_.size (); ++row)
        {
          auto const& f = found_[row];
          auto item = list_.topLevelItem (row);
          if (!item) item = new QTreeWidgetItem {&list_};
          auto name = program_name (f, x);
          if (!f.profile.isEmpty ()) name += " - " + f.profile;
          item->setText (0, name);
          item->setText (1, f.callsign);
          item->setText (2, radio_text (f, x));
          item->setText (3, date_text (f.last_used, x));
        }
      list_.header ()->setSectionResizeMode (QHeaderView::ResizeToContents);
      show_details ();
    }

    QString target_ini_;
    Language language_;
    QList<FoundSettings> found_;
    QLabel language_label_;
    QComboBox language_box_;
    QStackedWidget pages_;
    QLabel question_;
    QPushButton search_button_;
    QPushButton empty_button_1_;
    QLabel intro_;
    QTreeWidget list_;
    QTextBrowser details_;
    QPushButton import_button_;
    QPushButton empty_button_2_;
  };
}

void offer_settings_import (QString const& target_ini)
{
  if (QFileInfo::exists (target_ini)) return;

  ImportDialog dialog {target_ini};
  auto const accepted = QDialog::Accepted == dialog.exec ();
  auto chosen = accepted ? dialog.chosen () : nullptr;
  auto const& x = dialog.tx ();
  QDir {}.mkpath (QFileInfo {target_ini}.absolutePath ());
  if (chosen)
    {
      if (QFile::copy (chosen->path, target_ini))
        {
          QFile {target_ini}.setPermissions (QFile::ReadOwner | QFile::WriteOwner);
          QMessageBox::information (nullptr, t (x.title_import), t (x.imported).arg (chosen->path));
        }
      else
        {
          QMessageBox::warning (nullptr, t (x.title_import), t (x.copy_failed).arg (chosen->path));
        }
    }

  // Keep the language chosen here for all WSJT-SWISS texts; written after
  // the copy, which needs the file not to exist yet.
  QSettings settings {target_ini, QSettings::IniFormat};
  swiss::save_language (&settings);
}
