/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageReader.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmElement.h"
#include "gdcmPhotometricInterpretation.h"
#include "gdcmTransferSyntax.h"
#include "gdcmLookupTable.h"
#include "gdcmAttribute.h"
#include "gdcmSpacingHelper.h"

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
  const DataSet &ds = F->GetDataSet();
  const DataElement &de = ds.GetDataElement( tag );
  const Value &v = de.GetValue();
  const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
  return bv;
}

bool ImageReader::Read()
{
  if( !Reader::Read() )
    {
    return false;
    }

  const FileMetaInformation &header = F->GetHeader();
  const DataSet &ds = F->GetDataSet();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  // Need to set the type of image we are dealing with:
  PixelData.SetTransferSyntax( ts );

  bool res = false;
  /* Does it really make sense to check for Media Storage SOP Class UID?
   * I need then to check consistency with 0008 0016 Instance SOP Class UID
   * ... I don't think there is an end. 
   * I'd rather go the old way check a bunch of tags (From Image Plane
   * Module).
   */
  MediaStorage ms = header.GetMediaStorage();
  bool isImage = MediaStorage::IsImage( ms );
  if( isImage )
    {
    assert( ts != TransferSyntax::TS_END && ms != MediaStorage::MS_END );
    // Good it's the easy case. It's declared as an Image:
    gdcmDebugMacro( "Sweet ! Finally a good DICOM file !" );
    //PixelData.SetCompressionFromTransferSyntax( ts );
    res = ReadImage();
    }
  else
    {
    if( ms != MediaStorage::MS_END )
      {
      gdcmDebugMacro( "DICOM file is not an Image file but a : " <<
        MediaStorage::GetMSString(ms) << " SOP Class UID" );
      res = false;
      }
    else
      {
      // Too bad the media storage type was not recognized...
      // what should we do ?
      // Let's check 0008,0016:
      // D 0008|0016 [UI] [SOP Class UID] [1.2.840.10008.5.1.4.1.1.7 ]
      // ==> [Secondary Capture Image Storage]
      const Tag tsopclassuid(0x0008, 0x0016);
      if( ds.FindDataElement( tsopclassuid) )
        {
        const ByteValue *sopclassuid
          = GetPointerFromElement( tsopclassuid );
        std::string sopclassuid_str(
          sopclassuid->GetPointer(),
          sopclassuid->GetLength() );
        assert( sopclassuid_str.find( ' ' ) == std::string::npos );
        MediaStorage ms2 = MediaStorage::GetMSType(sopclassuid_str.c_str());
        bool isImage2 = MediaStorage::IsImage( ms2 );
        if( isImage2 )
          {
          gdcmDebugMacro( "After all it might be a DICOM file "
            "(Mallinckrodt-like)" );
          
    //PixelData.SetCompressionFromTransferSyntax( ts );
          //PixelData.SetCompressionType( Compression::RAW );
          res = ReadImage();
          }
        else
          {
          gdcmDebugMacro( "DICOM file is not an Image file but a : " <<
            MediaStorage::GetMSString(ms2) << " SOP Class UID" );
          res = false;
          }
        }
      else if( ts == TransferSyntax::ImplicitVRBigEndianACRNEMA || header.IsEmpty() )
        {
        // Those transfer syntax have a high probability of being ACR NEMA
        gdcmDebugMacro( "Looks like an ACR-NEMA file" );
        // Hopefully all ACR-NEMA are RAW:
        //PixelData.SetCompressionType( Compression::RAW );
        res = ReadACRNEMAImage();
        }
      else // there is a Unknown Media Storage Syntax
        {
        assert( ts != TransferSyntax::TS_END && ms == MediaStorage::MS_END );
        // god damit I don't know what to do...
        gdcmWarningMacro( "Attempting to read this file as a DICOM file"
          "\nDesperate attempt" );
        const Tag tpixeldata(0x7fe0, 0x0010);
        if( ds.FindDataElement( tpixeldata) )
          {
          // gdcm-CR-DCMTK-16-NonSamplePerPix.dcm
          // Someone defined the Transfer Syntax but I have no clue what
          // it is. Since there is Pixel Data element, let's try to read
          // that as a buggy DICOM Image file...
          //PixelData.SetCompressionType( Compression::RAW );
          res = ReadImage();
          }
        else
          {
          // Giving up
          abort();
          res = false;
          }
        }
      }
    }

  //if(res) PixelData.Print( std::cout );
  return res;
}

