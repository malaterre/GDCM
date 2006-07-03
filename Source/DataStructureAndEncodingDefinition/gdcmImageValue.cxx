#include "gdcmImageValue.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmJPEGCodec.h"
#include "gdcmStringStream.h"

namespace gdcm
{

bool ImageValue::GetBuffer(char *buffer) const
{
  unsigned long len = GetBufferLength();
  Value *p = PixelData;
  const ByteValue *bv = dynamic_cast<ByteValue*>(p);
  if( bv )
    {
    if( len != bv->GetLength() )
      {
      gdcmWarningMacro( "Pixel Length " << bv->GetLength() <<
        " is different from computer value " << len );
      }
    bv->GetBuffer(buffer, len);
    //MR_GE_with_Private_Compressed_Icon_0009_1110.dcm
    //ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
    //  buffer, SwapCode::BigEndian, len);
    return true;
    }
  else
    {
    // Fragments...
    const SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(p);
    sf->GetBuffer(buffer, len);
//#define MDEBUG
#ifdef MDEBUG
    std::ofstream f("/tmp/debug.jpg");
    unsigned long totalLen = sf->ComputeLength();
    f.write(buffer, totalLen);
    f.close();
#endif
    JPEGCodec codec;
    StringStream is;
    is.Write(buffer, len);
    StringStream os;
    bool r = codec.Decode(is, os);
    memcpy(buffer, os.Str().c_str(), len);
    return r;
    }

  buffer = 0;
  return false;
}

} // end namespace gdcm

