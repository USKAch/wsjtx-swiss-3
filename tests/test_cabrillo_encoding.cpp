#include <QtTest>
#include <QBuffer>
#include <QTextCodec>
#include <QTextStream>

#include "widgets/CabrilloEncoding.hpp"

class TestCabrilloEncoding final : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void initTestCase ()
  {
    // A Swiss Windows PC: the local code page is Windows-1252, which
    // wrote "ü" as the single byte 0xFC before the fix.
    auto codec = QTextCodec::codecForName ("Windows-1252");
    QVERIFY (codec);
    QTextCodec::setCodecForLocale (codec);
  }

  void writesUmlautsAndAccentsAsUtf8 ()
  {
    QByteArray bytes;
    QBuffer buffer {&bytes};
    QVERIFY (buffer.open (QIODevice::WriteOnly));
    QTextStream out {&buffer};
    use_cabrillo_encoding (out);
    out << QString::fromUtf8 ("ADDRESS: 8803 Rüschlikon\n")
        << QString::fromUtf8 ("NAME: Zoé Müller-Lüthi, Genève, Città\n");
    out.flush ();
    QCOMPARE (bytes, QByteArray {"ADDRESS: 8803 R\xC3\xBCschlikon\n"
                                 "NAME: Zo\xC3\xA9 M\xC3\xBCller-L\xC3\xBCthi, Gen\xC3\xA8ve, Citt\xC3\xA0\n"});
  }

  void writesNoByteOrderMark ()
  {
    QByteArray bytes;
    QBuffer buffer {&bytes};
    QVERIFY (buffer.open (QIODevice::WriteOnly));
    QTextStream out {&buffer};
    use_cabrillo_encoding (out);
    out << "START-OF-LOG:3.0\n";
    out.flush ();
    QVERIFY (bytes.startsWith ("START-OF-LOG:3.0"));
  }
};

QTEST_GUILESS_MAIN (TestCabrilloEncoding)
#include "test_cabrillo_encoding.moc"
