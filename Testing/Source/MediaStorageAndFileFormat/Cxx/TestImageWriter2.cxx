/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageWriter.h"
#include "gdcmImageReader.h"
#include "gdcmImage.h"

int TestImageWriter2(int argc, char *argv[])
{
  gdcm::ImageReader reader;
  reader.SetFileName( argv[1] );
  reader.Read();

  const gdcm::Image &ir = reader.GetImage();

  gdcm::Image image;
  image.SetNumberOfDimensions( ir.GetNumberOfDimensions() );

  const unsigned int *dims = ir.GetDimensions();
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );

  const gdcm::PixelFormat &pixeltype = ir.GetPixelFormat();
  image.SetPixelFormat( pixeltype );

  const gdcm::PhotometricInterpretation &pi = ir.GetPhotometricInterpretation();
  image.SetPhotometricInterpretation( pi );

  unsigned long len = image.GetBufferLength();
  assert( len = ir.GetBufferLength() );
  std::vector<char> buffer;
  buffer.resize(len); // black image

  gdcm::ByteValue *bv = new gdcm::ByteValue(buffer);
  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetValue( *bv );
  image.SetDataElement( pixeldata );

  const char filename[] = "toto.dcm";
  gdcm::ImageWriter writer;
  writer.SetImage( image );
  writer.SetFileName( filename );

  gdcm::File& file = writer.GetFile();
  gdcm::DataSet& ds = file.GetDataSet();

    gdcm::DataElement de( gdcm::Tag(0x0010,0x0010) );
    const char s[] = "GDCM^Rocks";
    de.SetByteValue( s, strlen( s ) );
    ds.Insert( de );

  if( !writer.Write() )
    {
    return 1;
    }

  return 0;
}

