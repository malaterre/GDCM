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

void delta_decode(unsigned short *outbuffer, const char *inbuffer, size_t length)
{
  std::vector<unsigned short> output;
  unsigned short delta = 0;
  for(size_t i = 0; i < length; ++i)
  {
   if( (unsigned char)inbuffer[i] == 0xa5 )
    {
      char repeat = inbuffer[i+1] + 1;
      char value  = inbuffer[i+2];
      if( (unsigned char)value == 0x5a )
      {
	//assert( repeat == 2 );
        std::cout << "5a v=" << std::hex << value << " " << (int)repeat << " " << 
		(int)value << " " << (int)inbuffer[i+3] << " " << std::dec << i <<  std::endl;
	//if( inbuffer[i+3] == 1 )
	//{
        //output.push_back( 0x015a );
	//}
	////i+=1;
	//delta = 0x015a;
      unsigned char v1 = (unsigned char)inbuffer[i+1];
      unsigned char v2 = (unsigned char)inbuffer[i+2];
      int value = v1 * 256 + v2;
	if( inbuffer[i+3] == 1 )
	{
		//std::cerr << value << " != " << 0x15A << std::endl;
		assert( 0x015A == value );
	}
	output.push_back( 0x0 /*value */);
	delta = value;

      i+=3; // 3 values treated at once
      }
      else
      {
      i+=2; // 2 values treated at once
      for( int r = 0; r < repeat; ++r )
        {
        int ivalue = (int)delta + (int)value;
        output.push_back( ivalue );
	delta = ivalue;
        }
      }
     }
    else if( inbuffer[i] == 0x5a )
    {
      unsigned char v1 = (unsigned char)inbuffer[i+1];
      unsigned char v2 = (unsigned char)inbuffer[i+2];
      i+=2; // 2 values treated at once
      if( v1 == 0xa5 )
      {
      int value = v2 * 256 + v1;
      //std::cout << "v=" << std::hex << value << " " << (int)v1 << " " << (int)v2 <<  " " << (int)inbuffer[i+1] <<" " << std::dec << output.size() << std::endl;
      if( v2 == 1 && inbuffer[i+1] == 1 )
        {
	i+=1;
        //int value = 0xFFFF;
        output.push_back( 0x0101 );
        delta = 0x0;
        }
      else
      {
	      //assert( v2 == 1 );
	      int value = 0xa5;
	      output.push_back( value );
	      delta = value;
      }
      }
      else
      {
      int value = v2 * 256 + v1;
      output.push_back( value );
      delta = value;
      }
    }
    else
    {
      //std::cout << delta << "," << (int)inbuffer[i] << std::endl;
      int value = (int)delta + (int)inbuffer[i];
      //std::cout << "value:" << value << std::endl;
      //assert( value <= 0xFFFF && value >= 0 );
      output.push_back( value );
      //assert( output.size() != 0x8890 / 2);
     delta = value;
    }
    //std::cout << output.size() << " from : " << std::hex << (int)inbuffer[i] << "(" << std::dec << i << ")" << std::endl;
  }

  if ( output.size() % 2 )
  {
	  output.resize( output.size() - 1 );
  }
  std::cout << length << " -> " << output.size() << std::endl;
  //std::ofstream out("decomp.raw");
  //out.write( (char*)&output[0], output.size() * 2 );
  //out.close();

  memcpy( outbuffer, &output[0], 256*256*2 /*output.size() * 2*/);

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
  delta_decode((unsigned short *)ref, bv2->GetPointer(), bv2->GetLength());

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
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::INT16;

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

  return 0;
}

