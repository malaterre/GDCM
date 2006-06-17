#include "gdcmImageReader.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
//#include "gdcmElement.h"

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

  const DataSet &ds = GetDataSet();
  TS::NegociatedType type = ds.GetNegociatedType();
  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  PixelData.SetNumberOfDimensions(2); // FIXME
 
  // 2. What are the col & rows:
  unsigned int dims[3];
  dims[2] = 0; // FIXME
  // D 0028|0010 [US] [Rows] [512]
  const Tag trows = gdcm::Tag(0x0028, 0x0010);
  const DataElement& rde = ds.GetDataElement( trows );
  if( type == TS::Explicit )
    {
    abort();
    //const ExplicitDataElement &xde =
    //  dynamic_cast<const ExplicitDataElement&>(rde);
    //Value &v = xde.GetValue();
    }
  else if( type == TS::Implicit )
    {
    const ImplicitDataElement &ide =
      dynamic_cast<const ImplicitDataElement&>(rde);
    const Value &v = ide.GetValue();
    const Value *pv = &v;
    const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
    //Element<VR::US,VM::VM1> rows = 
    //  reinterpret_cast<unsigned short>(bv->GetPointer());
    const char *rows_str = bv->GetPointer();
    const unsigned short *rows =
      reinterpret_cast<const unsigned short*>(rows_str);
    dims[0] = *rows;
    }
  else
    {
    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
    return false;
    }
  // D 0028|0011 [US] [Columns] [512]
  const Tag tcolumns = gdcm::Tag(0x0028, 0x0011);
  const DataElement& cde = ds.GetDataElement( tcolumns );
  if( type == TS::Explicit )
    {
    abort();
    //const ExplicitDataElement &xde =
    //  dynamic_cast<const ExplicitDataElement&>(rde);
    //Value &v = xde.GetValue();
    }
  else if( type == TS::Implicit )
    {
    const ImplicitDataElement &ide =
      dynamic_cast<const ImplicitDataElement&>(cde);
    const Value &v = ide.GetValue();
    const Value *pv = &v;
    const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
    //Element<VR::US,VM::VM1> rows = 
    //  reinterpret_cast<unsigned short>(bv->GetPointer());
    const char *columns_str = bv->GetPointer();
    const unsigned short *columns =
      reinterpret_cast<const unsigned short*>(columns_str);
    dims[1] = *columns;
    }
  else
    {
    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
    return false;
    }
  PixelData.SetDimensions( dims );
  // 3. Do the PixelData
  const Tag pixeldata = gdcm::Tag(0x7fe0, 0x0010);
  if( !ds.FindDataElement( pixeldata ) )
    {
    gdcmWarningMacro( "No Pixel Data Found" );
    return false;
    }
  const DataElement& pdde = ds.GetDataElement( pixeldata );
  if( type == TS::Explicit )
    {
    const ExplicitDataElement &xde =
      dynamic_cast<const ExplicitDataElement&>(pdde);
    PixelData.SetValue( xde.GetValue() );
    }
  else if( type == TS::Implicit )
    {
    const ImplicitDataElement &ide =
      dynamic_cast<const ImplicitDataElement&>(pdde);
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
