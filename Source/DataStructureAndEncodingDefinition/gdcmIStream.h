
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

class GDCM_EXPORT IStream : virtual public IOS
{
public:
  IStream () {}
  virtual ~IStream() {}

  virtual void Open() { }
  virtual void Close() {  }

  virtual operator void * ( ) const { assert(0); return 0; }
  virtual std::streampos Tellg() { 
    assert(0);
    return 0; }

  virtual IStream& Seekg( std::streamoff , std::ios_base::seekdir ) { 
    assert(0);
    return *this;
    }
  virtual IStream& Read(char* , std::streamsize ) { assert(0); return *this; }
  virtual IStream& Get(char&) { assert(0); return *this; }
  //virtual IStream& Read(uint16_t &vl);

protected:
};

}

#endif //__gdcmIStream_h