signed short ImageReader::ReadSSFromTag( Tag const &t, std::stringstream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::SS,VM::VM1> el;
  assert( bv->GetLength() == 2 );
  conversion = std::string(bv->GetPointer(), 2); 
  ss.clear();
  ss.str( conversion );
  el.Read( ss );
  return el.GetValue();
}

unsigned short ImageReader::ReadUSFromTag( Tag const &t, std::stringstream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::US,VM::VM1> el;
  assert( bv->GetLength() == 2 );
  conversion = std::string(bv->GetPointer(), 2); 
  ss.clear();
  ss.str( conversion );
  el.Read( ss );
  return el.GetValue();
}

int ImageReader::ReadISFromTag( Tag const &t, std::stringstream &ss,
  std::string &conversion )
{
  const ByteValue *bv = GetPointerFromElement(t);
  Element<VR::IS,VM::VM1> el;
  conversion = std::string(bv->GetPointer(), bv->GetLength());
  assert( conversion.size() == bv->GetLength() );
  const char *debug = conversion.c_str();
  assert( debug[bv->GetLength()] == '\0' ); 
  ss.clear();
  ss.str( conversion );
  el.Read( ss );
  int r = el.GetValue();
  return r;
}

void DoOverlays(const DataSet& ds, ImageValue& pixeldata)
{
  unsigned int numoverlays;
  if( (numoverlays = Overlay::GetNumberOfOverlays( ds )) )
    {
    pixeldata.SetNumberOfOverlays( numoverlays );

    Tag overlay(0x6000,0x0000);
    bool finished = false;
    unsigned int idxoverlays = 0;
    while( !finished )
      {
      const DataElement &de = ds.FindNextDataElement( overlay );
      // Are we done:
      if( de.GetTag().GetGroup() > 0x60FF ) // last possible overlay curve
        {
        finished = true;
        }
      else if( de.GetTag().IsPrivate() ) // GEMS owns some 0x6003
        {
        // Move on to the next public one:
        overlay.SetGroup( de.GetTag().GetGroup() + 1 );
        }
      else
        {
        // Yeah this is an overlay element
        Overlay &ov = pixeldata.GetOverlay(idxoverlays);
        ++idxoverlays; // move on to the next one
        overlay = de.GetTag();
        uint16_t currentoverlay = overlay.GetGroup();
        assert( !(currentoverlay % 2) ); // 0x6001 is not an overlay...
        // Now loop on all element from this current group:
        DataElement de2 = de;
        while( de2.GetTag().GetGroup() == currentoverlay )
          {
          ov.Update(de2);
          overlay.SetElement( de2.GetTag().GetElement() + 1 );
          de2 = ds.FindNextDataElement( overlay );
          // Next element:
          //overlay.SetElement( overlay.GetElement() + 1 );
          }
        // If we exit the loop we have pass the current overlay and potentially point to the next one:
        //overlay.SetElement( overlay.GetElement() + 1 );
        //ov.Print( std::cout );

        // Let's decode it:
        std::ostringstream unpack;
        ov.Decompress( unpack );
        std::string s = unpack.str();
        size_t l = s.size();
        // The following line will fail with images like XA_GE_JPEG_02_with_Overlays.dcm
        // since the overlays are stored in the unused bit of the PixelData
        if( !ov.IsEmpty() )
          {
          assert( unpack.str().size() == ov.GetRows() * ov.GetColumns() );
          }
        else
          {
          gdcmDebugMacro( "This image does not contains Overlay in the 0x60xx tags. "
            << "Instead the overlay is stored in the unused bit of the Pixel Data. "
            << "This is not supported right now"
            << std::endl );
          }
        }
      }
    //std::cout << "Num of Overlays: " << numoverlays << std::endl;
    assert( idxoverlays == numoverlays );
    }
}

