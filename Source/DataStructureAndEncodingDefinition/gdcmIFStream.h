
#ifndef __gdcmIFStream_h
#define __gdcmIFStream_h

#include "gdcmIStream.h"

#include <fstream>
#include <iostream>
#include <assert.h>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IFStream : public IStream
{
public:
  IFStream () {}
  ~IFStream() { assert( !(InternalStream.is_open())); }

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

  std::streampos Tellg() { return InternalStream.tellg(); }

  IStream& Seekg( std::streamoff off, std::ios_base::seekdir dir ) { 
    //std::cerr << "off= " << off << std::endl;
    InternalStream.seekg(off,dir);
    return *this;
    }
  IStream& Read(char* s, std::streamsize n);
  IStream& Get(char c) { 
    return Read(&c,1);
  }

protected:
  // Store filename for later access
  std::string FileName;
  // The real internal class
  std::ifstream InternalStream;

private:
};

}

#endif //__gdcmIFStream_h

