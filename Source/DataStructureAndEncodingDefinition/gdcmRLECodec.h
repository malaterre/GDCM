#ifndef __gdcmRLEcodec_h
#define __gdcmRLEcodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class RLEInternals;
class RLECodec : public Codec
{
public:
  RLECodec();
  ~RLECodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);

private:
  RLEInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmRLEcodec_h
