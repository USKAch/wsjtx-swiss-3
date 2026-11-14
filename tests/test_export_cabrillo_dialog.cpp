#include <QtTest>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

#include "ui_ExportCabrillo.h"

class TestExportCabrilloDialog final : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void saveWaitsForSuccessfulGeneration ()
  {
    QDialog details;
    Ui::ExportCabrillo ui;
    ui.setupUi (&details);
    QSignalSpy accepted {&details, &QDialog::accepted};
    bool generated {false};
    QObject::connect (ui.buttonBox, &QDialogButtonBox::accepted, &details, [&] {
        if (generated) details.accept ();
      });

    // The form must not accept itself while a save is cancelled or fails.
    ui.buttonBox->button (QDialogButtonBox::Save)->click ();
    QCOMPARE (accepted.count (), 0);

    generated = true;
    ui.buttonBox->button (QDialogButtonBox::Save)->click ();
    QCOMPARE (accepted.count (), 1);
  }

  void cancelDoesNotAccept ()
  {
    QDialog details;
    Ui::ExportCabrillo ui;
    ui.setupUi (&details);
    QSignalSpy accepted {&details, &QDialog::accepted};
    QSignalSpy rejected {&details, &QDialog::rejected};
    ui.buttonBox->button (QDialogButtonBox::Cancel)->click ();
    QCOMPARE (accepted.count (), 0);
    QCOMPARE (rejected.count (), 1);
  }
};

QTEST_MAIN (TestExportCabrilloDialog)
#include "test_export_cabrillo_dialog.moc"
