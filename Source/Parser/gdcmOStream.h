
#ifndef __gdcmOStream_h
#define __gdcmOStream_h


#include "gdcmType.h"
#include <fstream>
#include <assert.h>


namespace gdcm
{
/**
 * \brief Wrapper around ofstream
 * \note bla
 */

class GDCM_EXPORT OStream
{
public:
  bool operator ! ( ) const { return !InternalStream; }
  bool eof ( ) const { return InternalStream.eof(); }
  // Although correct this is not defined by the standart
  //operator bool() const { return !InternalStream.eof(); }
  //define the void* operation so that while( IStream ) becomes a valid cast
  //defined cast/ user cast
  operator void * ( ) const { return static_cast<void*>(InternalStream); }

  void SetFileName(const std::string& filename) { FileName = filename; }
  void Open() { InternalStream.open(FileName.c_str(), std::ios::binary);}
  void Close() { InternalStream.close(); }

protected:
  // Only subclass should have access to this method... this is too general
  // for end user
  OStream& Write(const char* s, std::streamsize n ) { 
    assert( !(!InternalStream) );
    InternalStream.write(s,n); return *this; }

private:
  std::string FileName;
  std::ofstream InternalStream;
};

}

#endif //__gdcmOStream_h
