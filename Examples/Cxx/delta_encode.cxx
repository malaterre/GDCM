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
 */
#include "gdcmReader.h"
#include "gdcmPrivateTag.h"
#include "gdcmImageWriter.h"

#include <iostream>
#include <iomanip>


void delta_encode(unsigned short *inbuffer, size_t length)
{
  std::vector<char> output;
  unsigned short prev = 0;
  //length = 100;
  // Do delta encoding:
  for(unsigned int i = 0; i < length; ++i)
  {
    //assert( output.size() == i );
    int diff = inbuffer[i] - prev;
    prev = inbuffer[i];
    char cdiff = (char)diff;
    //std::cout << std::hex << i << ":" << std::dec << diff << " - > " << std::hex << std::setfill( '0' ) << /*std::left <<*/ std::setw(2) << (short)cdiff << std::endl;
    //if( diff == (int)cdiff )
    if( diff <= 0x7f && diff >= -0x80 )
    {
       output.push_back( cdiff );
       //if( i == 0x5d ) std::cout << "Sp:" << std::setfill('0') << (int)output[i] << std::endl;
       //assert( output[i] == cdiff );
    }
    else
    {
    //std::cout << "Pb:     " <<   diff << std::endl;
       output.push_back( 'M' );
    }
  }
  // Do Run Length now:
  char prev0 = output[0];
  char prev1 = output[1];
  for(unsigned int i = 1; i < output.size(); ++i)
  {
    if( output[i] == prev1 && prev1 == prev0 ) 
    {
	    unsigned int j = 0; // nb repetition
	    while( output[i+j] == prev0 )
	    {
		    ++j;
	    }
	    ++j; // count cprev too
	    // in place:
    std::cout << "I:     " <<   i << std::endl;
	    output[i-2] = 0xa5;
	    output[i-2+1] = j;
	    output[i-2+2] = prev0;
	    output.erase( output.begin() + i, output.begin() + i - 2 + j);
	    if( j == 0xd2 )
	    {
		    //abort();
    std::cout << "HACK:     " <<   j << std::endl;
		    output.insert( output.begin() + i - 2, 2, 0xa5);
			    output[i-2+1] = 0x0;
	    }
    }
    prev0 = prev1;
    prev1 = output[i];
  }

  std::cout << output.size() << std::endl;
  std::ofstream out("comp.rle");
  out.write( &output[0], output.size() );
  out.close();
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];
	/*
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
*/

  std::ifstream i( filename );
  const unsigned int size = 131072;
  char *ref = new char [size];
  memset(ref,0,size);
  i.read( ref, size);
  i.close();
  delta_encode((unsigned short*)ref, size / 2);


  /*
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
  //writer.SetFile( reader.GetFile() );

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
    std::cerr << "Failed to write" << std::endl;
    return 1;
    }

    std::cout << "sucess !" << std::endl;
    */

  return 0;
}

