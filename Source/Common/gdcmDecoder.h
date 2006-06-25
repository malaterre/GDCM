
#ifndef __gdcmDecoder_h
#define __gdcmDecoder_h

#include "gdcmTypes.h"

namespace gdcm
{
  
class TS;
class IStream;
class OStream;
class Decoder
{
public:
  virtual ~Decoder() {}
  virtual bool CanDecode(TS const &) { return false; }
  virtual bool Decode(IStream &is, OStream &os) { return false; }
};

} // end namespace gdcm

#endif //__gdcmDecoder_h
