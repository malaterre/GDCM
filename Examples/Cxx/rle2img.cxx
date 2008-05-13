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
/*
 * Special thanks to:
 * Mauro Maiorca for bringing to our attention on this new ELSCINT1 
 * compression algorithm : PMSCT_RLE1 (different from the 'LOSSLESS RICE')
 * See post at:
 * http://groups.google.com/group/comp.protocols.dicom/msg/f2b99bf706a7f8ca
 * 
 * Thanks to Jesús Spínola, for more datasets,
 * http://www.itk.org/pipermail/insight-users/2008-April/025571.html
 *
 * And last but not least, a very big thank to Ivo van Poorten, without
 * whom we would still be looking at this compressed byte stream as if
 * it was RLE compressed.
 */
#include "gdcmReader.h"
#include "gdcmPrivateTag.h"
#include "gdcmImageWriter.h"

void delta_decode(unsigned short *outbuffer, const char *inbuffer, size_t length, size_t outlength)
{
  unsigned short t = 0;
  size_t i;
  size_t j;
  for (i=0,j=0; i < length; ++i,++j)
    {
    if( inbuffer[i] == (0xa5-256) )
      {
      int repeat = inbuffer[i+1] + 1;
      int value = inbuffer[i+2];
      i+=2;
      for( int r = 0; r < repeat; ++r, ++j )
        {
        outbuffer[j] = value + t;
        t = outbuffer[j];
        }
      --j;
      }
    else if( inbuffer[i] == 0x5a )
      {
      unsigned char v1 = (unsigned char)inbuffer[i+1];
      unsigned char v2 = (unsigned char)inbuffer[i+2];
      outbuffer[j] = v2 * 256 + v1;
      t = outbuffer[j];
      i+=2;
      }
    else
      {
	      if( j < outlength / 2 ) // FIXME
	      {
      //assert( ((int)inbuffer[i] + (int)t) >= 0 );
      outbuffer[j] = (int)inbuffer[i] + (int)t;
      t = outbuffer[j];
	      }
      }
    }
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  // (07a1,1011) CS [PMSCT_RLE1]                                       # 10,1 Tamar Compression Type
  const gdcm::PrivateTag tcompressiontype(0x07a1,0x0011,"ELSCINT1");
  if( !ds.FindDataElement( tcompressiontype ) ) return 1;
  const gdcm::DataElement& compressiontype = ds.GetDataElement( tcompressiontype );
  if ( compressiontype.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = compressiontype.GetByteValue();
  std::string comp = "PMSCT_RLE1";
  if( strncmp( bv->GetPointer(), comp.c_str(), comp.size() ) != 0 ) return 1;
  
  const gdcm::PrivateTag tcompressedpixeldata(0x07a1,0x000a,"ELSCINT1");
  if( !ds.FindDataElement( tcompressedpixeldata) ) return 1;
  const gdcm::DataElement& compressionpixeldata = ds.GetDataElement( tcompressedpixeldata);
  if ( compressionpixeldata.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv2 = compressionpixeldata.GetByteValue();

  char *ref = new char [131072];
  memset(ref,0,131072);
  delta_decode((unsigned short *)ref, bv2->GetPointer(), bv2->GetLength(), 131072);

  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetVR( gdcm::VR::OB );
  pixeldata.SetByteValue( ref, 131072);
  delete[] ref;

  gdcm::ImageWriter writer;

  gdcm::ImageValue &image = dynamic_cast<gdcm::ImageValue&>(writer.GetImage());
  image.SetNumberOfDimensions( 2 ); // good default
  image.SetDimension(0, 256 );
  image.SetDimension(1, 256 );
  //image.SetSpacing(0, spacing[0] );
  //image.SetSpacing(1, spacing[1] );
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::INT16; // bytepix = spm_type('int16','bits')/8;

  image.SetNumberOfDimensions( 2 );
  //image.SetDimension(2, p / pixeltype.GetPixelSize() );
  //image.SetDimension(2, numberOfImagesInMosaic );

  gdcm::PhotometricInterpretation pi;
  pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  //pixeltype.SetSamplesPerPixel(  );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );

  image.SetDataElement( pixeldata );

  std::string outfilename = "outrle.dcm";
  writer.SetFileName( outfilename.c_str() );
  if( !writer.Write() )
    {
    return 1;
    }


  return 0;
}

