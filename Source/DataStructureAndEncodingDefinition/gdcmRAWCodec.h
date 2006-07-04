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

  unsigned int GetPlanarConfiguration() const
    {
    return PlanarConfiguration;
    }
  void SetPlanarConfiguration(unsigned int pc)
    {
    PlanarConfiguration = pc;
    }

private:
  RAWInternals *Internals;
  unsigned int PlanarConfiguration;
};

} // end namespace gdcm

#endif //__gdcmRAWcodec_h
