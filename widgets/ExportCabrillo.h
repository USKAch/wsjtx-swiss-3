// -*- Mode: C++ -*-
#ifndef EXPORTCABRILLO_H
#define EXPORTCABRILLO_H

#include <QDialog>
#include <QScopedPointer>

class QSettings;
class Configuration;
class CabrilloLog;
namespace Ui {
  class ExportCabrillo;
}

class ExportCabrillo final
  : public QDialog
{
  Q_OBJECT

public:
  explicit ExportCabrillo (QSettings *, Configuration const *
                           , CabrilloLog const *, QWidget * parent = nullptr);
  ~ExportCabrillo ();

  // the file written, empty unless the log was saved
  QString saved_file () const {return saved_file_;}

private:
  void read_settings();
  void write_settings();
  void apply_swiss_xmas_defaults ();
  QString default_file_name () const;
  void save_log ();

  QSettings * settings_;
  Configuration const * configuration_;
  CabrilloLog const * log_;
  QScopedPointer<Ui::ExportCabrillo> ui;
  QString saved_file_;
};

#endif
