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
#include "gdcmImageValue.h"

int TestImageWriter2(int argc, char *argv[])
{
  gdcm::ImageValue image;
  image.SetNumberOfDimensions( 2 );
  const int dims[2] = { 256 , 256 };
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::INT8;

  gdcm::PhotometricInterpretation pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  pixeltype.SetSamplesPerPixel( 1 );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );

  unsigned long len = image.GetBufferLength();
  std::vector<char> buffer;
  buffer.resize(len); // black image

  gdcm::ByteValue *bv = new gdcm::ByteValue(buffer);
  image.SetValue( *bv );

  const char filename[] = "toto.dcm";
  gdcm::ImageWriter writer;
  writer.SetFileName( filename );
  writer.SetImage( image );
  if( !writer.Write() )
    {
    return 1;
    }

  return 0;
}

