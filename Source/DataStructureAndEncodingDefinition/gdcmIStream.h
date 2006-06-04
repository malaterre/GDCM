
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmType.h"
#include "gdcmSwapCode.h"

#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IStream
{
public:
  IStream ():SwapCodeValue(SwapCode::Unknown) {}
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

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }

protected:
  // SwapCode of the file once figured out (can be Unknown)
  SwapCode SwapCodeValue;
};

}

#endif //__gdcmIStream_h

