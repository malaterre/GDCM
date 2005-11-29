
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

/**
 * \brief Wrapper around ifstream
 * Should only provide wrapper around big endian stuff
 * Should not have any DICOM notion. See DICOMIStream for a specialization of IStream
 * \note bla
 */

#include "gdcmType.h"
#include <fstream>
#include <iostream>

namespace gdcm
{
class IStream
{
public:
  IStream () { SwapCode = SC::Unknown; }

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

  IStream& Seekg( std::streamoff off, std::ios_base::seekdir dir ) 
    { 
    //std::cerr << "off= " << off << std::endl;
    InternalStream.seekg(off,dir); return *this; }

protected:
  // Only subclass should have access to this method... this is too general
  // for end user
  IStream& Read(char* s, std::streamsize n);
  //IStream& Read(short* s, std::streamsize n);

  SC::SwapCodeType SwapCode;

private:
  std::string FileName;
  std::ifstream InternalStream;

};

}

#endif //__gdcmIStream_h
