#include "gdcmImageReader.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmStringStream.h"
#include "gdcmElement.h"

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

const ByteValue* ImageReader::GetPointerFromElement(Tag const &tag) const
{
  const DataSet &ds = GetDataSet();
  TS::NegociatedType type = ds.GetNegociatedType();

  const DataElement& rde = ds.GetDataElement( tag );
  if( type == TS::Explicit )
    {
    const ExplicitDataElement &xde =
      dynamic_cast<const ExplicitDataElement&>(rde);
    const Value &v = xde.GetValue();
    const Value *pv = &v;
    const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
    return bv;
    }
  else if( type == TS::Implicit )
    {
    const ImplicitDataElement &ide =
      dynamic_cast<const ImplicitDataElement&>(rde);
    const Value &v = ide.GetValue();
    //const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
    // C++ would throw an exception when dynamic_cast to a reference
    // since you could not construct a ref from NULL
    // Using good ol' pointer instead
    const Value *pv = &v;
    const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
    return bv;
    }
  // ooops ?
    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
  return 0;
}

bool ImageReader::Read()
{
  if( !Reader::Read() )
    {
    return false;
    }

  const FileMetaInformation &header = GetHeader();
  TS::TSType ts = header.GetTSType();
  
  bool res;
  if( ts == TS::ImplicitVRBigEndianACRNEMA 
   || ts == TS::TS_END )
    {
    // do compatible code
    res = ReadACRNEMAImage();
    }
  else
    {
    // read true DICOM dataset
    res = ReadImage();
    }

  PixelData.Print( std::cout );
  return res;
}

signed short ImageReader::ReadSSFromTag( Tag const & t, StringStream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::SS,VM::VM1> el;
  assert( bv->GetLength() == 2 );
  conversion = std::string(bv->GetPointer(), 2); 
  ss.Str( conversion );
  el.Read( ss );
  return el.GetValue();
}

unsigned short ImageReader::ReadUSFromTag( Tag const & t, StringStream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::US,VM::VM1> el;
  assert( bv->GetLength() == 2 );
  conversion = std::string(bv->GetPointer(), 2); 
  ss.Str( conversion );
  el.Read( ss );
  return el.GetValue();
}

int ImageReader::ReadISFromTag( Tag const & t, StringStream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::IS,VM::VM1> el;
  conversion = std::string(bv->GetPointer(), bv->GetLength());
  ss.Str( conversion );
  el.Read( ss );
  int r = el.GetValue();
  return r;
}

