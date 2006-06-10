
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

//  IStream& Read(char* s, std::streamsize n) {
//    InternalStream.read(s,n);
//    return *this;
//  }
//  IStream& Get(char &c) {
//    InternalStream.get(c);
//    return *this;
//  }
//  OStream& Write(const char* s, std::streamsize n) {
//    InternalStream.write(s, n);
//    return *this;
//  }
//
//  StringStream& operator<<(const char *a) {
//    InternalStream << a;
//    return *this;
//  }
  std::string Str() const {
    std::stringbuf *sb = static_cast<std::stringbuf*>(Rdbuf());
    return sb->str();
  }

protected:
  // The real internal class
  //std::stringstream InternalStream;
};

}

#endif //__gdcmStringStream_h