bool ImageReader::ReadImage()
{
  const DataSet &ds = F->GetDataSet();
  TransferSyntax::NegociatedType type; // = ds.GetNegociatedType();
  std::stringstream ss;
  std::string conversion;

  const Tag trecognitioncode(0x0008,0x0010);
  if( ds.FindDataElement( trecognitioncode ) )
    {
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm
    // PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
    gdcmDebugMacro( "Mixture of ACR NEMA and DICOM file" );
    }

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  // D 0028|0008 [IS] [Number of Frames] [8 ]
  const Tag tnumberofframes = Tag(0x0028, 0x0008);
  if( ds.FindDataElement( tnumberofframes ) )
    {
    int numberofframes = ReadISFromTag( tnumberofframes, ss, conversion );
    assert( numberofframes != 0 );
    if( numberofframes > 1 )
      {
      PixelData.SetNumberOfDimensions(3);
      PixelData.SetDimension(2, numberofframes );
      }
    else
      {
      gdcmDebugMacro( "NumberOfFrames was specified with a value of: "
        << numberofframes );
      PixelData.SetNumberOfDimensions(2);
      }
    }
  else
    {
    gdcmDebugMacro( "Attempting a guess for the number of dimensions" ); // FIXME
    PixelData.SetNumberOfDimensions(2);
    }

 
  // 2. What are the col & rows:
  // D 0028|0011 [US] [Columns] [512]
  const Tag tcolumns(0x0028, 0x0011);
  if( ds.FindDataElement( tcolumns ) )
    {
    PixelData.SetDimension(0,
      ReadUSFromTag( tcolumns, ss, conversion ) );
    }
  else
    {
    // Pretty bad we really need this information. Should not 
    // happen in theory. Maybe papyrus files ??
    gdcmErrorMacro( "This should not happen !" );
    return false;
    }

  // D 0028|0010 [US] [Rows] [512]
  PixelData.SetDimension(1,
    ReadUSFromTag( Tag(0x0028, 0x0010), ss, conversion ) );

  // Dummy check
  const unsigned int *dims = PixelData.GetDimensions();
  if( dims[0] == 0 || dims[1] == 0 )
    {
    // PhilipsLosslessRice.dcm
    gdcmWarningMacro( "Image is empty" );
    return false;
    }

  // 3. Pixel Format ?
  PixelFormat pf;
  // D 0028|0002 [US] [Samples per Pixel] [1]
  const Tag samplesperpixel = Tag(0x0028, 0x0002);
  if( ds.FindDataElement( samplesperpixel ) )
    {
    pf.SetSamplesPerPixel(
      ReadUSFromTag( samplesperpixel, ss, conversion ) );
    }

  // D 0028|0100 [US] [Bits Allocated] [16]
  pf.SetBitsAllocated(
    ReadUSFromTag( Tag(0x0028, 0x0100), ss, conversion ) );

  // D 0028|0101 [US] [Bits Stored] [12]
  pf.SetBitsStored(
    ReadUSFromTag( Tag(0x0028, 0x0101), ss, conversion ) );

  // D 0028|0102 [US] [High Bit] [11]
  pf.SetHighBit(
    ReadUSFromTag( Tag(0x0028, 0x0102), ss, conversion ) );

  // D 0028|0103 [US] [Pixel Representation] [0]
  pf.SetPixelRepresentation(
    ReadUSFromTag( Tag(0x0028, 0x0103), ss, conversion ) );

  // Very important to set the PixelFormat here before PlanarConfiguration
  PixelData.SetPixelFormat( pf );

  // 4. Planar Configuration
  // D 0028|0006 [US] [Planar Configuration] [1]
  const Tag planarconfiguration = Tag(0x0028, 0x0006);
  if( ds.FindDataElement( planarconfiguration ) )
    {
    PixelData.SetPlanarConfiguration(
      ReadUSFromTag( planarconfiguration, ss, conversion ) );
    }

  // 4 1/2 Let's do Pixel Spacing
  std::vector<double> spacing = SpacingHelper::GetSpacingValue(ds);
  // FIXME: Only SC is allowed not to have spacing:
  if( !spacing.empty() )
    {
    assert( spacing.size() >= PixelData.GetNumberOfDimensions() ); // In MR, you can have a Z spacing, but store a 2D image
    PixelData.SetSpacing( &spacing[0] );
    if( spacing.size() > PixelData.GetNumberOfDimensions() ) // FIXME HACK
      {
      PixelData.SetSpacing(PixelData.GetNumberOfDimensions(), spacing[PixelData.GetNumberOfDimensions()] );
      }
    }
  // 4 2/3 Let's do Origin
  const Tag timagepositionpatient(0x0020, 0x0032);
  if( ds.FindDataElement( timagepositionpatient ) )
    {
    const DataElement& de = ds.GetDataElement( timagepositionpatient );
    Attribute<0x0020,0x0032> at;
    at.Set( de.GetValue() );
    PixelData.SetOrigin( 0, at.GetValue(0));
    PixelData.SetOrigin( 1, at.GetValue(1));
    PixelData.SetOrigin( 2, at.GetValue(2));
    }
  else
    {
    assert( 0 && "TODO" ); // technically should only happen in SC
    }
  const Tag timageorientationpatient(0x0020, 0x0037);
  if( ds.FindDataElement( timageorientationpatient ) )
    {
    const DataElement& de = ds.GetDataElement( timageorientationpatient );
    Attribute<0x0020,0x0037> at;
    at.Set( de.GetValue() );
    PixelData.SetDirectionCosines( 0, at.GetValue(0));
    PixelData.SetDirectionCosines( 1, at.GetValue(1));
    PixelData.SetDirectionCosines( 2, at.GetValue(2));
    PixelData.SetDirectionCosines( 3, at.GetValue(3));
    PixelData.SetDirectionCosines( 4, at.GetValue(4));
    PixelData.SetDirectionCosines( 5, at.GetValue(5));
    }
  else
    {
    assert( 0 && "TODO" ); // technically should only happen in SC
    }

  // 5. Photometric Interpretation
  // D 0028|0004 [CS] [Photometric Interpretation] [MONOCHROME2 ]
  const Tag tphotometricinterpretation(0x0028, 0x0004);
  const ByteValue *photometricinterpretation
    = GetPointerFromElement( tphotometricinterpretation );
  std::string photometricinterpretation_str(
    photometricinterpretation->GetPointer(),
    photometricinterpretation->GetLength() );
  PhotometricInterpretation pi(
    PhotometricInterpretation::GetPIType(
      photometricinterpretation_str.c_str()));
  assert( pi != PhotometricInterpretation::UNKNOW);
  PixelData.SetPhotometricInterpretation( pi );

  // Do the Palette Color:
  if ( pi == PhotometricInterpretation::PALETTE_COLOR )
    {
    SmartPointer<LookupTable> lut = new LookupTable;
    lut->Allocate( pf.GetBitsAllocated() );
    // for each red, green, blue:
    for(int i=0; i<3; ++i)
      {
      // (0028,1101) US 0\0\16
      // (0028,1102) US 0\0\16
      // (0028,1103) US 0\0\16
      const Tag tdescriptor(0x0028, (0x1101 + i));
      //const ByteValue &descriptor = GetPointerFromElement( tdescriptor );
      // Element<VR::US,VM::VM3> el_us3;
      // assert( descriptor->GetLength() == 6 );
      // std::string descriptor_str(
      //   descriptor->GetPointer(),
      //   descriptor->GetLength() );
      // ss.clear();
      // ss.str( descriptor_str );
      // el_us3.Read( ss );
      Element<VR::US,VM::VM3> el_us3;
      // Now pass the byte array to a DICOMizer:
      el_us3.Set( ds[tdescriptor].GetValue() );
      lut->InitializeLUT( LookupTable::LookupTableType(i),
        el_us3[0], el_us3[1], el_us3[2] );
      //el_us3.Print( std::cerr << std::endl );

      // (0028,1201) OW 
      // (0028,1202) OW
      // (0028,1203) OW 
      const Tag tlut(0x0028, (0x1201 + i));
      
      // Segmented LUT
      // (0028,1221) OW 
      // (0028,1222) OW
      // (0028,1223) OW 
      const Tag seglut(0x0028, (0x1221 + i));
      if( ds.FindDataElement( tlut ) )
        {
        const ByteValue *lut_raw = GetPointerFromElement( tlut );
        //std::string descriptor_str(
        //  descriptor_str->GetPointer(),
        //  descriptor_str->GetLength() );
        //std::cerr << descriptor_str << std::endl;
        // LookupTableType::RED == 0
        lut->SetLUT( LookupTable::LookupTableType(i),
          (unsigned char*)lut_raw->GetPointer(), lut_raw->GetLength() );
        //assert( pf.GetBitsAllocated() == el_us3.GetValue(2) );

        unsigned long check =
          (el_us3.GetValue(0) ? el_us3.GetValue(0) : 65536) 
          * el_us3.GetValue(2) / 8;
        assert( check == lut_raw->GetLength() );
        }
      else if( ds.FindDataElement( seglut ) )
        {
        gdcmWarningMacro( "TODO" ); abort();
        const ByteValue *lut_raw = GetPointerFromElement( seglut );
        lut->SetLUT( LookupTable::LookupTableType(i),
          (unsigned char*)lut_raw->GetPointer(), lut_raw->GetLength() );
        }
      else
        {
        abort();
        }
      }
    PixelData.SetLUT(*lut);
    }
  // TODO
  //assert( pi.GetSamplesPerPixel() == pf.GetSamplesPerPixel() );

  // 6. Do the Overlays if any
  DoOverlays(ds, PixelData);

  // 7. Do the PixelData
  const Tag pixeldata = Tag(0x7fe0, 0x0010);
  if( !ds.FindDataElement( pixeldata ) )
    {
    gdcmWarningMacro( "No Pixel Data Found" );
    return false;
    }
  const DataElement& xde = ds.GetDataElement( pixeldata );
#if 1
  //if( type == TS::Explicit )
    {
    if( xde.GetVR() == VR::OW )
      {
      // Need to byte swap
      assert( F->GetHeader().GetDataSetTransferSyntax() 
        != TransferSyntax::ImplicitVRBigEndianPrivateGE );
      bool need = false;
//      = 
//        ByteSwap<int>::SystemIsLittleEndian() &&
//        (Stream.GetSwapCode() != SwapCode::LittleEndian)
//     || ByteSwap<int>::SystemIsBigEndian() &&
//        (Stream.GetSwapCode() != SwapCode::BigEndian );
//      if( need )
//        {
//#ifdef GDCM_WORDS_BIGENDIAN
//      assert( ts.GetSwapCode() == SwapCode::LittleEndian );
//#else
//      assert( ts.GetSwapCode() == SwapCode::BigEndian );
//#endif
//        }
      PixelData.SetNeedByteSwap( need );
      }
    PixelData.SetValue( xde.GetValue() );
    }
//  else if( type == TS::Implicit )
//    {
//    TS ts = GetHeader().GetTransferSyntaxType();
//#ifdef GDCM_WORDS_BIGENDIAN
//    if( ts != TS::ImplicitVRBigEndianPrivateGE
//      && pf.GetBitsAllocated() == 16 )
//#else
//    if( ts == TS::ImplicitVRBigEndianPrivateGE
//      && pf.GetBitsAllocated() == 16 )
//#endif
//      {
//      // TS::ImplicitVRBigEndianPrivateGE is written in BigEndian except the
//      // image which is in LittleEndian
//      PixelData.SetNeedByteSwap( true );
//      }
//    const ImplicitDataElement &ide =
//      dynamic_cast<const ImplicitDataElement&>(pdde);
//    PixelData.SetValue( ide.GetValue() );
//    }
//  else
//    {
//    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
//    return false;
//    }
#endif

  // FIXME:
  // We should check that when PixelData is RAW that Col * Dim == PixelData.GetLength()

  return true;
}

