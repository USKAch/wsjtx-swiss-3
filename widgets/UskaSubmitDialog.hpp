#ifndef USKA_SUBMIT_DIALOG_HPP___
#define USKA_SUBMIT_DIALOG_HPP___

#include <QDate>
#include <QDialog>
#include <QString>

#include "pimpl_h.hpp"

//
// Submit a Cabrillo log to the USKA contest log portal
// (https://contestlog.uska.ch/submit) the way its web form does.
//
// The contest list comes from the portal itself, so only open contests
// can be chosen; the one matching the QSO date is preselected. The
// operator confirms the portal's declaration of compliance; nothing is
// submitted without it. Errors and warnings from the portal's log check
// are shown before the log is submitted.
//
class UskaSubmitDialog final
  : public QDialog
{
public:
  // portal_url e.g. https://contestlog.uska.ch/submit
  UskaSubmitDialog (QString const& portal_url, QString const& cabrillo_file
                    , QString const& callsign, QString const& email
                    , QDate const& qso_date, int qso_count, QWidget * parent = nullptr);
  ~UskaSubmitDialog ();

  // the email address as last entered
  QString email () const;

private:
  class impl;
  pimpl<impl> m_;
};

#endif
