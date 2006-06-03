
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmType.h"
#include "gdcmSwapCode.h"
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

class GDCM_EXPORT IStream
{
public:
  IStream ():SwapCodeValue(SwapCode::Unknown) {}
  ~IStream() { assert( !(InternalStream.is_open())); }

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

  std::streampos Tellg() { return InternalStream.tellg(); }

  IStream& Seekg( std::streamoff off, std::ios_base::seekdir dir ) { 
    //std::cerr << "off= " << off << std::endl;
    InternalStream.seekg(off,dir); return *this;
    }

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }
  std::string const &GetFileName() const { return FileName; }

protected:
  // Only subclass should have access to this method... this is too general
  // for end user
  IStream& Read(char* s, std::streamsize n);

  SwapCode SwapCodeValue;

private:
  std::string FileName;
  std::ifstream InternalStream;
};

}

#endif //__gdcmIStream_h

