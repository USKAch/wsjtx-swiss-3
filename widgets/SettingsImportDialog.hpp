#ifndef SETTINGS_IMPORT_DIALOG_HPP___
#define SETTINGS_IMPORT_DIALOG_HPP___

#include <QString>

//
// First-start settings import for WSJT-SWISS 3
//
// When the settings file target_ini does not exist yet, ask the
// operator whether to search this PC for the settings of WSJT-X (and
// its "--rig-name" profiles) or an earlier WSJT-SWISS. Each settings
// file found is listed with its location and the details an operator
// recognises (callsign, radio, sound card, last used). Nothing is
// searched or copied without the operator's confirmation, and the
// source files are only read, never changed.
//
void offer_settings_import (QString const& target_ini);

#endif
