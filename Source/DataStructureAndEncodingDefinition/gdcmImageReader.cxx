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

const char* ImageReader::GetPointerFromElement(Tag const &tag)
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
    const char *str = bv->GetPointer();
    return str;
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
    const char *str = bv->GetPointer();
    return str;
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

unsigned short ImageReader::ReadUSFromTag( Tag const & t, StringStream &ss,
  std::string &conversion )
{
  const char *t_str = GetPointerFromElement(t);
  Element<VR::US,VM::VM1> el;
  conversion = std::string(t_str, 2);
  ss.Str( conversion );
  el.Read( ss );
  return el.GetValue();
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
  const Tag tnumberofframes = gdcm::Tag(0x0028, 0x0008);
  if( ds.FindDataElement( tnumberofframes ) )
    {
    const char *numberofframes_str = GetPointerFromElement(tnumberofframes);
    assert( numberofframes_str != "" );
    conversion = std::string(numberofframes_str);
    ss.Str( conversion );
    Element<VR::IS,VM::VM1> a; // numberofframes;
    a.Read( ss );
    int numberofframes = a.GetValue();
    assert( numberofframes != 0 );
    if( numberofframes > 1 )
      {
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
  pt.SetSamplesPerPixel(
    ReadUSFromTag( Tag(0x0028, 0x0002), ss, conversion ) );

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

  // 4. Do the Planar configuration
  // D 0028|0006 [US] [Planar Configuration] [1]
  PixelData.SetPlanarConfiguration(
    ReadUSFromTag( Tag(0x0028, 0x0006), ss, conversion ) );

  // 5. Do the PixelData
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

bool ImageReader::ReadACRNEMAImage()
{
  const DataSet &ds = GetDataSet();
  TS::NegociatedType type = ds.GetNegociatedType();

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  // D 0028|0005 [SS] [Image Dimensions (RET)] [2]
  const Tag timagedimensions = gdcm::Tag(0x0028, 0x0005);
  if( ds.FindDataElement( timagedimensions ) )
    {
    const char *imagedimensions_str = GetPointerFromElement(timagedimensions);
    const signed short *imagedimensions =
      reinterpret_cast<const signed short*>(imagedimensions_str);
    PixelData.SetNumberOfDimensions( *imagedimensions );
    }
  else
    {
    gdcmWarningMacro( "Attempting a guess for the number of dimensions" );
    PixelData.SetNumberOfDimensions( 2 );
    }
//#error US-MONO2-8-8x-execho.dcm 

  // 2. What are the col & rows:
  unsigned int dims[2];

  // D 0028|0011 [US] [Columns] [512]
  const Tag tcolumns = gdcm::Tag(0x0028, 0x0011);
  const char *columns_str = GetPointerFromElement(tcolumns);
  const unsigned short *columns =
    reinterpret_cast<const unsigned short*>(columns_str);
  dims[0] = *columns;

  // D 0028|0010 [US] [Rows] [512]
  const Tag trows = gdcm::Tag(0x0028, 0x0010);
  const char *rows_str = GetPointerFromElement(trows);
  const unsigned short *rows =
    reinterpret_cast<const unsigned short*>(rows_str);
  dims[1] = *rows;

  PixelData.SetDimensions( dims );

  // 3. Pixel Type ?
  PixelType pt;
  // D 0028|0100 [US] [Bits Allocated] [16]
  const Tag tbitsallocated = gdcm::Tag(0x0028, 0x0100);
  const char *bitsallocated_str = GetPointerFromElement(tbitsallocated);
  const unsigned short *bitsallocated =
    reinterpret_cast<const unsigned short*>(bitsallocated_str);
  pt.SetBitsAllocated( *bitsallocated );

  // D 0028|0101 [US] [Bits Stored] [12]
  const Tag tbitsstored = gdcm::Tag(0x0028, 0x0101);
  const char *bitsstored_str = GetPointerFromElement(tbitsstored);
  const unsigned short *bitsstored =
    reinterpret_cast<const unsigned short*>(bitsstored_str);
  pt.SetBitsStored( *bitsstored );

  // D 0028|0102 [US] [High Bit] [11]
  const Tag thighbit = gdcm::Tag(0x0028, 0x0102);
  const char *highbit_str = GetPointerFromElement(thighbit);
  const unsigned short *highbit =
    reinterpret_cast<const unsigned short*>(highbit_str);
  pt.SetHighBit( *highbit );

  // D 0028|0103 [US] [Pixel Representation] [0]
  const Tag tpixelrepresentation = gdcm::Tag(0x0028, 0x0103);
  const char *pixelrepresentation_str =
    GetPointerFromElement(tpixelrepresentation);
  const unsigned short *pixelrepresentation =
    reinterpret_cast<const unsigned short*>(pixelrepresentation_str);
  pt.SetPixelRepresentation( *pixelrepresentation );

  PixelData.SetPixelType( pt );

  // 4. Do the PixelData
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
