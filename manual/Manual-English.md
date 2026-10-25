# WSJT-SWISS 3 – Manual

WSJT-SWISS 3 is an edition of [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) 3.0.2 for the USKA **Swiss XMAS Contest**. During a contest QSO, the stations exchange their canton, e.g. **ZH** or **BE**. WSJT-SWISS 3 logs the QSOs, creates the Cabrillo log and submits it directly to the USKA.

Contest rules: https://uska.ch/contest/schweizer-contest-kw/

**Important:**

- WSJT-SWISS 3 is installed **next to** your normal WSJT-X. Your WSJT-X and its settings are not changed.
- Callsigns with a suffix (/P, /M etc.) and callsigns with four letters after the digit (e.g. HB9HSLU) do not work in the contest.
- Only WSJT-SWISS 3 shows cantons correctly, so the stations you work also need WSJT-SWISS 3.

---

## 1. Download

The installer `wsjtx-…-win64.exe` is on the [Releases page](https://github.com/USKAch/wsjtx-swiss-3/releases).

Browsers and virus scanners sometimes block the download because the file is rarely downloaded. This is a false alarm.

- **Chrome:** click "Keep", or in "Downloads" choose "Keep dangerous file".
- **Edge:** "Keep" → "Show more" → "Keep anyway".

## 2. Installation

1. Run the installer.
2. If the warning "Windows protected your PC" (SmartScreen) appears, click **"More info"** and then **"Run anyway"**. The program is not signed with a commercial certificate, which is normal for open-source software.
3. WSJT-SWISS 3 is installed in `C:\WSJTX-SWISS3`. In the Start menu it is called **WSJT-SWISS 3**.

After the contest you can remove it under **Windows Settings → Apps** (uninstall "WSJT-SWISS 3").

## 3. First start

### Taking over settings

On the first start, WSJT-SWISS 3 asks whether it should search your PC for the settings of WSJT-X or an earlier WSJT-SWISS version. Nothing is searched or copied without your confirmation.

1. Click **"Search"**.
2. The list shows all settings found, with callsign, radio and the date they were last used. Below it you see the details of the selected entry, e.g. sound cards and file location.
3. Select the entry you use for your station and click **"Import selected"**.

The settings are copied for WSJT-SWISS 3; the original stays unchanged. Before transmitting, check the **Radio** and **Audio** tabs under **File → Settings**.

You can choose the language of the WSJT-SWISS windows (Deutsch, Français, Italiano, English) at the top of the window. It also applies to the other WSJT-SWISS messages. The rest of the WSJT-X interface is in English.

### Choosing your canton

Next, WSJT-SWISS 3 asks for your canton. It is sent with every contest QSO. You can change it later under **File → Settings → Advanced**.

The Swiss XMAS mode is already switched on (**File → Settings → Advanced → Special operating activity: Swiss XMAS**), and you call "CQ XMAS".

## 4. Operating

1. Under **Mode**, select **FT4**.
2. Set band and frequency according to the USKA rules and announcement.
3. Click **Enable Tx** to call CQ, or double-click a station to answer it.

The canton exchange happens automatically during the QSO:

```
Station A (ZH)                 Station B (BE)
──────────────────────────────────────────────
CQ XMAS HB9AAA JN47
                               HB9AAA HB9BBB 1A BE
HB9BBB HB9AAA R 1A ZH
                               HB9AAA HB9BBB RR73
```

The "1A" before the canton is part of the message format and has no meaning.

Completed QSOs are entered in the contest log automatically, with **599** and the canton as report (e.g. "599 BE"). You can see the contest log under **View → Contest log**.

### Second contest day

The two digital contest days are separate contests with separate log submissions. You may work stations from the first day again on the second day.

If you start WSJT-SWISS 3 on a new day and the contest log still holds QSOs from an earlier day, the program asks:

- **"Export that log first"** – save the old log as a Cabrillo file (and submit it), then start with an empty log.
- **"Start a new contest log"** – start with an empty log right away.
- **"Keep the log"** – change nothing.

In every case the QSOs stay in your ADIF log file (`wsjtx_log.adi`).

## 5. Submitting the log

The log must reach the USKA within 8 days after the contest.

1. Choose **File → Export Cabrillo log …**.
2. The fields are prefilled for the Swiss XMAS Contest. The first time, add your name, address and email; they are remembered. The USKA's confirmation of receipt goes to this email address.
3. Click **Save**. The suggested file name is your callsign in "Documents", e.g. `HB9BLA.cbr`; confirm with **Save**.
4. When asked whether to submit the log now, click **"Submit to USKA now"**.
5. In the window "Submit log to USKA", check the contest (it is preselected from the QSO date), read the declaration and tick **"I make this declaration"**.
6. Click **"Submit log"**.

At the end the window reports "USKA has received your log …", and you receive a confirmation with the log attached by email. If it does not arrive, check your spam folder.

You can also submit a saved log later: **File → Submit Cabrillo log to USKA …**. If direct submission does not work, use the web page https://contestlog.uska.ch/submit.

## 6. Compatibility

| Situation | Result |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest with canton exchange |
| WSJT-SWISS 3 ↔ WSJT-X | Normal QSOs work; cantons are shown incorrectly |
| Normal FT4/FT8 QSOs outside the contest | As with WSJT-X; switch off "Special operating activity" for them |
