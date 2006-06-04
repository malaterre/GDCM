
#ifndef __gdcmOStream_h
#define __gdcmOStream_h

#include "gdcmIOS.h"

namespace gdcm
{

/**
 * \brief Wrapper around ostream
 * \note bla
 */

class GDCM_EXPORT OStream : public IOS
{
public:
  OStream () {}
  ~OStream() {}

  void Open() { }
  void Close() { }

  operator void * ( ) const { assert(0); return 0; }
  std::streampos Tellp() { assert(0); return 0; }

  OStream& Seekp( std::streamoff , std::ios_base::seekdir ) { 
    assert(0);
    return *this;
    }
  OStream& Write(const char* , std::streamsize ) { assert(0); return *this; }

protected:
};

}

#endif //__gdcmIStream_h

