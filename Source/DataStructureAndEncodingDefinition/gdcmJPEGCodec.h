#ifndef __gdcmJPEGcodec_h
#define __gdcmJPEGcodec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class JPEGInternals;
class JPEGCodec : public Codec
{
public:
  JPEGCodec();
  ~JPEGCodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);
private:
  JPEGInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmJPEGcodec_h
