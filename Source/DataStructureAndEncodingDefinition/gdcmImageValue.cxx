#include "gdcmImageValue.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"

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
    return true;
    }
  else
    {
    // Fragments...
    abort();
    }

  buffer = 0;
  return false;
}

} // end namespace gdcm

