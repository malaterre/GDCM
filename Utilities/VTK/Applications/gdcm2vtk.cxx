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
#include "vtkGDCMImageReader.h"
#include "vtkGDCMImageWriter.h"

#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"
#include "vtkImageData.h"
#include "vtkMINCImageReader.h"
#include "vtkMINCImageAttributes.h"
#include "vtkMedicalImageProperties.h"

#include "gdcmFilename.h"

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    return 1;
    }
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  vtkImageReader2Factory* imgfactory = vtkImageReader2Factory::New();
  vtkImageReader2* imgreader =
    imgfactory->CreateImageReader2(filename);
  imgreader->SetFileName(filename);
  imgfactory->Delete(); 

  vtkGDCMImageWriter * writer = vtkGDCMImageWriter::New();
  writer->SetFileName( outfilename );
  writer->SetInput( imgreader->GetOutput() );

  gdcm::Filename fn( filename );
  if( strcmp(fn.GetExtension(), ".mnc") == 0 )
    {
    //std::cout << "minc" << std::endl;
    vtkMINCImageReader *reader = vtkMINCImageReader::SafeDownCast( imgreader );
    writer->SetDirectionCosines( reader->GetDirectionCosines() );
    //writer->GetMedicalImageProperties()->SetModality( "MR" );
    writer->SetScale( reader->GetRescaleSlope() );
    writer->SetShift( reader->GetRescaleIntercept() );
    reader->GetImageAttributes()->PrintFileHeader();
    }

  writer->Write();

  imgreader->GetOutput()->Print( std::cout );

  writer->Delete();
  imgreader->Delete();

  return 0;
}

