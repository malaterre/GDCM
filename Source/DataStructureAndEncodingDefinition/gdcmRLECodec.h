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

  void SetLength(unsigned long l)
    {
    Length = l;
    }
private:
  RLEInternals *Internals;
  unsigned long Length;
};

} // end namespace gdcm

#endif //__gdcmRLEcodec_h
