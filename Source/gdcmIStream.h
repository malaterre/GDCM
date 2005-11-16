
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

/**
 * \brief Wrapper around ifstream
 * \note bla
 */

#include "gdcmType.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmValue.h"
#include <fstream>

namespace gdcm
{
class IStream
{
public:
  bool operator ! ( ) const { return !InternalStream; }
  bool eof ( ) const { return InternalStream.eof(); }

  void SetFileName(const std::string& filename) { FileName = filename; }
  void Open() { InternalStream.open(FileName.c_str(), std::ios::binary);}
  void Close() { InternalStream.close(); }
  

  // Read a tag from the IStream
  IStream &Read(Tag &t);

  // Read a VR from the IStream
  IStream &Read(VR::VRType &t);

  // Read a uin16_t from the Stream
  IStream &Read(uint16_t &vl);

  // Read a uin32_t from the Stream
  IStream &Read(uint32_t &vl);

  // Read a Value from the Stream
  IStream &Read(Value &v, uint32_t length);

  // FIXME Should not be here
  IStream &ReadDICM();

private:
  std::string FileName;
  std::ifstream InternalStream;
};

}

#endif //__gdcmIStream_h
