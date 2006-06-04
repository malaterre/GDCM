
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmIOS.h"

#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IStream : public IOS
{
public:
  IStream () {}
  ~IStream() {}

  void Open() { }
  void Close() {  }

  operator void * ( ) const { assert(0); return 0; }
  std::streampos Tellg() { 
    assert(0);
    return 0; }

  IStream& Seekg( std::streamoff , std::ios_base::seekdir ) { 
    assert(0);
    return *this;
    }
  IStream& Read(char* , std::streamsize ) { assert(0); return *this; }
  IStream& Get(char) { assert(0); return *this; }

protected:
};

}

#endif //__gdcmIStream_h

