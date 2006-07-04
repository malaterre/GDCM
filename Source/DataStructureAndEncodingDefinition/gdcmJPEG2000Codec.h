#ifndef __gdcmJPEG2000codec_h
#define __gdcmJPEG2000codec_h

#include "gdcmCodec.h"

namespace gdcm
{
  
class JPEG2000Internals;
class JPEG2000Codec : public Codec
{
public:
  JPEG2000Codec();
  ~JPEG2000Codec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);
private:
  JPEG2000Internals *Internals;
};

} // end namespace gdcm

#endif //__gdcmJPEG2000codec_h
