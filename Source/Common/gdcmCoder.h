#ifndef __gdcmCoder_h
#define __gdcmCoder_h

#include "gdcmTypes.h"

namespace gdcm
{

class TS;
class IStream;
class OStream;
class Coder
{
public:
  virtual ~Coder() {}
  virtual bool CanCode(TS const &) { return false; }
  virtual bool Code(IStream &is, OStream &os) { return false; }
};

} // end namespace gdcm

#endif //__gdcmCoder_h
