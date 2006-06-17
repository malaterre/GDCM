#include "gdcmImageReader.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"

namespace gdcm
{
ImageReader::ImageReader()
{
}

ImageReader::~ImageReader()
{
}

const char *ImageReader::GetPointer() const
{
  const Tag pixeldata = gdcm::Tag(0x7fe0, 0x0010);
  const DataSet &ds = GetDataSet();
  if( ds.FindDataElement( pixeldata ) )
    {
    const DataElement& de = ds.GetDataElement( pixeldata );
    TS::NegociatedType type = ds.GetNegociatedType();
    if( type == TS::Explicit )
      {
      const ExplicitDataElement &xde =
        dynamic_cast<const ExplicitDataElement&>(de);
      const Value &v = xde.GetValue();
      // C++ would throw an exception when dynamic_cast to a reference
      // since you could not construct a ref from NULL
      // using good ol' pointer instead
      const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
      if(bv)
        return bv->GetPointer();
      else
        return 0;
      }
    else if( type == TS::Implicit )
      {
      const ImplicitDataElement &xde =
        dynamic_cast<const ImplicitDataElement&>(de);
      const Value &v = xde.GetValue();
      const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
      if(bv)
        return bv->GetPointer();
      else
        return 0;
      }
    else
      {
      gdcmErrorMacro( "Not sure how you are supposed to reach here" );
      }
    }
  else
    {
    gdcmWarningMacro( "No Pixel Data Found" );
    }
  return 0;
}

} // end namespace gdcm
