#include "gdcmJPEG2000Codec.h"
#include "gdcmTS.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"

namespace gdcm
{

class JPEG2000Internals
{
public:
};

JPEG2000Codec::JPEG2000Codec()
{
  Internals = new JPEG2000Internals;
}

JPEG2000Codec::~JPEG2000Codec()
{
  delete Internals;
}

bool JPEG2000Codec::CanDecode(TS const &ts)
{
  return ts.GetCompressionType() == Compression::JPEG2000;
}

bool JPEG2000Codec::Decode(IStream &is, OStream &os)
{
  return true;
}

} // end namespace gdcm