bool ImageReader::ReadACRNEMAImage()
{
  const DataSet &ds = F->GetDataSet();
  TransferSyntax::NegociatedType type; // = ds.GetNegociatedType();
  std::stringstream ss;
  std::string conversion;
  // Construct a stringstream to mimic the reading from the file
  //ss.SetSwapCode( Stream.GetSwapCode() );
  //PixelData.SetSwapCode( Stream.GetSwapCode() );

  // Ok we have the dataset let's feed the Image (PixelData)
  // 1. First find how many dimensions there is:
  // D 0028|0005 [SS] [Image Dimensions (RET)] [2]
  const Tag timagedimensions = Tag(0x0028, 0x0005);
  if( ds.FindDataElement( timagedimensions ) )
    {
    const DataElement& de = ds.GetDataElement( timagedimensions );
    Attribute<0x0028,0x0005> at;
    at.Set( de.GetValue() );
    unsigned short imagedimensions = at.GetValue();
    assert( imagedimensions == ReadSSFromTag( timagedimensions, ss, conversion ) );
    if ( imagedimensions == 3 )
      {
      PixelData.SetNumberOfDimensions(3);
      // D 0028|0012 [US] [Planes] [262]
      const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0012) );
      Attribute<0x0028,0x0012> at;
      at.Set( de.GetValue() );
      PixelData.SetDimension(2, at.GetValue() );
      assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0012), ss, conversion ) );
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
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0011) );
    Attribute<0x0028,0x0011> at;
    at.Set( de.GetValue() );
    PixelData.SetDimension(0, at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0011), ss, conversion ) );
    }

  // D 0028|0010 [US] [Rows] [512]
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0010) );
    Attribute<0x0028,0x0010> at;
    at.Set( de.GetValue() );
    PixelData.SetDimension(1, at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0010), ss, conversion ) );
    }

  // This is the definition of an ACR NEMA image:
  // D 0008|0010 [LO] [Recognition Code (RET)] [ACR-NEMA 2.0]
  // LIBIDO compatible code:
  // D 0008|0010 [LO] [Recognition Code (RET)] [ACRNEMA_LIBIDO_1.1]
  const Tag trecognitioncode(0x0008,0x0010);
  if( ds.FindDataElement( trecognitioncode ) )
    {
    const ByteValue *libido = ds.GetDataElement(trecognitioncode).GetByteValue();
    assert( libido );
    std::string libido_str( libido->GetPointer(), libido->GetLength() );
    assert( libido_str != "CANRME_AILIBOD1_1." );
    if( libido_str == "ACRNEMA_LIBIDO_1.1" || libido_str == "ACRNEMA_LIBIDO_1.0" )
      {
      // Swap Columns & Rows
      // assert( PixelData.GetNumberOfDimensions() == 2 );
      const unsigned int *dims = PixelData.GetDimensions();
      unsigned int tmp = dims[0];
      PixelData.SetDimension(0, dims[1] );
      PixelData.SetDimension(1, tmp );
      }
    else
      {
      assert( libido_str == "ACR-NEMA 2.0"
           || libido_str == "ACR-NEMA 1.0" );
      }
    }
  else
    {
    gdcmWarningMacro(
      "Reading as ACR NEMA an image which does not look likes ACR NEMA" );
    // File: acc-max.dcm is it ACR or DICOM ?
    // abort();
    }

  // 3. Pixel Format ?
  PixelFormat pf;
  // D 0028|0100 [US] [Bits Allocated] [16]
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0100) );
    Attribute<0x0028,0x0100> at;
    at.Set( de.GetValue() );
    pf.SetBitsAllocated( at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0100), ss, conversion ) );
    }

  // D 0028|0101 [US] [Bits Stored] [12]
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0101) );
    Attribute<0x0028,0x0101> at;
    at.Set( de.GetValue() );
    pf.SetBitsStored( at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0101), ss, conversion ) );
    }

  // D 0028|0102 [US] [High Bit] [11]
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0102) );
    Attribute<0x0028,0x0102> at;
    at.Set( de.GetValue() );
    pf.SetHighBit( at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0102), ss, conversion ) );
    }

  // D 0028|0103 [US] [Pixel Representation] [0]
    {
    const DataElement& de = ds.GetDataElement( Tag(0x0028, 0x0103) );
    Attribute<0x0028,0x0103> at;
    at.Set( de.GetValue() );
    pf.SetPixelRepresentation( at.GetValue() );
    assert( at.GetValue() == ReadUSFromTag( Tag(0x0028, 0x0103), ss, conversion ) );
    }

  PixelData.SetPixelFormat( pf );

  // 4. Do the Overlays if any
  DoOverlays(ds, PixelData);

  // 4 1/2 Let's do Pixel Spacing
  const Tag tpixelspacing(0x0028, 0x0030);
  if( ds.FindDataElement( tpixelspacing ) )
    {
    const DataElement& de = ds.GetDataElement( tpixelspacing );
    Attribute<0x0028,0x0030> at;
    at.Set( de.GetValue() );
    PixelData.SetSpacing( 0, at.GetValue(0));
    PixelData.SetSpacing( 1, at.GetValue(1));
    }
  // 4 2/3 Let's do Origin
  const Tag timageposition(0x0020, 0x0030);
  if( ds.FindDataElement( timageposition) )
    {
    const DataElement& de = ds.GetDataElement( timageposition);
    Attribute<0x0020,0x0030> at;
    at.Set( de.GetValue() );
    PixelData.SetOrigin( 0, at.GetValue(0));
    PixelData.SetOrigin( 1, at.GetValue(1));
    PixelData.SetOrigin( 2, at.GetValue(2));
    }
  const Tag timageorientation(0x0020, 0x0035);
  if( ds.FindDataElement( timageorientation) )
    {
    const DataElement& de = ds.GetDataElement( timageorientation);
    Attribute<0x0020,0x0035> at;
    at.Set( de.GetValue() );
    PixelData.SetDirectionCosines( 0, at.GetValue(0));
    PixelData.SetDirectionCosines( 1, at.GetValue(1));
    PixelData.SetDirectionCosines( 2, at.GetValue(2));
    PixelData.SetDirectionCosines( 3, at.GetValue(3));
    PixelData.SetDirectionCosines( 4, at.GetValue(4));
    PixelData.SetDirectionCosines( 5, at.GetValue(5));
    }

  // 5. Do the PixelData
  const Tag pixeldata = Tag(0x7fe0, 0x0010);
  if( !ds.FindDataElement( pixeldata ) )
    {
    gdcmWarningMacro( "No Pixel Data Found" );
    return false;
    }
  const DataElement& de = ds.GetDataElement( pixeldata );
