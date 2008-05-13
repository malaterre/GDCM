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
 * I do not know what the format is, just guessing from info found on the net:
 *
 * http://atonal.ucdavis.edu/matlab/fmri/spm5/spm_dicom_convert.m
 *
 */
#include "gdcmReader.h"
#include "gdcmImageWriter.h"
#include "gdcmCSAHeader.h"

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
    csa.Print( ds.GetDataElement( t1 ) );
    }
#if 0
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
#else

  int dims[2] = { 448, 448 };
  dims[0] /= 7;
  dims[1] /= 7;
  double spacing[2] = {1,1};

  // SliceThickness ??
 	const gdcm::CSAElement &csael4 = csa.GetCSAElementByName( "NumberOfImagesInMosaic" );
  std::cout << csael4 << std::endl;
  gdcm::Element<gdcm::VR::IS, gdcm::VM::VM1> el4;
  el4.Set( csael4.GetValue() );
  int numberOfImagesInMosaic = el4.GetValue();
  std::cout << "NumberOfImagesInMosaic:" << numberOfImagesInMosaic << std::endl;
#endif

  //const gdcm::DataElement & pixeldata = ds.GetDataElement( gdcm::Tag(0x7fe1,0x1010) );
  const gdcm::DataElement & pixeldata = ds.GetDataElement( gdcm::Tag(0x7fe0,0x0010) );
  const gdcm::VL &l = pixeldata.GetVL();
  const int p =  l / (dims[0] * dims[1]);
  std::cout << "VL:" << l << std::endl;
  std::cout << "pixel:" << p << std::endl;

  gdcm::ImageWriter writer;

  gdcm::ImageValue &image = dynamic_cast<gdcm::ImageValue&>(writer.GetImage());
  image.SetNumberOfDimensions( 2 ); // good default
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  image.SetSpacing(0, spacing[0] );
  image.SetSpacing(1, spacing[1] );
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::INT16; // bytepix = spm_type('int16','bits')/8;

  image.SetNumberOfDimensions( 3 );
  //image.SetDimension(2, p / pixeltype.GetPixelSize() );
  image.SetDimension(2, numberOfImagesInMosaic );

  gdcm::PhotometricInterpretation pi;
  pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  //pixeltype.SetSamplesPerPixel(  );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );

  image.SetDataElement( pixeldata );

  std::string outfilename = "outcsa.dcm";
  writer.SetFileName( outfilename.c_str() );
  if( !writer.Write() )
    {
    return 1;
    }

  return 0;
}
