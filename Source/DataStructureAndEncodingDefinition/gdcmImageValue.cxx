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
    memcpy(buffer, bv->GetPointer(), len);
    return true;
    }

  buffer = 0;
  return false;
}

} // end namespace gdcm