#if 1
  //if( type == TS::Explicit )
    {
    if ( de.GetVR() == VR::OW )
      {
      abort();
      PixelData.SetNeedByteSwap(true);
      }
    PixelData.SetValue( de.GetValue() );
    }
//  else if( type == TS::Implicit )
//    {
//    TS ts = GetHeader().GetTransferSyntaxType();
//#ifdef GDCM_WORDS_BIGENDIAN
//    if( ts != TS::ImplicitVRBigEndianACRNEMA
//      && pf.GetBitsAllocated() == 16 )
//#else
//    if( ts == TS::ImplicitVRBigEndianACRNEMA
//      && pf.GetBitsAllocated() == 16 )
//#endif
//      {
//#ifdef GDCM_WORDS_BIGENDIAN
//      assert( ts.GetSwapCode() == SwapCode::LittleEndian );
//#else
//      assert( ts.GetSwapCode() == SwapCode::BigEndian );
//#endif
//      PixelData.SetNeedByteSwap( true );
//      }
//    const ImplicitDataElement &ide =
//      dynamic_cast<const ImplicitDataElement&>(pdde);
//    PixelData.SetValue( ide.GetValue() );
//    }
//  else
//    {
//    gdcmErrorMacro( "Not sure how you are supposed to reach here" );
//    return false;
//    }
#endif

  // There is no such thing as Photometric Interpretation and 
  // Planar Configuration in ACR NEMA so let's default to something ...
  PixelData.SetPhotometricInterpretation(
    PhotometricInterpretation::MONOCHROME2 );
  PixelData.SetPlanarConfiguration(0);
  const Tag planarconfiguration = Tag(0x0028, 0x0006);
  assert( !ds.FindDataElement( planarconfiguration ) );
  const Tag tphotometricinterpretation(0x0028, 0x0004);
  // Some funny ACR NEMA file have PhotometricInterpretation ...
  if( ds.FindDataElement( tphotometricinterpretation ) )
    {
    const ByteValue *photometricinterpretation
      = ds.GetDataElement( tphotometricinterpretation ).GetByteValue();
    assert( photometricinterpretation );
    std::string photometricinterpretation_str(
      photometricinterpretation->GetPointer(),
      photometricinterpretation->GetLength() );
    PhotometricInterpretation pi(
      PhotometricInterpretation::GetPIType(
        photometricinterpretation_str.c_str()));
    assert( pi == PhotometricInterpretation::MONOCHROME2 );
    }

  return true;
}


} // end namespace gdcm
