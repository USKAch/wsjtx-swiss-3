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

Browsers and virus scanners may warn about an unfamiliar installer. Check that the download comes from the project's Releases page and matches the version you intended to install before keeping or running it.

- **Chrome:** click "Keep", or in "Downloads" choose "Keep dangerous file".
- **Edge:** "Keep" → "Show more" → "Keep anyway".

## 2. Installation

1. Run the installer.
2. If the warning "Windows protected your PC" (SmartScreen) appears, verify the source and version. **More info** shows further details; **Run anyway** continues installation if you choose to proceed.
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
2. Select **3.580 MHz (80 m)** or **7.055 MHz (40 m)** in the frequency dropdown. Both contest entries are labelled **Swiss**. Check the contest announcement before operating.
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

**New Call on Band** is enabled in the default highlighting scheme under **File → Settings → Colors**. It marks a callsign you have not worked on that band. Saved highlighting choices are retained when upgrading or importing settings; use **Reset Highlighting** or tick the option yourself if your existing profile has it disabled.

### Second contest day

The two digital contest days are separate contests with separate log submissions. You may work stations from the first day again on the second day.

If you start WSJT-SWISS 3 on a new day and the contest log still holds QSOs from an earlier day, the program asks:

- **"Export that log first"** – save the old log as a Cabrillo file (and submit it), then start with an empty log.
- **"Start a new contest log"** – start with an empty log right away.
- **"Keep the log"** – change nothing.

In every case the QSOs stay in your ADIF log file (`wsjtx_log.adi`).

## 5. Submitting the log

Submit within the deadline in the current contest rules.

1. Check **View → Contest log**, then choose **File → Submit log to USKA …**.
2. Review the current log's UTC date and your prefilled station details. The first time, add your name, address and email. These details are remembered. The callsign comes from **Settings → General**.
3. Click **Continue**. The program creates the Cabrillo file automatically and opens the submission window. You do not need to export a file or choose a folder first.
4. Check the QSO count, contest and confirmation email. For a December contest date, the matching digital contest is preselected when it is available. Otherwise select the correct contest.
5. Read the declaration, tick **I make this declaration**, and click **Submit log**.

At the end the window reports "USKA has received your log …", and you receive a confirmation with the log attached by email. If it does not arrive, check your spam folder.

An empty contest log cannot be submitted. If the portal reports warnings, review them before choosing **Submit anyway**; **Cancel** stops this attempt. Correct a rejected log in the application and start **Submit log to USKA** again to generate a fresh file.

Generated files are retained under **Cabrillo** in the WSJT-SWISS log directory, with a separate subfolder for every attempt. Open that directory with **File → Open log directory**. They can be used on the [USKA submission page](https://contestlog.uska.ch/submit) if direct submission fails. If the program says receipt is uncertain, check for the confirmation email before submitting again.

**File → Export Cabrillo log …** remains available for a separate backup. Review the details and click **Save**, then choose a `.cbr` filename. The save dialog starts in the WSJT-SWISS log directory and remembers the last successful export folder. After saving, **Submit to USKA now** submits that file; **Open submission page** opens the website; **Later** keeps the local copy without submitting.

## 6. Compatibility

| Situation | Result |
|---|---|
| WSJT-SWISS 3 ↔ WSJT-SWISS 3 | Contest with canton exchange |
| WSJT-SWISS 3 ↔ WSJT-X | Normal QSOs work; cantons are shown incorrectly |
| Normal FT4/FT8 QSOs outside the contest | As with WSJT-X; switch off "Special operating activity" for them |

## 7. Windows and screenshots

The [window reference](Window-reference.md) describes setup prompts, every Settings tab, contest logging, submission, export, additional displays and maintenance dialogs, with screenshots. Start with the contest workflow above; the reference also explains windows that are not needed for this contest.
