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

#include "vtkImageData.h"
#include "vtkMultiThreader.h"
#include "vtkMedicalImageProperties.h"

#include "gdcmTesting.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmImageReader.h"

int TestvtkGDCMImageWrite(const char *filename, bool verbose = false)
{
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  //reader->CanReadFile( filename );
  if( verbose )
    std::cerr << "Reading : " << filename << std::endl;
  reader->SetFileName( filename );
  reader->Update();
  if( verbose )
    {
    reader->GetOutput()->Print( cout );
    reader->GetMedicalImageProperties()->Print( cout );
    }

  // Create directory first:
  const char subdir[] = "TestvtkGDCMImageWriter";
  std::string tmpdir = gdcm::Testing::GetTempDirectory( subdir );
  if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
    {
    gdcm::System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string gdcmfile = gdcm::Testing::GetTempFilename( filename, subdir );

  vtkGDCMImageWriter *writer = vtkGDCMImageWriter::New();
  writer->SetInput( reader->GetOutput() );
  writer->SetDirectionCosines( reader->GetDirectionCosines() );
  writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
  writer->SetFileName( gdcmfile.c_str() );
  writer->Write();
  if( verbose )  std::cerr << "Write out: " << gdcmfile << std::endl;

  reader->Delete();
  writer->Delete();

  // Need to check we can still read this image back:
  gdcm::ImageReader r;
  r.SetFileName( gdcmfile.c_str() );
  if( !r.Read() )
    {
    return 1;
    }

  return 0; 
}

int TestvtkGDCMImageWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMImageWrite(filename, true);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestvtkGDCMImageWrite( filename );
    ++i;
    }

  return r;
}

