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
#include "gdcmUID.h"

namespace gdcm
{

ImageWriter::ImageWriter()
{
}

ImageWriter::~ImageWriter()
{
}

void ImageWriter::SetImage(Image const &img)
{
  const ImageValue &iv = dynamic_cast<const ImageValue&>( img );
  PixelData = iv;
}

bool ImageWriter::Write()
{
  File& file = GetFile();
  DataSet& ds = file.GetDataSet();

  // col & rows:
  Attribute<0x0028, 0x0011> columns;
  columns.SetValue( PixelData.GetDimension(1) );
  ds.Replace( columns.GetAsDataElement() );

  Attribute<0x0028, 0x0010> rows;
  rows.SetValue( PixelData.GetDimension(0) );
  ds.Replace( rows.GetAsDataElement() );

  // Pixel Format :
  // (0028,0100) US 8                                        #   2, 1 BitsAllocated
  // (0028,0101) US 8                                        #   2, 1 BitsStored
  // (0028,0102) US 7                                        #   2, 1 HighBit
  // (0028,0103) US 0                                        #   2, 1 PixelRepresentation
  Attribute<0x0028, 0x0100> bitsallocated;
  bitsallocated.SetValue( PixelData.GetPixelFormat().GetBitsAllocated() );
  ds.Replace( bitsallocated.GetAsDataElement() );

  Attribute<0x0028, 0x0101> bitsstored;
  bitsstored.SetValue( PixelData.GetPixelFormat().GetBitsStored() );
  ds.Replace( bitsstored.GetAsDataElement() );

  Attribute<0x0028, 0x0102> highbit;
  highbit.SetValue( PixelData.GetPixelFormat().GetHighBit() );
  ds.Replace( highbit.GetAsDataElement() );

  Attribute<0x0028, 0x0103> pixelrepresentation;
  pixelrepresentation.SetValue( PixelData.GetPixelFormat().GetPixelRepresentation() );
  ds.Replace( pixelrepresentation.GetAsDataElement() );

  Attribute<0x0028, 0x0002> samplesperpixel;
  samplesperpixel.SetValue( PixelData.GetPixelFormat().GetSamplesPerPixel() );
  ds.Replace( samplesperpixel.GetAsDataElement() );

  // Pixel Data
  DataElement de( Tag(0x7fe0,0x0010) );
  const Value &v = PixelData.GetValue();
  de.SetValue( v );
  const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
  de.SetVL( bv->GetLength() );
  //assert( bv ); // For now...
  ds.Replace( de );
  // PhotometricInterpretation
  // const Tag tphotometricinterpretation(0x0028, 0x0004);
  const PhotometricInterpretation &pi = PixelData.GetPhotometricInterpretation();
  if( !ds.FindDataElement( Tag(0x0028, 0x0004) ) )
    {
    const char *pistr = PhotometricInterpretation::GetPIString(pi);
    DataElement de( Tag(0x0028, 0x0004 ) );
    de.SetByteValue( pistr, strlen(pistr) );
    ds.Insert( de );
    }

  if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
    {
    MediaStorage ms = MediaStorage::SecondaryCaptureImageStorage;
    const char* msstr = MediaStorage::GetMSString(ms);
    DataElement de( Tag(0x0008, 0x0016 ) );
    de.SetByteValue( msstr, strlen(msstr) );
    ds.Insert( de );

    const char *modality = ms.GetModality();
    DataElement de2( Tag(0x0008, 0x0060 ) );
    de2.SetByteValue( modality, strlen(modality) );
    ds.Insert( de2 );
    // (0008,0064) CS [SI]                                     #   2, 1 ConversionType
    const char conversion[] = "SI"; // FIXME
    DataElement de3( Tag(0x0008, 0x0064 ) );
    de3.SetByteValue( conversion, strlen(conversion) );
    ds.Insert( de3 );
    }

  // UIDs:
  // (0008,0018) UI [1.3.6.1.4.1.5962.1.1.1.1.3.20040826185059.5457] #  46, 1 SOPInstanceUID
  // (0020,000d) UI [1.3.6.1.4.1.5962.1.2.1.20040826185059.5457] #  42, 1 StudyInstanceUID
  // (0020,000e) UI [1.3.6.1.4.1.5962.1.3.1.1.20040826185059.5457] #  44, 1 SeriesInstanceUID
  UID uid;
    {
    const char *sop = uid.GenerateUniqueUID();
    DataElement de( Tag(0x0008,0x0018) );
    de.SetByteValue( sop, strlen(sop) );
    ds.Insert( de );
    }

    {
    const char *study = uid.GenerateUniqueUID();
    DataElement de( Tag(0x0020,0x000d) );
    de.SetByteValue( study, strlen(study) );
    ds.Insert( de );
    }

    {
    const char *series = uid.GenerateUniqueUID();
    DataElement de( Tag(0x0020,0x000e) );
    de.SetByteValue( series, strlen(series) );
    ds.Insert( de );
    }

  FileMetaInformation &fmi = file.GetHeader();

  // Set Transfer Syntax UID to default:
  TransferSyntax ts;
    {
    const char *tsuid = TransferSyntax::GetTSString( ts );
    DataElement de( Tag(0x0002,0x0010) );
    de.SetByteValue( tsuid, strlen(tsuid) );
    fmi.Insert( de );
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
  if( !ds.FindDataElement( Tag(0x0008,0x0020) ) )
    {
    DataElement de( Tag(0x0008,0x0020) );
    ds.Insert( de );
    }
  // StudyTime
  if( !ds.FindDataElement( Tag(0x0008,0x0030) ) )
    {
    DataElement de( Tag(0x0008,0x0030) );
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
