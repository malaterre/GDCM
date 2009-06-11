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
#include "gdcmImage.h"
#include "gdcmImageWriter.h"
#include "gdcmFileDerivation.h"
//#include "gdcmImageChangePhotometricInterpretation.h"

int main(int, char *[])
{
  gdcm::SmartPointer<gdcm::Image> im = new gdcm::Image;

  char * buffer = new char[ 256 * 256 * 3];
  char * p = buffer;
  int b = 128;
        int ybr[3];
        int ybr2[3];
        int rgb[3];
  for(int r = 0; r < 256; ++r)
    for(int g = 0; g < 256; ++g)
      //for(int b = 0; b < 256; ++b)
        {
        rgb[0] = r;
        rgb[1] = g;
        rgb[1] = 128;
        rgb[2] = b;
        ybr[0] = r;
        ybr[1] = g;
        ybr[1] = 128;
        ybr[2] = b;

        ybr2[0] = r;
        ybr2[1] = g;
        ybr2[1] = 128;
        ybr2[2] = b;
        //gdcm::ImageChangePhotometricInterpretation::YBR2RGB(rgb, ybr);
        //gdcm::ImageChangePhotometricInterpretation::RGB2YBR(ybr2, rgb);
        *p++ = ybr2[0];
        *p++ = ybr2[1];
        *p++ = ybr2[2];
        }

  im->SetNumberOfDimensions( 2 );
  im->SetDimension(0, 256 );
  im->SetDimension(1, 256 );

  im->GetPixelFormat().SetSamplesPerPixel(3);
  //im->SetPhotometricInterpretation( gdcm::PhotometricInterpretation::RGB );
  im->SetPhotometricInterpretation( gdcm::PhotometricInterpretation::YBR_FULL );

  unsigned long l = im->GetBufferLength();
  if( l != 256 * 256 * 3 )
    {
    return 1;
    }
  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetByteValue( buffer, l );
  im->SetDataElement( pixeldata );

  gdcm::ImageWriter w;

  gdcm::FileDerivation fd;
  fd.AddReference( "1.2.3.4", "5.6.7.8" );
  fd.AddReference( "0.1.2.3.4", "0.5.6.7.8" );
  fd.SetDerivationCodeSequenceCodeValue( 113072 );
  fd.SetFile( w.GetFile() );
  if( !fd.Derive() )
    {
    return 1;
    }

  w.SetImage( *im );
  w.SetFileName( "ybr2.dcm" );
  //w.SetFileName( "rgb.dcm" );
  if( !w.Write() )
    {
    return 1;
    }

  return 0;
}
