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
//#include <vtksys/SystemTools.hxx>

#include "gdcmTesting.h"
#include "gdcmFilename.h"

int TestvtkGDCMImageWrite(const char *filename)
{
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;
  reader->SetFileName( filename );
  reader->Update();
  reader->GetOutput()->Print( cout );
  reader->GetMedicalImageProperties()->Print( cout );

  vtkImageData *copy = vtkImageData::New();
  copy->DeepCopy( reader->GetOutput() );

  vtkGDCMImageWriter *writer = vtkGDCMImageWriter::New();
  writer->SetInput( reader->GetOutput() );
  //writer->SetInput( copy );
  writer->SetDirectionCosines( reader->GetDirectionCosines() );
  writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
  gdcm::Filename fn = filename;
  std::string gdcmfile; //= vtksys::SystemTools::GetFilenamePath( filename );
  gdcmfile = "/tmp/vtkdcm";
  gdcmfile += '/';
  //gdcmfile += vtksys::SystemTools::GetFilenameWithoutExtension( filename );
  gdcmfile += fn.GetName();
  gdcmfile += ".dcm";
  writer->SetFileName( gdcmfile.c_str() );
  writer->Write();
  std::cerr << "Write out: " << gdcmfile << std::endl;

  reader->Delete();
  writer->Delete();
  copy->Delete();

  return 0; 
}

int TestvtkGDCMImageWriter(int argc, char *argv[])
{
  //vtkMultiThreader::SetGlobalMaximumNumberOfThreads(1);
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMImageWrite(filename);
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

