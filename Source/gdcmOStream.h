
#ifndef __gdcmOStream_h
#define __gdcmOStream_h

/**
 * \brief Wrapper around ofstream
 * \note bla
 */

#include "gdcmType.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmValue.h"
#include <fstream>


namespace gdcm
{
class OStream
{
public:
  void SetFileName(const std::string& filename) { FileName = filename; }
  void Open() { InternalStream.open(FileName.c_str(), std::ios::binary);}
  void Close() { InternalStream.close(); }

  // Write a tag from the IStream
  OStream &Write(const Tag &t);

  // Write a VR from the IStream
  OStream &Write(const VR::VRType &t);

  // Write a uin16_t from the Stream
  OStream &Write(const uint16_t &vl);

  // Write a uin32_t from the Stream
  OStream &Write(const uint32_t &vl);

  // Write a Value from the Stream
  OStream &Write(const Value &v);

private:
  std::string FileName;
  std::ofstream InternalStream;
};

}

#endif //__gdcmOStream_h
