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
  return ts.GetCompressionType() == Compression::RAW;
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
    assert( !(buf_size % 2) );
    ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
      dummy_buffer, SwapCode::BigEndian, buf_size/2);
    }
  if( PlanarConfiguration )
    {
    // US-RGB-8-epicard.dcm
    //assert( image.GetNumberOfDimensions() == 3 );
    assert( !(buf_size % 3) );
    unsigned long size = buf_size/3;
    char *copy = new char[ buf_size ];
    memmove( copy, dummy_buffer, buf_size);

    const char *r = copy;
    const char *g = copy + size;
    const char *b = copy + size + size;

    char *p = dummy_buffer;
    for (unsigned long j = 0; j < size; ++j)
      {
      *(p++) = *(r++);
      *(p++) = *(g++);
      *(p++) = *(b++);
      }
    delete[] copy;
    }
  os.Write(dummy_buffer, buf_size);
  delete[] dummy_buffer;
  return true;
}

} // end namespace gdcm
