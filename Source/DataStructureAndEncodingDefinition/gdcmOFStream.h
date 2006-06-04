
#ifndef __gdcmOFStream_h
#define __gdcmOFStream_h

#include "gdcmOStream.h"

#include <fstream>
#include <iostream>
#include <assert.h>

namespace gdcm
{

/**
 * \brief Wrapper around ofstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT OFStream : public OStream
{
public:
  OFStream ():SwapCodeValue(SwapCode::Unknown) {}
  ~OFStream() { assert( !(InternalStream.is_open())); }

  bool operator ! ( ) const { return !InternalStream; }
  bool eof ( ) const { return InternalStream.eof(); }
  // Although correct this is not defined by the standart
  //operator bool() const { return !InternalStream.eof(); }
  //define the void* operation so that while( IStream ) becomes a valid cast
  //defined cast/ user cast
  operator void * ( ) const { return static_cast<void*>(InternalStream); }

  // Filename operation are undirectional in the iostream standart (can 
  // only set them, not get them). Therefore deviate a little from 
  // std::istream
  void SetFileName(const std::string& filename) { FileName = filename; }
  std::string const &GetFileName() const { return FileName; }
  void Open() { 
    InternalStream.open(FileName.c_str(), std::ios::binary);
  }
  void Close() { InternalStream.close(); }

  std::streampos Tellp() { return InternalStream.tellp(); }

  OStream& Seekp( std::streamoff off, std::ios_base::seekdir dir ) { 
    //std::cerr << "off= " << off << std::endl;
    InternalStream.seekp(off,dir);
    return *this;
    }
  OStream& Write(const char* s, std::streamsize n);

protected:
  // Store filename for later access
  std::string FileName;
  // The real internal class
  std::ofstream InternalStream;

private:
};

}

#endif //__gdcmOFStream_h

