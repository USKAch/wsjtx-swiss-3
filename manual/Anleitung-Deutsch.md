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

Browser und Virenscanner blockieren den Download manchmal, weil die Datei selten heruntergeladen wird. Das ist ein Fehlalarm.

- **Chrome:** «Behalten» klicken oder unter «Downloads» «Gefährliche Datei behalten» wählen.
- **Edge:** «Behalten» → «Weitere Informationen» → «Trotzdem behalten».

## 2. Installieren

1. Den Installer ausführen.
2. Erscheint die Warnung «Der Computer wurde durch Windows geschützt» (SmartScreen): **«Weitere Informationen»** und dann **«Trotzdem ausführen»** klicken. Das Programm ist nicht mit einem kommerziellen Zertifikat signiert; das ist bei Open-Source-Software üblich.
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
2. Band und Frequenz gemäss Reglement bzw. Ausschreibung der USKA einstellen.
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

Das Log muss innerhalb von 8 Tagen nach dem Contest bei der USKA sein.

1. **File → Export Cabrillo log …** wählen.
2. Die Angaben sind für den Swiss XMAS Contest vorausgefüllt. Ergänze beim ersten Mal Name, Adresse und E-Mail; sie bleiben gespeichert. An die E-Mail-Adresse geht die Empfangsbestätigung der USKA.
3. **Save** klicken. Als Dateiname ist dein Rufzeichen in «Dokumente» vorgeschlagen, z. B. `HB9BLA.cbr`; mit **Speichern** bestätigen.
4. Auf die Frage, ob das Log jetzt eingesendet werden soll, **«Jetzt an die USKA senden»** klicken.
5. Im Fenster «Log an die USKA senden» den Contest prüfen (er ist anhand des QSO-Datums vorgewählt), die Erklärung lesen und **«Ich gebe diese Erklärung ab»** ankreuzen.
6. **«Log senden»** klicken.

Am Ende meldet das Fenster «Die USKA hat dein Log … erhalten», und du bekommst eine Bestätigung mit dem Log im Anhang per E-Mail. Kommt sie nicht an, prüfe den Spam-Ordner.

Ein gespeichertes Log kannst du auch später einsenden: **File → Cabrillo-Log an die USKA senden …**. Wenn die direkte Einsendung nicht klappt, verwende die Webseite https://contestlog.uska.ch/submit.

## 6. Kompatibilität

| Situation | Ergebnis |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest mit Kantonsaustausch |
| WSJT-SWISS 3 ↔ WSJT-X | Normale QSOs funktionieren; Kantone werden falsch angezeigt |
| Normale FT4/FT8-QSOs ausserhalb des Contests | Wie mit WSJT-X; dafür «Special operating activity» ausschalten |
