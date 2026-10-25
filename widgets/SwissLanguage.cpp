#include "SwissLanguage.hpp"

#include <QHash>
#include <QSettings>

namespace
{
  struct Entry
  {
    char const * english;
    char const * german;
    char const * french;
    char const * italian;
  };

  // German in Swiss spelling (ss). Keep the placeholders of the English text.
  Entry const entries[] = {
    // splash screen
    {"Swiss XMAS Contest edition of WSJT-X by K1JT et al.",
     "Ausgabe von WSJT-X (K1JT et al.) für den Swiss XMAS Contest",
     "Édition de WSJT-X (K1JT et al.) pour le Swiss XMAS Contest",
     "Edizione di WSJT-X (K1JT et al.) per lo Swiss XMAS Contest"},
    {"Swiss adaptation by HB9BLA",
     "Schweizer Anpassung: HB9BLA",
     "Adaptation suisse : HB9BLA",
     "Adattamento svizzero: HB9BLA"},
    {"Send WSJT-SWISS issue reports to",
     "Fehlermeldungen zu WSJT-SWISS an",
     "Signalez les problèmes de WSJT-SWISS à",
     "Segnalate i problemi di WSJT-SWISS a"},
    {"Do not show this again",
     "Nicht mehr anzeigen",
     "Ne plus afficher",
     "Non mostrare più"},

    // canton
    {"Swiss XMAS Contest", "Swiss XMAS Contest", "Swiss XMAS Contest", "Swiss XMAS Contest"},
    {"Select the canton of your station. It is sent with every contest QSO, e.g. \"599 ZH\".\n"
     "You can change it later in File > Settings > Advanced.",
     "Wählen Sie den Kanton Ihrer Station. Er wird mit jedem Contest-QSO gesendet, z. B. «599 ZH».\n"
     "Sie können ihn später unter File > Settings > Advanced ändern.",
     "Choisissez le canton de votre station. Il est transmis à chaque QSO du concours, p. ex. « 599 ZH ».\n"
     "Vous pourrez le modifier plus tard sous File > Settings > Advanced.",
     "Scelga il cantone della Sua stazione. Viene trasmesso con ogni QSO del contest, ad es. «599 ZH».\n"
     "Potrà modificarlo più tardi in File > Settings > Advanced."},
    {"Select your canton for the Swiss XMAS Contest",
     "Wählen Sie Ihren Kanton für den Swiss XMAS Contest",
     "Choisissez votre canton pour le Swiss XMAS Contest",
     "Scelga il Suo cantone per lo Swiss XMAS Contest"},
    {"OK", "OK", "OK", "OK"},
    {"Later", "Später", "Plus tard", "Più tardi"},
    {"Cancel", "Abbrechen", "Annuler", "Annulla"},
    {"Close", "Schliessen", "Fermer", "Chiudi"},
    {"Language:", "Sprache:", "Langue :", "Lingua:"},

    // new contest day
    {"Swiss XMAS - new contest day",
     "Swiss XMAS – neuer Contest-Tag",
     "Swiss XMAS – nouveau jour de concours",
     "Swiss XMAS – nuovo giorno di contest"},
    {"Your contest log holds %1 QSOs from %2 (UTC).\n\n"
     "The two digital contest days are separate contests with separate log submissions, "
     "and stations worked then may be worked again today.\n\n"
     "Start today with a new, empty contest log? The QSOs stay in your ADIF log file (wsjtx_log.adi).",
     "Ihr Contest-Log enthält %1 QSOs vom %2 (UTC).\n\n"
     "Die beiden digitalen Contest-Tage sind getrennte Contests mit getrennter Logeinsendung; "
     "damals gearbeitete Stationen dürfen heute erneut gearbeitet werden.\n\n"
     "Heute mit einem neuen, leeren Contest-Log beginnen? Die QSOs bleiben in Ihrer ADIF-Logdatei (wsjtx_log.adi).",
     "Votre log de concours contient %1 QSO du %2 (UTC).\n\n"
     "Les deux journées numériques sont des concours distincts, avec des envois de logs distincts, "
     "et les stations contactées alors peuvent l'être à nouveau aujourd'hui.\n\n"
     "Commencer aujourd'hui avec un nouveau log de concours vide ? Les QSO restent dans votre fichier log ADIF (wsjtx_log.adi).",
     "Il Suo log del contest contiene %1 QSO del %2 (UTC).\n\n"
     "Le due giornate digitali sono contest separati con invii dei log separati, "
     "e le stazioni collegate allora possono essere collegate di nuovo oggi.\n\n"
     "Iniziare oggi con un nuovo log del contest vuoto? I QSO restano nel Suo file log ADIF (wsjtx_log.adi)."},
    {"Export that log first",
     "Zuerst dieses Log exportieren",
     "Exporter d'abord ce log",
     "Esportare prima questo log"},
    {"Start a new contest log",
     "Neues Contest-Log beginnen",
     "Commencer un nouveau log de concours",
     "Iniziare un nuovo log del contest"},
    {"Keep the log",
     "Log behalten",
     "Conserver le log",
     "Mantenere il log"},

    // Cabrillo export
    {"Cabrillo Log saved",
     "Cabrillo-Log gespeichert",
     "Log Cabrillo enregistré",
     "Log Cabrillo salvato"},
    {"The log was saved as\n%1\n\nSubmit it to the USKA log portal now?",
     "Das Log wurde gespeichert als\n%1\n\nJetzt an das USKA-Logportal senden?",
     "Le log a été enregistré sous\n%1\n\nL'envoyer maintenant au portail de logs de l'USKA ?",
     "Il log è stato salvato come\n%1\n\nInviarlo ora al portale dei log dell'USKA?"},
    {"Submit to USKA now",
     "Jetzt an die USKA senden",
     "Envoyer maintenant à l'USKA",
     "Invia ora all'USKA"},
    {"Open submission page",
     "Einsendeseite öffnen",
     "Ouvrir la page d'envoi",
     "Apri la pagina di invio"},
    {"Submit Cabrillo log to USKA ...",
     "Cabrillo-Log an die USKA senden ...",
     "Envoyer un log Cabrillo à l'USKA ...",
     "Inviare un log Cabrillo all'USKA ..."},
    {"Submit Cabrillo log to USKA",
     "Cabrillo-Log an die USKA senden",
     "Envoyer un log Cabrillo à l'USKA",
     "Inviare un log Cabrillo all'USKA"},
    {"Cabrillo Log (*.cbr *.log *.txt)",
     "Cabrillo-Log (*.cbr *.log *.txt)",
     "Log Cabrillo (*.cbr *.log *.txt)",
     "Log Cabrillo (*.cbr *.log *.txt)"},
    {"Cannot open \"%1\": %2",
     "«%1» kann nicht geöffnet werden: %2",
     "Impossible d'ouvrir « %1 » : %2",
     "Impossibile aprire «%1»: %2"},

    // submission window
    {"Submit log to USKA",
     "Log an die USKA senden",
     "Envoyer le log à l'USKA",
     "Inviare il log all'USKA"},
    {"Log file:", "Logdatei:", "Fichier log :", "File di log:"},
    {"Callsign:", "Rufzeichen:", "Indicatif :", "Nominativo:"},
    {"QSOs:", "QSOs:", "QSO :", "QSO:"},
    {"Contest:", "Contest:", "Concours :", "Contest:"},
    {"Email for the confirmation:",
     "E-Mail für die Bestätigung:",
     "E-mail pour la confirmation :",
     "E-mail per la conferma:"},
    {"I declare that I have adhered strictly to the contest rules and regulations as well as "
     "the provisions of my license.",
     "Ich erkläre, dass ich das Wettbewerbsreglement sowie die Bestimmungen meiner Konzession "
     "genau eingehalten habe.",
     "Je déclare avoir strictement respecté le règlement du concours ainsi que les dispositions "
     "de ma concession.",
     "Dichiaro di aver rispettato rigorosamente il regolamento del contest e le disposizioni "
     "della mia concessione."},
    {"I make this declaration",
     "Ich gebe diese Erklärung ab",
     "Je fais cette déclaration",
     "Faccio questa dichiarazione"},
    {"Submit log", "Log senden", "Envoyer le log", "Invia il log"},
    {"Use the web page instead",
     "Stattdessen die Webseite verwenden",
     "Utiliser plutôt la page web",
     "Usa invece la pagina web"},
    {"HTTP status %1", "HTTP-Status %1", "Statut HTTP %1", "Stato HTTP %1"},
    {"Fetching the open contests from %1 ...",
     "Offene Contests werden von %1 abgerufen ...",
     "Récupération des concours ouverts depuis %1 ...",
     "Recupero dei contest aperti da %1 ..."},
    {"The USKA log portal could not be reached.",
     "Das USKA-Logportal ist nicht erreichbar.",
     "Le portail de logs de l'USKA est injoignable.",
     "Il portale dei log dell'USKA non è raggiungibile."},
    {"The portal has no open contest at the moment. Each contest opens for submissions after it "
     "has taken place.",
     "Das Portal hat zurzeit keinen offenen Contest. Jeder Contest wird nach seiner Durchführung "
     "für Einsendungen geöffnet.",
     "Le portail n'a actuellement aucun concours ouvert. Chaque concours est ouvert aux envois "
     "après son déroulement.",
     "Il portale non ha al momento alcun contest aperto. Ogni contest viene aperto agli invii "
     "dopo il suo svolgimento."},
    {"Contest preselected from the QSO date; check it.",
     "Contest anhand des QSO-Datums vorgewählt; bitte prüfen.",
     "Concours présélectionné d'après la date des QSO ; veuillez vérifier.",
     "Contest preselezionato in base alla data dei QSO; verifichi per favore."},
    {"Choose the contest of this log.",
     "Wählen Sie den Contest dieses Logs.",
     "Choisissez le concours de ce log.",
     "Scelga il contest di questo log."},
    {"Cannot read %1: %2",
     "%1 kann nicht gelesen werden: %2",
     "Impossible de lire %1 : %2",
     "Impossibile leggere %1: %2"},
    {"Uploading the log for checking ...",
     "Das Log wird zur Prüfung hochgeladen ...",
     "Envoi du log pour vérification ...",
     "Caricamento del log per la verifica ..."},
    {"The log could not be uploaded.",
     "Das Log konnte nicht hochgeladen werden.",
     "Le log n'a pas pu être envoyé.",
     "Non è stato possibile caricare il log."},
    {"The portal rejected the log:",
     "Das Portal hat das Log abgelehnt:",
     "Le portail a refusé le log :",
     "Il portale ha rifiutato il log:"},
    {"Please correct the log and export it again.",
     "Bitte korrigieren Sie das Log und exportieren Sie es erneut.",
     "Veuillez corriger le log et l'exporter à nouveau.",
     "Corregga il log e lo esporti di nuovo."},
    {"Unexpected answer from the portal (%1).",
     "Unerwartete Antwort des Portals (%1).",
     "Réponse inattendue du portail (%1).",
     "Risposta inattesa del portale (%1)."},
    {"The portal found these issues:",
     "Das Portal hat diese Probleme gefunden:",
     "Le portail a trouvé ces problèmes :",
     "Il portale ha trovato questi problemi:"},
    {"The portal found %1 issue(s) in the log, listed in the window. Invalid QSOs may reduce the "
     "score.\n\nSubmit the log anyway?",
     "Das Portal hat %1 Problem(e) im Log gefunden; sie sind im Fenster aufgeführt. Ungültige QSOs "
     "können die Punktzahl verringern.\n\nLog trotzdem senden?",
     "Le portail a trouvé %1 problème(s) dans le log, indiqués dans la fenêtre. Des QSO non "
     "valables peuvent réduire le score.\n\nEnvoyer le log quand même ?",
     "Il portale ha trovato %1 problema/i nel log, elencati nella finestra. QSO non validi possono "
     "ridurre il punteggio.\n\nInviare comunque il log?"},
    {"Submit anyway", "Trotzdem senden", "Envoyer quand même", "Invia comunque"},
    {"Submission cancelled.",
     "Einsendung abgebrochen.",
     "Envoi annulé.",
     "Invio annullato."},
    {"The portal suggests no category for this log; please submit it on the web page.",
     "Das Portal schlägt für dieses Log keine Kategorie vor; bitte senden Sie es über die Webseite.",
     "Le portail ne propose aucune catégorie pour ce log ; veuillez l'envoyer via la page web.",
     "Il portale non propone alcuna categoria per questo log; lo invii tramite la pagina web."},
    {"The portal did not accept the details.",
     "Das Portal hat die Angaben nicht akzeptiert.",
     "Le portail n'a pas accepté les informations.",
     "Il portale non ha accettato i dati."},
    {"Submitting the log ...",
     "Das Log wird gesendet ...",
     "Envoi du log ...",
     "Invio del log ..."},
    {"The portal's answer was not the expected confirmation.",
     "Die Antwort des Portals war nicht die erwartete Bestätigung.",
     "La réponse du portail n'était pas la confirmation attendue.",
     "La risposta del portale non era la conferma attesa."},
    {"The log may have been received anyway: if a confirmation email from the portal arrives, "
     "it was. Otherwise try again, or use the web page.",
     "Das Log ist möglicherweise trotzdem angekommen: Wenn eine Bestätigungs-E-Mail des Portals "
     "eintrifft, ist es angekommen. Andernfalls versuchen Sie es erneut oder verwenden Sie die Webseite.",
     "Le log a peut-être été reçu malgré tout : si un e-mail de confirmation du portail arrive, "
     "c'est le cas. Sinon, réessayez ou utilisez la page web.",
     "Il log potrebbe essere stato ricevuto comunque: se arriva un'e-mail di conferma dal portale, "
     "è stato ricevuto. Altrimenti riprovi o usi la pagina web."},
    {"Nothing was submitted. You can try again, or use the web page.",
     "Es wurde nichts gesendet. Sie können es erneut versuchen oder die Webseite verwenden.",
     "Rien n'a été envoyé. Vous pouvez réessayer ou utiliser la page web.",
     "Non è stato inviato nulla. Può riprovare o usare la pagina web."},
    {"USKA has received your log for \"%1\" (category %2).\n\n"
     "A confirmation with the log attached is sent to %3; it is the official receipt. "
     "If it does not arrive, check your spam folder.",
     "Die USKA hat Ihr Log für «%1» (Kategorie %2) erhalten.\n\n"
     "Eine Bestätigung mit dem Log im Anhang wird an %3 gesendet; sie ist die offizielle "
     "Empfangsbestätigung. Falls sie nicht ankommt, prüfen Sie den Spam-Ordner.",
     "L'USKA a reçu votre log pour « %1 » (catégorie %2).\n\n"
     "Une confirmation avec le log en pièce jointe est envoyée à %3 ; c'est l'accusé de réception "
     "officiel. Si elle n'arrive pas, vérifiez votre dossier de spam.",
     "L'USKA ha ricevuto il Suo log per «%1» (categoria %2).\n\n"
     "Una conferma con il log allegato viene inviata a %3; è la ricevuta ufficiale. "
     "Se non arriva, controlli la cartella dello spam."},
  };

