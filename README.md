# WSJT-SWISS 3

[![Build](https://github.com/USKAch/wsjtx-swiss-3/actions/workflows/build-swiss-windows.yml/badge.svg)](https://github.com/USKAch/wsjtx-swiss-3/actions/workflows/build-swiss-windows.yml) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?logo=windows)](https://github.com/USKAch/wsjtx-swiss-3/releases) [![WSJT-X](https://img.shields.io/badge/Based%20on-WSJT--X%203.0.2-green)](https://wsjt.sourceforge.io/wsjtx.html)

WSJT-SWISS 3 is an edition of [WSJT-X](https://wsjt.sourceforge.io/wsjtx.html) for the **Swiss XMAS Contest** of the USKA. During a contest QSO in FT4, the stations exchange their canton (ZH, BE, …). WSJT-SWISS 3 logs the QSOs, creates the Cabrillo log and submits it directly to the USKA log portal.

## Download

**Herunterladen · Télécharger · Scaricare · Download**

[![Download WSJT-SWISS 3 for Windows](https://img.shields.io/badge/Download-WSJT--SWISS%203.0.2--swiss2%20for%20Windows-0078D6?style=for-the-badge&logo=windows)](https://github.com/USKAch/wsjtx-swiss-3/releases/download/v3.0.2-swiss2/wsjtx-3.0.2-swiss2-win64.exe)

Click the button, then run the downloaded file `wsjtx-3.0.2-swiss2-win64.exe`. It installs to `C:\WSJTX-SWISS3`, next to a normal WSJT-X, which is not changed. The manuals below explain the installation step by step, including the SmartScreen warning. Older versions are on the [Releases page](https://github.com/USKAch/wsjtx-swiss-3/releases).

## Manuals

| Language | Manual |
|---|---|
| Deutsch | [Anleitung](manual/Anleitung-Deutsch.md) |
| Français | [Manuel](manual/Manuel-Francais.md) |
| Italiano | [Manuale](manual/Manuale-Italiano.md) |
| English | [Manual](manual/Manual-English.md) |

## What WSJT-SWISS 3 adds to WSJT-X

- **Canton exchange:** the contest messages carry the canton instead of an ARRL Field Day section, e.g. `HB9AAA HB9BBB 1A BE`. The 26 cantons replace the section table of the Field Day message (i3=0, n3=3), so only WSJT-SWISS 3 shows them correctly.
- **Swiss XMAS mode by default:** *File → Settings → Advanced → Special operating activity: Swiss XMAS*, with "CQ XMAS". The canton is chosen from a list.
- **Settings import:** on the first start, WSJT-SWISS 3 offers to copy the settings of an existing WSJT-X or WSJT-SWISS installation on the PC. Nothing is copied without the operator's confirmation.
- **Contest log:** QSOs are logged with "599 <canton>". Each of the two digital contest days starts with its own log.
- **Cabrillo export and submission:** the export is prefilled for the USKA (file named after the callsign, `CATEGORY-MODE: DIGI`). The log can then be submitted to [contestlog.uska.ch](https://contestlog.uska.ch/submit) from the program. The operator confirms the declaration, and the portal sends a confirmation email.
- **Languages:** the texts added by WSJT-SWISS are in German, French, Italian and English. The default follows the Windows language. The rest of the WSJT-X interface is in English.

## Building

Windows installers are built with GitHub Actions on MSYS2 UCRT64 (`.github/workflows/build-swiss-windows.yml`):

- **Test build:** *Actions → Build WSJT-SWISS Windows Installer → Run workflow*; the installer is attached to the run as an artifact.
- **Release:** push a tag `v<version>-swiss<n>`, e.g. `v3.0.2-swiss1`; the installer is published as a pre-release. Then update the download links in this README and in the four manuals to the new installer, because a pre-release has no permanent "latest" link.

The branch `original` holds the unchanged upstream WSJT-X 3.0.2; `master` holds the Swiss changes.

## Credits and license

- **WSJT-X** by Joe Taylor, K1JT, and the WSJT Development Team.
- **WSJT-SWISS** adaptation by HB9BLA for the USKA.

Licensed under the GNU General Public License v3.0, see [COPYING](COPYING). The original WSJT-X build notes are in [README](README).
