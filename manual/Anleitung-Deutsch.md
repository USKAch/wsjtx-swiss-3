# WSJT-SWISS 3 – Anleitung

WSJT-SWISS 3 ist eine Ausgabe von [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) 3.0.2 für den **Swiss XMAS Contest** der USKA. Während eines Contest-QSOs tauschen die Stationen ihren Kanton aus, z. B. **ZH** oder **BE**. WSJT-SWISS 3 loggt die QSOs, erstellt das Cabrillo-Log und sendet es direkt an die USKA.

Das Reglement des Contests: https://uska.ch/contest/schweizer-contest-kw/

**Wichtig:**

- WSJT-SWISS 3 wird **neben** deinem normalen WSJT-X installiert. Dein WSJT-X und seine Einstellungen werden nicht verändert.
- Rufzeichen mit Zusatz (/P, /M usw.) und Rufzeichen mit vier Buchstaben nach der Ziffer (z. B. HB9HSLU) funktionieren im Contest nicht.
- Kantone werden nur von WSJT-SWISS 3 richtig angezeigt. Deine Gegenstationen brauchen deshalb ebenfalls WSJT-SWISS 3.

---

## 1. Herunterladen

Den Installer `wsjtx-…-win64.exe` findest du auf der [Releases-Seite](https://github.com/USKAch/wsjtx-swiss-3/releases).

Browser und Virenscanner können bei einem unbekannten Installer warnen. Prüfe vor dem Behalten oder Ausführen, ob die Datei von der Releases-Seite des Projekts stammt und zur gewünschten Version gehört.

- **Chrome:** «Behalten» klicken oder unter «Downloads» «Gefährliche Datei behalten» wählen.
- **Edge:** «Behalten» → «Weitere Informationen» → «Trotzdem behalten».

## 2. Installieren

1. Den Installer ausführen.
2. Erscheint «Der Computer wurde durch Windows geschützt» (SmartScreen), prüfe Quelle und Version. **Weitere Informationen** zeigt Details; mit **Trotzdem ausführen** kannst du danach die Installation fortsetzen.
3. WSJT-SWISS 3 wird in `C:\WSJTX-SWISS3` installiert. Im Startmenü heisst es **WSJT-SWISS 3**.

Entfernen kannst du es nach dem Contest unter **Windows-Einstellungen → Apps** («WSJT-SWISS 3» deinstallieren).

## 3. Erster Start

### Einstellungen übernehmen

Beim ersten Start fragt WSJT-SWISS 3, ob es auf deinem PC nach Einstellungen von WSJT-X oder einer früheren WSJT-SWISS-Version suchen soll. Ohne deine Bestätigung wird nichts gesucht und nichts kopiert.

1. **«Suchen»** klicken.
2. Die Liste zeigt alle gefundenen Einstellungen mit Rufzeichen, Funkgerät und dem Datum der letzten Verwendung. Unten siehst du die Details des gewählten Eintrags, z. B. Soundkarten und Speicherort.
3. Den Eintrag wählen, den du für deine Station verwendest, und **«Auswahl übernehmen»** klicken.

Die Einstellungen werden für WSJT-SWISS 3 kopiert; das Original bleibt unverändert. Prüfe danach unter **File → Settings** die Register **Radio** und **Audio**, bevor du sendest.

Die Sprache der WSJT-SWISS-Fenster (Deutsch, Français, Italiano, English) kannst du oben im Fenster wählen. Sie gilt auch für die übrigen WSJT-SWISS-Meldungen. Die restliche Bedienoberfläche von WSJT-X ist englisch.

### Kanton wählen

Danach fragt WSJT-SWISS 3 nach deinem Kanton. Er wird mit jedem Contest-QSO gesendet. Ändern kannst du ihn später unter **File → Settings → Advanced**.

Der Swiss-XMAS-Modus ist bereits eingeschaltet (**File → Settings → Advanced → Special operating activity: Swiss XMAS**), und du rufst «CQ XMAS».

## 4. Betrieb

1. Unter **Mode** die Betriebsart **FT4** wählen.
2. **3.580 MHz (80 m)** oder **7.055 MHz (40 m)** in der Frequenzliste wählen. Beide Einträge tragen die Beschreibung **Swiss**. Beachte die aktuelle Ausschreibung.
3. **Enable Tx** klicken, um CQ zu rufen, oder eine Station doppelklicken, um zu antworten.

Der Kantonsaustausch läuft automatisch im QSO-Ablauf:

```
Station A (ZH)                 Station B (BE)
──────────────────────────────────────────────
CQ XMAS HB9AAA JN47
                               HB9AAA HB9BBB 1A BE
HB9BBB HB9AAA R 1A ZH
                               HB9AAA HB9BBB RR73
```

Das «1A» vor dem Kanton gehört zum Nachrichtenformat und hat keine Bedeutung.

Abgeschlossene QSOs werden automatisch ins Contest-Log eingetragen, mit **599** und dem Kanton als Rapport (z. B. «599 BE»). Das Contest-Log siehst du unter **View → Contest log**.

### Zweiter Contest-Tag

Die beiden digitalen Contest-Tage sind getrennte Contests mit getrennter Logeinsendung. Stationen vom ersten Tag darfst du am zweiten Tag wieder arbeiten.

Startest du WSJT-SWISS 3 an einem neuen Tag und das Contest-Log enthält noch QSOs eines früheren Tages, fragt das Programm:

- **«Zuerst dieses Log exportieren»** – das alte Log als Cabrillo-Datei speichern (und einsenden), danach mit einem leeren Log beginnen.
- **«Neues Contest-Log beginnen»** – sofort mit einem leeren Log beginnen.
- **«Log behalten»** – nichts ändern.

Die QSOs bleiben in jedem Fall in deiner ADIF-Logdatei (`wsjtx_log.adi`).

## 5. Log einsenden

Beachte die Einsendefrist im aktuellen Contest-Reglement.

1. Prüfe **View → Contest log** und wähle **File → Log an die USKA senden …**.
2. Prüfe das UTC-Datum des aktuellen Logs und die vorausgefüllten Stationsangaben. Ergänze beim ersten Mal Name, Adresse und E-Mail. Die Angaben bleiben gespeichert. Das Rufzeichen stammt aus **Settings → General**.
3. Klicke **Weiter**. Das Programm erstellt die Cabrillo-Datei automatisch und öffnet das Einsendefenster. Du musst vorher weder eine Datei exportieren noch einen Ordner auswählen.
4. Prüfe QSO-Anzahl, Contest und E-Mail-Adresse. Bei einem Contest-Datum im Dezember wird der passende digitale Contest vorgewählt, sofern das Portal ihn anbietet. Wähle ihn andernfalls selbst aus.
5. Lies die Erklärung, kreuze **Ich gebe diese Erklärung ab** an und klicke **Log senden**.

Die USKA bestätigt den Empfang per E-Mail mit dem Log im Anhang. Prüfe den Spam-Ordner, falls sie fehlt. Ein leeres Contestlog kann nicht eingesendet werden. Bei Warnungen kannst du die Einsendung abbrechen oder nach Prüfung trotzdem fortsetzen. Korrigiere ein abgewiesenes Log im Programm und beginne die Einsendung erneut.

Die automatisch erzeugten Dateien bleiben im Unterordner **Cabrillo** des WSJT-SWISS-Logverzeichnisses erhalten, jede Einsendung in einem eigenen Ordner. **File → Open log directory** öffnet das Verzeichnis. Bei Verbindungsproblemen kannst du die Datei auf https://contestlog.uska.ch/submit hochladen. Meldet das Programm einen ungewissen Empfang, prüfe zuerst deine E-Mail, bevor du erneut einsendest.

Für eine separate Sicherung gibt es weiterhin **File → Export Cabrillo log …**. Nach **Save** wählst du einen `.cbr`-Dateinamen. Der Dialog beginnt im Logverzeichnis und merkt sich den zuletzt erfolgreich verwendeten Exportordner. Danach kannst du sofort einsenden, die Webseite öffnen oder mit **Später** nur die lokale Kopie behalten.

## 6. Kompatibilität

**New Call on Band** ist im Standardschema unter **Settings → Colors** eingeschaltet. Gespeicherte Einstellungen bleiben beim Import oder Update erhalten. Falls die Option dort ausgeschaltet ist, kannst du sie ankreuzen oder mit **Reset Highlighting** das Standardschema laden.

| Situation | Ergebnis |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest mit Kantonsaustausch |
| WSJT-SWISS 3 ↔ WSJT-X | Normale QSOs funktionieren; Kantone werden falsch angezeigt |
| Normale FT4/FT8-QSOs ausserhalb des Contests | Wie mit WSJT-X; dafür «Special operating activity» ausschalten |

## 7. Fenster und Bildschirmfotos

Die [Fensterreferenz mit Bildschirmfotos](Window-reference.md) beschreibt die Startdialoge, alle Einstellungen, das Contestlog, die Einsendung, den Export und die zusätzlichen Anzeigen. Die ausführliche Referenz ist auf Englisch; die meisten Fenster verwenden ohnehin englische Beschriftungen. Die Bildschirmfotos zeigen ein separates Beispielprofil ohne angeschlossenes Funkgerät.

| Fenster | Zweck |
|---|---|
| First start / Einstellungen übernehmen | Sprache wählen, vorhandene Stationsdaten suchen und vor dem Kopieren prüfen. |
| Swiss XMAS Contest | Stationskanton auswählen; später unter Advanced änderbar. |
| Hauptfenster / Wide Graph | Stationen decodieren, Frequenz wählen und QSOs führen; der Wasserfall zeigt die empfangenen Signale. |
| Settings: General, Radio, Audio | Rufzeichen, Locator, Region, Funkgerätesteuerung und Audiogeräte einstellen. |
| Settings: Tx Macros, Reporting | Freie Nachrichten und automatische Protokollierung einrichten. |
| Settings: Frequencies, Colors | Arbeitsfrequenzen und die Hervorhebung neuer Rufzeichen pro Band festlegen. |
| Settings: Advanced, Alerts, Filters | Swiss XMAS und Kanton, akustische Hinweise und Anzeigefilter einstellen. |
| Contest Log / Log QSO | Kontakte prüfen oder einen Kontakt manuell protokollieren. |
| Neuer Contest-Tag | Altes Log zuerst sichern, behalten oder eine neue Contest-Tabelle beginnen. |
| Log an die USKA senden | Stationsangaben prüfen, automatisch eine Datei erzeugen und nach der Erklärung einsenden. |
| Export Cabrillo | Bei Bedarf eine zusätzliche Datei speichern; für die normale Einsendung nicht nötig. |
| Portalwarnung / Empfangsbestätigung | Logfehler prüfen; die E-Mail mit dem angehängten Log bestätigt den Empfang. |
| Astronomical Data, Echo/Fast Graph, Message Averaging | Zusätzliche Anzeigen für andere Betriebsarten; für den Swiss-FT4-Contest nicht nötig. |
| Fox Log, Active Stations, Message Creator, QSY Monitor | DXpeditions-, Stations- und Frequenzwechsel-Werkzeuge. |
| Palette Designer / Farbschema | Farben des Wasserfalls und der Decodes anpassen. |
| Configurations / Change Operator | Stationskonfiguration oder Operator wechseln. |
| Datei-, Schrift- und Farbauswahl | Die im Fenstertitel genannte Datei oder Darstellung auswählen; Abbrechen verwirft die Auswahl. |
| Download Samples, Equalization Tools, Help | Beispielaufnahmen, Kalibrierung und Programminformationen. |
| Fehler- und Rückfragedialoge | Genannten Pfad, Gerät oder Datensatz prüfen; bei Löschfragen das Ziel vor dem Bestätigen kontrollieren. |
