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

  // Pixel Data
  DataElement de( Tag(0x7fe0,0x0010) );
  const Value &v = PixelData.GetValue();
  de.SetValue( v );
  const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
  de.SetVL( bv->GetLength() );
  //assert( bv ); // For now...
  ds.Replace( de );

  if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
    {
    MediaStorage ms = MediaStorage::SecondaryCaptureImageStorage;
    const char* msstr = MediaStorage::GetMSString(ms);
    DataElement de( Tag(0x0008, 0x0016 ) );
    de.SetByteValue( msstr, strlen(msstr) );
    ds.Insert( de );
    }

  FileMetaInformation &fmi = file.GetHeader();
  fmi.FillFromDataSet( ds );

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