  swiss::Language current {swiss::Language::German};

  QHash<QString, Entry const *> const& index ()
  {
    static QHash<QString, Entry const *> const map = [] {
      QHash<QString, Entry const *> m;
      for (auto const& e : entries) m.insert (QString::fromUtf8 (e.english), &e);
      return m;
    } ();
    return map;
  }

  char const * code (swiss::Language l)
  {
    switch (l)
      {
      case swiss::Language::French: return "fr";
      case swiss::Language::Italian: return "it";
      case swiss::Language::English: return "en";
      default: return "de";
      }
  }
}

namespace swiss
{
  QList<Language> languages ()
  {
    return {Language::German, Language::French, Language::Italian, Language::English};
  }

  QString name (Language l)
  {
    switch (l)
      {
      case Language::French: return QString::fromUtf8 ("Français");
      case Language::Italian: return "Italiano";
      case Language::English: return "English";
      default: return "Deutsch";
      }
  }

  Language language ()
  {
    return current;
  }

  void set_language (Language l)
  {
    current = l;
  }

  QLocale locale ()
  {
    switch (current)
      {
      case Language::French: return QLocale {"fr_CH"};
      case Language::Italian: return QLocale {"it_CH"};
      case Language::English: return QLocale {"en_GB"};
      default: return QLocale {"de_CH"};
      }
  }

  void load_language (QSettings * settings)
  {
    auto const& stored = settings->value ("Swiss/Language").toString ();
    for (auto l : languages ())
      {
        if (stored == code (l)) current = l;
      }
  }

  void save_language (QSettings * settings)
  {
    settings->setValue ("Swiss/Language", code (current));
  }

  QString t (char const * english)
  {
    auto const& key = QString::fromUtf8 (english);
    auto const& e = index ().value (key);
    if (!e) return key;
    switch (current)
      {
      case Language::German: return QString::fromUtf8 (e->german);
      case Language::French: return QString::fromUtf8 (e->french);
      case Language::Italian: return QString::fromUtf8 (e->italian);
      default: return key;
      }
  }
}
