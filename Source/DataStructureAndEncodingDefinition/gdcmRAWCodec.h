#ifndef __gdcmRAWcodec_h
#define __gdcmRAWcodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class RAWInternals;
class RAWCodec : public Codec
{
public:
  RAWCodec();
  ~RAWCodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);

private:
  RAWInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmRAWcodec_h
