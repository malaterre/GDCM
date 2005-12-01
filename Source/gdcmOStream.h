
#ifndef __gdcmOStream_h
#define __gdcmOStream_h

/**
 * \brief Wrapper around ofstream
 * \note bla
 */

#include "gdcmType.h"
#include <fstream>
#include <assert.h>


namespace gdcm
{
class OStream
{
public:
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
