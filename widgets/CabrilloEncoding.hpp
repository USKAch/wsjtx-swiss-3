#ifndef CABRILLO_ENCODING_HPP_
#define CABRILLO_ENCODING_HPP_

#include <QTextStream>

// Cabrillo logs are written as UTF-8 without a byte order mark. Qt 5's
// QTextStream otherwise uses the local code page, Windows-1252 on a
// Swiss PC, so a name or address with ä, ö, ü, é, è or à reached the
// USKA portal as single Latin-1 bytes and showed as "R?schlikon".
inline void use_cabrillo_encoding (QTextStream& stream)
{
  stream.setCodec ("UTF-8");
  stream.setGenerateByteOrderMark (false);
}

#endif
