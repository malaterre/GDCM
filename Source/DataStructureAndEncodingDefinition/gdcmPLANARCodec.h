#ifndef __gdcmPLANARcodec_h
#define __gdcmPLANARcodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class PLANARInternals;
class PLANARCodec : public Codec
{
public:
  PLANARCodec();
  ~PLANARCodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);

private:
  PLANARInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmPLANARcodec_h
