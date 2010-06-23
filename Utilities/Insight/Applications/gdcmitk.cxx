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
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkGDCMImageIO2.h"

int main( int argc, char* argv[] )
{
  if( argc < 5 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " DicomImage OutputDicomImage ";
    std::cerr << " OutputImage RescaleDicomImage\n";
    return EXIT_FAILURE;
    }

  typedef short InputPixelType;
  const unsigned int   InputDimension = 2;

  typedef itk::Image< InputPixelType, InputDimension > InputImageType;
  typedef itk::ImageFileReader< InputImageType > ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::GDCMImageIO2           ImageIOType;

  ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
  
  reader->SetImageIO( gdcmImageIO );
  try
    {
    reader->Update();
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << "exception in file reader " << std::endl;
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::ImageFileWriter< InputImageType >  Writer1Type;

  Writer1Type::Pointer writer1 = Writer1Type::New();

  writer1->SetFileName( argv[2] );
  writer1->SetInput( reader->GetOutput() );
  writer1->SetImageIO( gdcmImageIO );
  try
    {
    writer1->Update();
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << "exception in file writer " << std::endl;
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }
  typedef unsigned char WritePixelType;
  
  typedef itk::Image< WritePixelType, 2 > WriteImageType;
  
  typedef itk::RescaleIntensityImageFilter< 
               InputImageType, WriteImageType > RescaleFilterType;

  RescaleFilterType::Pointer rescaler = RescaleFilterType::New();

  rescaler->SetOutputMinimum(   0 );
  rescaler->SetOutputMaximum( 255 );
  typedef itk::ImageFileWriter< WriteImageType >  Writer2Type;

  Writer2Type::Pointer writer2 = Writer2Type::New();

  writer2->SetFileName( argv[3] );
 
  rescaler->SetInput( reader->GetOutput() );
  writer2->SetInput( rescaler->GetOutput() );


  try
    {
    writer2->Update();
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << "exception in file writer " << std::endl;
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::ImageFileWriter< WriteImageType >  Writer3Type;
  
  Writer3Type::Pointer writer3 = Writer3Type::New();

  writer3->SetFileName( argv[4] );
  writer3->SetInput( rescaler->GetOutput() );
  writer3->UseInputMetaDataDictionaryOff ();
  writer3->SetImageIO( gdcmImageIO );
  try
    {
    writer3->Update();
    }
  catch (itk::ExceptionObject & e)
    {
    std::cerr << "Exception in file writer " << std::endl;
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

