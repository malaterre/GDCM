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

const Image& ImageReader::GetImage() const
{
  return PixelData;
}

//void ImageReader::SetImage(Image const &img)
//{
//  PixelData = img;
//}

template <class DEType>
const Value& TemplateGetPointer(DataElement const &de)
{
  const DEType &xde =
    dynamic_cast<const DEType&>(de);
  const Value &v = xde.GetValue();
  return v;
//  //const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
//  // C++ would throw an exception when dynamic_cast to a reference
//  // since you could not construct a ref from NULL
//  // Using good ol' pointer instead
//  const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
//  if(bv)
//    {
//    return bv->GetPointer();
//    }
//
//  return 0;
}

bool ImageReader::Read()
{
  if( !Reader::Read() )
    {
    return false;
    }

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. Do the PixelData
  const Tag pixeldata = gdcm::Tag(0x7fe0, 0x0010);
  const DataSet &ds = GetDataSet();
  if( !ds.FindDataElement( pixeldata ) )
    {
    gdcmWarningMacro( "No Pixel Data Found" );
    return false;
    }
  const DataElement& de = ds.GetDataElement( pixeldata );
  TS::NegociatedType type = ds.GetNegociatedType();
  if( type == TS::Explicit )
    {
    const ExplicitDataElement &xde =
      dynamic_cast<const ExplicitDataElement&>(de);
    PixelData.SetValue( xde.GetValue() );
    }
  else if( type == TS::Implicit )
    {
    const ImplicitDataElement &ide =
      dynamic_cast<const ImplicitDataElement&>(de);
    PixelData.SetValue( ide.GetValue() );
    }
  else
    {
    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
    return false;
    }

  return true;
}


} // end namespace gdcm
