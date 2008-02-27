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
#include "gdcmImageWriter.h"
#include "gdcmTrace.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmUIDGenerator.h"
#include "gdcmSystem.h"
#include "gdcmSpacingHelper.h"

namespace gdcm
{

ImageWriter::ImageWriter():PixelData()
{
}

ImageWriter::~ImageWriter()
{
}

void ImageWriter::SetImage(Image const &img)
{
  //assert( Stream.is_open() );
  const ImageValue &iv = dynamic_cast<const ImageValue&>( img );
  PixelData = iv;
  //assert( Stream.is_open() );
}

bool ImageWriter::Write()
{
  //assert( Stream.is_open() );
  File& file = GetFile();
  DataSet& ds = file.GetDataSet();

  // col & rows:
  Attribute<0x0028, 0x0011> columns;
  columns.SetValue( PixelData.GetDimension(0) );
  ds.Replace( columns.GetAsDataElement() );

  Attribute<0x0028, 0x0010> rows;
  rows.SetValue( PixelData.GetDimension(1) );
  ds.Replace( rows.GetAsDataElement() );

  // (0028,0008) IS [12]                                     #   2, 1 NumberOfFrames
  if( PixelData.GetNumberOfDimensions() == 3 )
    {
    Attribute<0x0028, 0x0008> numberofframes;
    assert( PixelData.GetDimension(2) > 1 );
    numberofframes.SetValue( PixelData.GetDimension(2) );
    ds.Replace( numberofframes.GetAsDataElement() );
    }

  PixelFormat pf = PixelData.GetPixelFormat();
  PhotometricInterpretation pi = PixelData.GetPhotometricInterpretation();
  // FIXME HACK !
  if( pi == PhotometricInterpretation::PALETTE_COLOR )
    {
    pi = PhotometricInterpretation::RGB;
    pf.SetSamplesPerPixel( 3 );
    }
  if( pf.GetBitsAllocated() == 24 )
    {
    pi = PhotometricInterpretation::RGB;
    pf.SetBitsAllocated( 8 );
    pf.SetBitsStored( 8 );
    pf.SetHighBit( 7 );
    pf.SetSamplesPerPixel( 3 );
    }
  // Pixel Format :
  // (0028,0100) US 8                                        #   2, 1 BitsAllocated
  // (0028,0101) US 8                                        #   2, 1 BitsStored
  // (0028,0102) US 7                                        #   2, 1 HighBit
  // (0028,0103) US 0                                        #   2, 1 PixelRepresentation
  Attribute<0x0028, 0x0100> bitsallocated;
  bitsallocated.SetValue( pf.GetBitsAllocated() );
  ds.Replace( bitsallocated.GetAsDataElement() );

  Attribute<0x0028, 0x0101> bitsstored;
  bitsstored.SetValue( pf.GetBitsStored() );
  ds.Replace( bitsstored.GetAsDataElement() );

  Attribute<0x0028, 0x0102> highbit;
  highbit.SetValue( pf.GetHighBit() );
  ds.Replace( highbit.GetAsDataElement() );

  Attribute<0x0028, 0x0103> pixelrepresentation;
  pixelrepresentation.SetValue( pf.GetPixelRepresentation() );
  ds.Replace( pixelrepresentation.GetAsDataElement() );

  Attribute<0x0028, 0x0002> samplesperpixel;
  samplesperpixel.SetValue( pf.GetSamplesPerPixel() );
  ds.Replace( samplesperpixel.GetAsDataElement() );

  // Pixel Data
  DataElement de( Tag(0x7fe0,0x0010) );
  const Value &v = PixelData.GetDataElement().GetValue();
  de.SetValue( v );
  const ByteValue *bv = de.GetByteValue();
  const TransferSyntax &ts = PixelData.GetTransferSyntax();
  assert( ts.IsExplicit() || ts.IsImplicit() );
  VL vl;
  if( bv )
    {
    // if ts is explicit -> set VR
    vl = bv->GetLength();
    }
  else
    {
    // if ts is explicit -> set VR
    vl.SetToUndefined();
    }
  //if( ts.IsExplicit() )
    {
    de.SetVR( VR::OB ); // OW ???
    }
  de.SetVL( vl );
  ds.Replace( de );
  // PhotometricInterpretation
  // const Tag tphotometricinterpretation(0x0028, 0x0004);
  if( !ds.FindDataElement( Tag(0x0028, 0x0004) ) )
    {
    const char *pistr = PhotometricInterpretation::GetPIString(pi);
    DataElement de( Tag(0x0028, 0x0004 ) );
    de.SetByteValue( pistr, strlen(pistr) );
    ds.Insert( de );
    if( pi == PhotometricInterpretation::RGB ) // FIXME
      {
      Attribute<0x0028, 0x0006> planarconfiguration;
      planarconfiguration.SetValue( PixelData.GetPlanarConfiguration() );
      ds.Replace( planarconfiguration.GetAsDataElement() );
      }
    }

  if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
    {
    MediaStorage ms = MediaStorage::SecondaryCaptureImageStorage;
    const char* msstr = MediaStorage::GetMSString(ms);
    DataElement de( Tag(0x0008, 0x0016 ) );
    de.SetByteValue( msstr, strlen(msstr) );
    ds.Insert( de );
    }

  // (re)Compute MediaStorage:
  MediaStorage ms;
  ms.SetFromDataSet( ds );
  if( !ds.FindDataElement( Tag(0x0008, 0x0060) ) )
    {
    const char *modality = ms.GetModality();
    DataElement de( Tag(0x0008, 0x0060 ) );
    de.SetByteValue( modality, strlen(modality) );
    ds.Insert( de );
    }
  else
    {
    const ByteValue *bv = ds.GetDataElement( Tag(0x0008, 0x0060 ) ).GetByteValue();
    std::string modality2 = std::string( bv->GetPointer(), bv->GetLength() );
    if( modality2 != ms.GetModality() )
      {
      DataElement de( Tag(0x0008, 0x0060 ) );
      de.SetByteValue( ms.GetModality(), strlen(ms.GetModality()) );
      ds.Replace( de );
      }
    }
  if( !ds.FindDataElement( Tag(0x0008, 0x0064) ) )
    {
    if( ms == MediaStorage::SecondaryCaptureImageStorage )
      {
      // (0008,0064) CS [SI]                                     #   2, 1 ConversionType
      const char conversion[] = "SI"; // FIXME
      DataElement de( Tag(0x0008, 0x0064 ) );
      de.SetByteValue( conversion, strlen(conversion) );
      ds.Insert( de );
      }
    }

  // Spacing:
  std::vector<double> sp;
  sp.resize(3); // important !
  sp[0] = PixelData.GetSpacing()[0];
  sp[1] = PixelData.GetSpacing()[1];
  sp[2] = PixelData.GetSpacing()[2]; // might be a dummy value...
  SpacingHelper::SetSpacingValue(ds, sp);

  // UIDs:
  // (0008,0018) UI [1.3.6.1.4.1.5962.1.1.1.1.3.20040826185059.5457] #  46, 1 SOPInstanceUID
  // (0020,000d) UI [1.3.6.1.4.1.5962.1.2.1.20040826185059.5457] #  42, 1 StudyInstanceUID
  // (0020,000e) UI [1.3.6.1.4.1.5962.1.3.1.1.20040826185059.5457] #  44, 1 SeriesInstanceUID
  UIDGenerator uid;

  // Be careful with the SOP Instance UID:
  if( ds.FindDataElement( Tag(0x0008, 0x0018) ) )
    {
    // We are comming from a real DICOM image, we need to reference it...
    assert( 0 && "TODO FIXME" );
    }
    {
    const char *sop = uid.Generate();
    DataElement de( Tag(0x0008,0x0018) );
    de.SetByteValue( sop, strlen(sop) );
    ds.Insert( de );
    }

  // Are we on a particular Study ? If not create a new UID
  if( !ds.FindDataElement( Tag(0x0020, 0x000d) ) )
    {
    const char *study = uid.Generate();
    DataElement de( Tag(0x0020,0x000d) );
    de.SetByteValue( study, strlen(study) );
    ds.Insert( de );
    }

  // Are we on a particular Series ? If not create a new UID
  if( !ds.FindDataElement( Tag(0x0020, 0x000e) ) )
    {
    const char *series = uid.Generate();
    DataElement de( Tag(0x0020,0x000e) );
    de.SetByteValue( series, strlen(series) );
    ds.Insert( de );
    }

  FileMetaInformation &fmi = file.GetHeader();

  //assert( ts == TransferSyntax::ImplicitVRLittleEndian );
    {
    const char *tsuid = TransferSyntax::GetTSString( ts );
    DataElement de( Tag(0x0002,0x0010) );
    de.SetByteValue( tsuid, strlen(tsuid) );
    fmi.Insert( de );
    fmi.SetDataSetTransferSyntax(ts);
    }
  fmi.FillFromDataSet( ds );

  // Some Type 2 Element:
  // PatientName
  if( !ds.FindDataElement( Tag(0x0010,0x0010) ) )
    {
    DataElement de( Tag(0x0010,0x0010) );
    ds.Insert( de );
    }
  // PatientID
  if( !ds.FindDataElement( Tag(0x0010,0x0020) ) )
    {
    DataElement de( Tag(0x0010,0x0020) );
    ds.Insert( de );
    }
  // PatientBirthDate
  if( !ds.FindDataElement( Tag(0x0010,0x0030) ) )
    {
    DataElement de( Tag(0x0010,0x0030) );
    ds.Insert( de );
    }
  // PatientSex
  if( !ds.FindDataElement( Tag(0x0010,0x0040) ) )
    {
    DataElement de( Tag(0x0010,0x0040) );
    ds.Insert( de );
    }
  // StudyDate
  char date[18];
  const size_t datelen = 8;
  int res = System::GetCurrentDateTime(date);
  assert( res );
  if( !ds.FindDataElement( Tag(0x0008,0x0020) ) )
    {
    DataElement de( Tag(0x0008,0x0020) );
    // Do not copy the whole cstring:
    de.SetByteValue( date, datelen );
    ds.Insert( de );
    }
  // StudyTime
  const size_t timelen = 6; // get rid of milliseconds
  if( !ds.FindDataElement( Tag(0x0008,0x0030) ) )
    {
    DataElement de( Tag(0x0008,0x0030) );
    // Do not copy the whole cstring:
    de.SetByteValue( date+datelen, timelen );
    ds.Insert( de );
    }
  // ReferringPhysicianName
  if( !ds.FindDataElement( Tag(0x0008,0x0090) ) )
    {
    DataElement de( Tag(0x0008,0x0090) );
    ds.Insert( de );
    }
  // StudyID
  if( !ds.FindDataElement( Tag(0x0020,0x0010) ) )
    {
    // FIXME: this one is actually bad since the value is needed for DICOMDIR construction
    DataElement de( Tag(0x0020,0x0010) );
    ds.Insert( de );
    }
  // AccessionNumber
  if( !ds.FindDataElement( Tag(0x0008,0x0050) ) )
    {
    DataElement de( Tag(0x0008,0x0050) );
    ds.Insert( de );
    }
  // SeriesNumber
  if( !ds.FindDataElement( Tag(0x0020,0x0011) ) )
    {
    DataElement de( Tag(0x0020,0x0011) );
    ds.Insert( de );
    }
  // InstanceNumber
  if( !ds.FindDataElement( Tag(0x0020,0x0013) ) )
    {
    DataElement de( Tag(0x0020,0x0013) );
    ds.Insert( de );
    }
  // Patient Orientation
  if( !ds.FindDataElement( Tag(0x0020,0x0020) ) )
    {
    DataElement de( Tag(0x0020,0x0020) );
    ds.Insert( de );
    }
  //const char dummy[] = "dummy";
  //assert( Stream.is_open() );
  //Stream << dummy;


  assert( Stream.is_open() );
  if( !Writer::Write() )
    {
    return false;
    }
  return true;
}

bool ImageWriter::WriteImage()
{
  return true;
}

//bool ImageWriter::WriteACRNEMAImage()
//{
//  return true;
//}

} // end namespace gdcm
