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
#include "vtkTIFFReader.h"

#include "gdcmFilename.h"

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    return 1;
    }
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();

  vtkImageReader2Factory* imgfactory = vtkImageReader2Factory::New();
  imgfactory->RegisterReader( reader );
  vtkImageReader2* imgreader =
    imgfactory->CreateImageReader2(filename);
  imgreader->SetFileName(filename);
  imgfactory->Delete(); 

  vtkGDCMImageWriter * writer = vtkGDCMImageWriter::New();
  writer->SetFileName( outfilename );
  writer->SetInput( imgreader->GetOutput() );

  gdcm::Filename fn( filename );

  if( vtkGDCMImageReader * reader = vtkGDCMImageReader::SafeDownCast(imgreader) )
    {
    writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
    }
  else if( vtkMINCImageReader *reader = vtkMINCImageReader::SafeDownCast( imgreader ) )
    {
    writer->SetDirectionCosines( reader->GetDirectionCosines() );
    //writer->GetMedicalImageProperties()->SetModality( "MR" );
    // the following does not work with VTKData/Data/t3_grid_0.mnc
    //writer->SetScale( reader->GetRescaleSlope() );
    //writer->SetShift( reader->GetRescaleIntercept() );
    reader->GetImageAttributes()->PrintFileHeader();
    }
  else if( vtkTIFFReader *reader = vtkTIFFReader::SafeDownCast( imgreader ) )
    {
    // TIFF has resolution (spacing), and VTK make sure to set set in mm
    // For some reason vtkTIFFReader is all skrew up and will load the image in whatever orientation
    // as stored on file, thus this is up to the user to set it properly...
    // If anyone has any clue why...
    reader->SetOrientationType( 4 );
    }

  writer->Write();

  imgreader->GetOutput()->Print( std::cout );

  writer->Delete();
  imgreader->Delete();
  reader->Delete();

  return 0;
}

