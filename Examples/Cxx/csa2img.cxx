/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * I do not know what the format is, just guessing from info found on the net:
 *
 * http://atonal.ucdavis.edu/matlab/fmri/spm5/spm_dicom_convert.m
 *
 * This example is an attempt at understanding the format used by SIEMENS
 * their "SIEMENS CSA NON-IMAGE" DICOM file (1.3.12.2.1107.5.9.1)
 * 
 * Everything done in this code is for the sole purpose of writing interoperable 
 * software under Sect. 1201 (f) Reverse Engineering exception of the DMCA.
 * If you believe anything in this code violates any law or any of your rights, 
 * please contact us (gdcm-developers@lists.sourceforge.net) so that we can 
 * find a solution. 
 *
 */
#include "gdcmReader.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmCSAHeader.h"
#include "gdcmAttribute.h"
#include "gdcmPrivateTag.h"

#include <math.h>

/*
 *  gdcmSampleData/images_of_interest/MR-sonata-3D-as-Tile.dcm  
 */
bool reorganize_mosaic(const unsigned short *input, const unsigned int *inputdims, unsigned int square,
  const unsigned int *outputdims, unsigned short *output )
{
  for(unsigned x = 0; x < outputdims[0]; ++x)
    {
    for(unsigned y = 0; y < outputdims[1]; ++y)
      {
      for(unsigned z = 0; z < outputdims[2]; ++z)
        {
        output[ x + y*outputdims[0] + z*outputdims[0]*outputdims[1] ] = 
          input[ (x + z * outputdims[0]) + (y + (z/square)*outputdims[0])*inputdims[0] ];
        }
      }
    }
  return true;
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  // gdcmDataExtra/gdcmNonImageData/exCSA_Non-Image_Storage.dcm
  // PHANTOM.MR.CARDIO_COEUR_S_QUENCE_DE_REP_RAGE.9.257.2008.03.20.14.53.25.578125.43151705.IMA
  const char *filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::CSAHeader csa;
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
  //std::cout << t1 << std::endl;
  const gdcm::PrivateTag &t2 = csa.GetCSASeriesHeaderInfoTag();

  if( ds.FindDataElement( t1 ) )
    {
    csa.LoadFromDataElement( ds.GetDataElement( t1 ) );
    csa.Print( std::cout );
    }
  //const gdcm::Image &inputimage = reader.GetImage();
#if 1
  int dims[2];
  const gdcm::CSAElement &csael = csa.GetCSAElementByName( "Columns" );
  std::cout << csael << std::endl;
  const gdcm::ByteValue *bv = csael.GetByteValue();
  gdcm::Element<gdcm::VR::IS, gdcm::VM::VM1> el;
  el.Set( csael.GetValue() );
  dims[0] = el.GetValue();
  std::cout << "Columns:" << el.GetValue() << std::endl;

   const gdcm::CSAElement &csael2 = csa.GetCSAElementByName( "Rows" );
  std::cout << csael2 << std::endl;
  gdcm::Element<gdcm::VR::IS, gdcm::VM::VM1> el2;
  el2.Set( csael2.GetValue() );
  dims[1] = el2.GetValue();
  std::cout << "Rows:" << el2.GetValue() << std::endl;

   const gdcm::CSAElement &csael3 = csa.GetCSAElementByName( "PixelSpacing" );
  std::cout << csael3 << std::endl;
  gdcm::Element<gdcm::VR::DS, gdcm::VM::VM2> el3;
  el3.Set( csael3.GetValue() );
  double spacing[2];
  spacing[0] = el3.GetValue(0);
  spacing[1] = el3.GetValue(1);
  std::cout << "PixelSpacing:" << el3.GetValue() << "," << el3.GetValue(1) << std::endl;


  gdcm::ImageWriter writer;

  gdcm::Image &image = writer.GetImage();
  image.SetNumberOfDimensions( 2 ); // good default
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  image.SetSpacing(0, spacing[0] );
  image.SetSpacing(1, spacing[1] );
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::INT16; // bytepix = spm_type('int16','bits')/8;

  unsigned long l = image.GetBufferLength();
  const int p =  l / (dims[0] * dims[1]);

  //image.SetNumberOfDimensions( 3 );
  //image.SetDimension(2, p / pixeltype.GetPixelSize() );

  gdcm::PhotometricInterpretation pi;
  pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  //pixeltype.SetSamplesPerPixel(  );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );
  //image.SetIntercept( inputimage.GetIntercept() );
  //image.SetSlope( inputimage.GetSlope() );

  //gdcm::DataElement pixeldata( gdcm::Tag(0x7fe1,0x1010) );
  //pixeldata.SetByteValue( &outbuf[0], outbuf.size() );
  gdcm::PrivateTag csanonimaget(0x7fe1,0x10,"SIEMENS CSA NON-IMAGE");
  const gdcm::DataElement &pixeldata = ds.GetDataElement( csanonimaget );
  image.SetDataElement( pixeldata );

  std::string outfilename = "outcsa.dcm";
  //writer.SetFile( reader.GetFile() );
  writer.SetFileName( outfilename.c_str() );
  if( !writer.Write() )
    {
    std::cerr << "could not write: " << outfilename << std::endl;
    return 1;
    }

#else
  // The following is deprecated.
  // See gdcmconv --mosaic instead

  //int dims[2] = { 448, 448 };
  //dims[0] /= 7;
  //dims[1] /= 7;
    unsigned int dims[3] = {};
  //double spacing[2] = {1,1};
    {
    const gdcm::DataElement& de = ds.GetDataElement( gdcm::Tag(0x0028, 0x0011) );
    gdcm::Attribute<0x0028,0x0011> at;
    at.SetFromDataElement( de );
    //pixeldata.SetDimension(0, at.GetValue() );
    dims[0] = at.GetValue();
    }

    {
    const gdcm::DataElement& de = ds.GetDataElement( gdcm::Tag(0x0028, 0x0010) );
    gdcm::Attribute<0x0028,0x0010> at;
    at.SetFromDataElement( de );
    //pixeldata.SetDimension(1, at.GetValue() );
    dims[1] = at.GetValue();
    }


  // SliceThickness ??
   const gdcm::CSAElement &csael4 = csa.GetCSAElementByName( "NumberOfImagesInMosaic" );
  std::cout << csael4 << std::endl;
  gdcm::Element<gdcm::VR::IS, gdcm::VM::VM1> el4;
  el4.Set( csael4.GetValue() );
  int numberOfImagesInMosaic = el4.GetValue();

  unsigned int div = (unsigned int)ceil(sqrt( (double)numberOfImagesInMosaic ) );
  dims[0] /= div;
  dims[1] /= div;
  dims[2] = numberOfImagesInMosaic;

  std::cout << "NumberOfImagesInMosaic:" << numberOfImagesInMosaic << std::endl;
  const double *spacing = inputimage.GetSpacing();

  unsigned long l = inputimage.GetBufferLength();
  std::vector<char> buf;
  buf.resize(l);
  inputimage.GetBuffer( &buf[0] );
  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe1,0x1010) );

  std::vector<char> outbuf;
  outbuf.resize(l);
  //outbuf = buf;

  bool b = reorganize_mosaic((unsigned short*)&buf[0], inputimage.GetDimensions(), div, dims, (unsigned short*)&outbuf[0] );

  pixeldata.SetByteValue( &outbuf[0], outbuf.size() );
  //const gdcm::DataElement & pixeldata = ds.GetDataElement( gdcm::Tag(0x7fe1,0x1010) );
  //const gdcm::DataElement & pixeldata = ds.GetDataElement( gdcm::Tag(0x7fe0,0x0010) );
  //const gdcm::VL &l = pixeldata.GetVL();
  const int p =  l / (dims[0] * dims[1]);
  std::cout << "VL:" << l << std::endl;
  std::cout << "pixel:" << p << std::endl;


  gdcm::ImageWriter writer;

  gdcm::Image &image = writer.GetImage();
  image.SetNumberOfDimensions( 2 ); // good default
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  image.SetSpacing(0, spacing[0] );
  image.SetSpacing(1, spacing[1] );
  gdcm::PixelFormat pixeltype = inputimage.GetPixelFormat(); //gdcm::PixelFormat::INT16; // bytepix = spm_type('int16','bits')/8;

  image.SetNumberOfDimensions( 3 );
  //image.SetDimension(2, p / pixeltype.GetPixelSize() );
  image.SetDimension(2, numberOfImagesInMosaic );

  gdcm::PhotometricInterpretation pi;
  pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  //pixeltype.SetSamplesPerPixel(  );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );
  image.SetIntercept( inputimage.GetIntercept() );
  image.SetSlope( inputimage.GetSlope() );

  image.SetDataElement( pixeldata );

  std::string outfilename = "outcsa.dcm";
  //writer.SetFile( reader.GetFile() );
  writer.SetFileName( outfilename.c_str() );
  if( !writer.Write() )
    {
    std::cerr << "could not write: " << outfilename << std::endl;
    return 1;
    }
#endif

  return 0;
}
