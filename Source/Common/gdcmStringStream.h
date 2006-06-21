
#ifndef __gdcmStringStream_h
#define __gdcmStringStream_h

#include "gdcmIOStream.h"
#include <sstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT StringStream : public IOStream
{
public:
  explicit StringStream ();
  explicit StringStream (const std::string & str);
  ~StringStream() {}

  operator void * ( ) const { return InternalSStream; }

  IStream& Read(char* s, std::streamsize n) {
    InternalSStream.read(s,n);
    return *this;
  }
  IStream& Get(char &c) {
    InternalSStream.get(c);
    return *this;
  }
  OStream& Write(const char* s, std::streamsize n) {
    InternalSStream.write(s, n);
    return *this;
  }

  //StringStream& operator<<(const char *a) {
  //  InternalSStream << a;
  //  return *this;
  //}
  std::string Str() const {
    return InternalSStream.str();
  }
  void Str(std::string & s ) {
    InternalSStream.str(s);
  }

  //operator std::stringstream () const { return InternalSStream; }

protected:
  // The real internal class
  std::stringstream InternalSStream;
};

}

#endif //__gdcmStringStream_h

