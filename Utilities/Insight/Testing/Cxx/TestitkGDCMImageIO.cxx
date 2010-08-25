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
//#include "itkRescaleIntensityImageFilter.h"
#include "itkGDCMImageIO2.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"


#include "gdcmFilename.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmDirectory.h"

int TestitkGDCMImageIOFunc(const char *filename, bool verbose = false)
{
  if( verbose )
    std::cerr << "Reading : " << filename << std::endl;

  //Extract the series UID of the selected dicom image
  typedef itk::ImageIOBase::IOComponentType  ScalarPixelType;

  itk::GDCMImageIO2::Pointer imageIO = 
                                   itk::GDCMImageIO2::New();

  if( !imageIO )
    {
    std::cerr << "Failure generating GDCM image IO2 " << std::endl;
    return 1;
    }

  // Now that we found the appropriate ImageIO class, ask it to 
  // read the meta data from the image file.
  imageIO->SetFileName( filename );

  try
    {
    imageIO->ReadImageInformation();
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
    }

  ScalarPixelType pixelType = imageIO->GetComponentType();

  if ( verbose )
  std::cerr << pixelType << std::endl;

  return 0;
}

int TestitkGDCMImageIO(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestitkGDCMImageIOFunc(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  gdcm::Trace::ErrorOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestitkGDCMImageIOFunc( filename, false);
    ++i;
    }

  return r;
}
