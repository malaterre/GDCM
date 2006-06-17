#include "gdcmImageValue.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"

namespace gdcm
{

template <class DEType>
const char *TemplateGetPointer(DataElement const &de)
{
  const DEType &xde =
    dynamic_cast<const DEType&>(de);
  const Value &v = xde.GetValue();
  // C++ would throw an exception when dynamic_cast to a reference
  // since you could not construct a ref from NULL
  // using good ol' pointer instead
  const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
  if(bv)
    {
    return bv->GetPointer();
    }

  return 0;
}

bool ImageValue::GetBuffer(char *buffer) const
{
  buffer = 0;
//  const Tag pixeldata = gdcm::Tag(0x7fe0, 0x0010);
//  const DataSet &ds = GetDataSet();
//  if( ds.FindDataElement( pixeldata ) )
//    {
//    const DataElement& de = ds.GetDataElement( pixeldata );
//    TS::NegociatedType type = ds.GetNegociatedType();
//    if( type == TS::Explicit )
//      {
//      const char *ibuffer = TemplateGetPointer<ExplicitDataElement>(de);
//      }
//    else if( type == TS::Implicit )
//      {
//      const char *ibuffer = TemplateGetPointer<ImplicitDataElement>(de);
//      }
//    else
//      {
//      gdcmErrorMacro( "Not sure how you are supposed to reach here" );
//      }
//    }
//  else
//    {
//    gdcmWarningMacro( "No Pixel Data Found" );
//    }

  return false;
}

} // end namespace gdcm