bool ImageReader::ReadImage()
{
  const DataSet &ds = GetDataSet();
  TS::NegociatedType type = ds.GetNegociatedType();
  StringStream ss;
  std::string conversion;
  // Construct a stringstream to mimic the reading from the file
  ss.SetSwapCode( Stream.GetSwapCode() );

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  // D 0028|0008 [IS] [Number of Frames] [8 ]
  const Tag tnumberofframes = Tag(0x0028, 0x0008);
  if( ds.FindDataElement( tnumberofframes ) )
    {
    int numberofframes = ReadISFromTag( tnumberofframes, ss, conversion );
    assert( numberofframes != 0 );
    gdcmWarningMacro( "I did not check the Transfer Syntax" );
    if( numberofframes > 1 )
      {
      assert( numberofframes == 3 );
      PixelData.SetNumberOfDimensions(3);
      PixelData.SetDimensions(2, numberofframes );
      }
    else
      {
      PixelData.SetNumberOfDimensions(2);
      }
    }
  else
    {
    gdcmWarningMacro( "Attempting a guess for the number of dimensions" );
    PixelData.SetNumberOfDimensions(2);
    }

 
  // 2. What are the col & rows:
  // D 0028|0011 [US] [Columns] [512]
  PixelData.SetDimensions(0,
    ReadUSFromTag( Tag(0x0028, 0x0011), ss, conversion ) );

  // D 0028|0010 [US] [Rows] [512]
  PixelData.SetDimensions(1,
    ReadUSFromTag( Tag(0x0028, 0x0010), ss, conversion ) );

  // 3. Pixel Type ?
  PixelType pt;
  // D 0028|0002 [US] [Samples per Pixel] [1]
  const Tag samplesperpixel = Tag(0x0028, 0x0002);
  if( ds.FindDataElement( samplesperpixel ) )
    {
    pt.SetSamplesPerPixel(
      ReadUSFromTag( samplesperpixel, ss, conversion ) );
    }

  // D 0028|0100 [US] [Bits Allocated] [16]
  pt.SetBitsAllocated(
    ReadUSFromTag( Tag(0x0028, 0x0100), ss, conversion ) );

  // D 0028|0101 [US] [Bits Stored] [12]
  pt.SetBitsStored(
    ReadUSFromTag( Tag(0x0028, 0x0101), ss, conversion ) );

  // D 0028|0102 [US] [High Bit] [11]
  pt.SetHighBit(
    ReadUSFromTag( Tag(0x0028, 0x0102), ss, conversion ) );

  // D 0028|0103 [US] [Pixel Representation] [0]
  pt.SetPixelRepresentation(
    ReadUSFromTag( Tag(0x0028, 0x0103), ss, conversion ) );

  // Very important to set the PixelType here before PlanarConfiguration
  PixelData.SetPixelType( pt );

  // D 0028|0006 [US] [Planar Configuration] [1]
  const Tag planarconfiguration = Tag(0x0028, 0x0006);
  if( ds.FindDataElement( planarconfiguration ) )
    {
    PixelData.SetPlanarConfiguration(
      ReadUSFromTag( planarconfiguration, ss, conversion ) );
    }

  // 5. Do the PixelData
  const Tag pixeldata = Tag(0x7fe0, 0x0010);
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

bool ImageReader::ReadACRNEMAImage()
{
  const DataSet &ds = GetDataSet();
  TS::NegociatedType type = ds.GetNegociatedType();
  StringStream ss;
  std::string conversion;
  // Construct a stringstream to mimic the reading from the file
  ss.SetSwapCode( Stream.GetSwapCode() );

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  // D 0028|0005 [SS] [Image Dimensions (RET)] [2]
  const Tag timagedimensions = Tag(0x0028, 0x0005);
  if( ds.FindDataElement( timagedimensions ) )
    {
    int imagedimensions = ReadSSFromTag( timagedimensions, ss, conversion );
    if ( imagedimensions == 3 )
      {
      PixelData.SetNumberOfDimensions(3);
      // D 0028|0012 [US] [Planes] [262]
      PixelData.SetDimensions(2,
        ReadUSFromTag( Tag(0x0028, 0x0012), ss, conversion ) );
      }
    else if ( imagedimensions == 2 )
      {
      PixelData.SetNumberOfDimensions(2);
      }
    else
      {
      abort();
      }
    }
  else
    {
    gdcmWarningMacro( "Attempting a guess for the number of dimensions" );
    PixelData.SetNumberOfDimensions( 2 );
    }

  // 2. What are the col & rows:
  // D 0028|0011 [US] [Columns] [512]
  PixelData.SetDimensions(0,
    ReadUSFromTag( Tag(0x0028, 0x0011), ss, conversion ) );

  // D 0028|0010 [US] [Rows] [512]
  PixelData.SetDimensions(1,
    ReadUSFromTag( Tag(0x0028, 0x0010), ss, conversion ) );

  // 3. Pixel Type ?
  PixelType pt;
  // D 0028|0100 [US] [Bits Allocated] [16]
  pt.SetBitsAllocated(
    ReadUSFromTag( Tag(0x0028, 0x0100), ss, conversion ) );

  // D 0028|0101 [US] [Bits Stored] [12]
  pt.SetBitsStored(
    ReadUSFromTag( Tag(0x0028, 0x0101), ss, conversion ) );

  // D 0028|0102 [US] [High Bit] [11]
  pt.SetHighBit(
    ReadUSFromTag( Tag(0x0028, 0x0102), ss, conversion ) );

  // D 0028|0103 [US] [Pixel Representation] [0]
  pt.SetPixelRepresentation(
    ReadUSFromTag( Tag(0x0028, 0x0103), ss, conversion ) );

  PixelData.SetPixelType( pt );

  // 4. Do the PixelData
  const Tag pixeldata = Tag(0x7fe0, 0x0010);
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
