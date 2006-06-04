
#ifndef __gdcmOStream_h
#define __gdcmOStream_h

#include "gdcmIOS.h"

namespace gdcm
{

/**
 * \brief Wrapper around ostream
 * \note bla
 */

class GDCM_EXPORT OStream : virtual public IOS
{
public:
  OStream () {}
  virtual ~OStream() {}

  virtual void Open() { }
  virtual void Close() { }

  virtual operator void * ( ) const { assert(0); return 0; }
  virtual std::streampos Tellp() { assert(0); return 0; }

  virtual OStream& Seekp( std::streamoff , std::ios_base::seekdir ) { 
    assert(0);
    return *this;
    }
  virtual OStream& Write(const char* , std::streamsize ) { assert(0); return *this; }

protected:
};

}

#endif //__gdcmIStream_h

