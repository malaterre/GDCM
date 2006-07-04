#include "gdcmRAWCodec.h"
#include "gdcmTS.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"
#include "gdcmByteSwap.txx"


namespace gdcm
{

class RAWInternals
{
public:
};

RAWCodec::RAWCodec()
{
  Internals = new RAWInternals;
}

RAWCodec::~RAWCodec()
{
  delete Internals;
}

bool RAWCodec::CanDecode(TS const &ts)
{
  return TS::IsRAW(ts);
}

bool RAWCodec::Decode(IStream &is, OStream &os)
{
  // FIXME: Do some stupid work:
  is.Seekg( 0, std::ios::end);
  std::streampos buf_size = is.Tellg();
  char *dummy_buffer = new char[buf_size];
  is.Seekg(0, std::ios::beg);
  is.Read( dummy_buffer, buf_size);
  SwapCode sc = is.GetSwapCode();
  if( sc == SwapCode::BigEndian )
    {
    //MR_GE_with_Private_Compressed_Icon_0009_1110.dcm
    ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
      dummy_buffer, SwapCode::BigEndian, buf_size/2);
    }
  os.Write(dummy_buffer, buf_size);
  return true;
}

} // end namespace gdcm
