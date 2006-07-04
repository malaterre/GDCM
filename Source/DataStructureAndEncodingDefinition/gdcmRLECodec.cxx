#include "gdcmRLECodec.h"
#include "gdcmTS.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"

namespace gdcm
{

class RLEInternals
{
public:
};

RLECodec::RLECodec()
{
  Internals = new RLEInternals;
}

RLECodec::~RLECodec()
{
  delete Internals;
}

bool RLECodec::CanDecode(TS const &ts)
{
  (void)ts;
  abort();
  return true;
}


bool RLECodec::Decode(IStream &is, OStream &os)
{
  // FIXME: Do some stupid work:
  is.Seekg( 0, std::ios::end);
  std::streampos buf_size = is.Tellg();
  char *dummy_buffer = new char[buf_size];
  is.Seekg(0, std::ios::beg);
  is.Read( dummy_buffer, buf_size);
  SwapCode sc = is.GetSwapCode();

  os.Write(dummy_buffer, buf_size);
  delete[] dummy_buffer;
  return true;
}

} // end namespace gdcm
