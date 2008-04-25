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
#include "vtkStringArray.h"

#include "gdcmTesting.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmFilenameGenerator.h"
#include "gdcmImageReader.h"

#include <iostream>

#ifndef vtkFloatingPointType
#define vtkFloatingPointType float
#endif

int TestvtkGDCMImageWrite2(const char *filename, bool verbose = false)
{
  int res = 0; // no error
  if( verbose )
    std::cerr << "Reading : " << filename << std::endl;
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  reader->FileLowerLeftOn();
  int canread = reader->CanReadFile( filename );
  if( canread )
    {
    reader->SetFileName( filename );
    reader->Update();
    if( verbose )
      {
      reader->GetOutput()->Print( cout );
      reader->GetMedicalImageProperties()->Print( cout );
      }

    // Create directory first:
    const char subdir[] = "TestvtkGDCMImageWriter2";
    std::string tmpdir = gdcm::Testing::GetTempDirectory( subdir );
    if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
      {
      gdcm::System::MakeDirectory( tmpdir.c_str() );
      //return 1;
      }
    std::string gdcmfile = gdcm::Testing::GetTempFilename( filename, subdir );
    //std::cerr << filename << std::endl;
    //std::cerr << gdcmfile << std::endl;

    std::ostringstream os;
    os << gdcmfile;
    os << "%01d";
    gdcm::FilenameGenerator fg;
    //fg.SetPattern( gdcmfile.c_str() );
    fg.SetPattern( os.str().c_str() );
    unsigned int nfiles = reader->GetOutput()->GetDimensions()[2];
    fg.SetNumberOfFilenames( nfiles );
    bool b = fg.Generate();
    if( !b )
      {
      std::cerr << "FilenameGenerator::Generate() failed" << std::endl;
      return 1;
      }
    if( !fg.GetNumberOfFilenames() )
      {
      std::cerr << "FilenameGenerator::Generate() failed somehow..." << std::endl;
      return 1;
      }
    
    vtkGDCMImageWriter *writer = vtkGDCMImageWriter::New();
    writer->SetInput( reader->GetOutput() );
    writer->SetDirectionCosines( reader->GetDirectionCosines() );
    writer->SetImageFormat( reader->GetImageFormat() );
    writer->SetFileDimensionality( 2 ); // test the 3D to 2D writing mode
    writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
    //writer->SetFileName( gdcmfile.c_str() );
    vtkStringArray *filenames = vtkStringArray::New();
    for(unsigned int i = 0; i < fg.GetNumberOfFilenames(); ++i)
      {
      filenames->InsertNextValue( fg.GetFilename(i) );
      std::cerr << fg.GetFilename(i) << std::endl;
      }
    assert( filenames->GetNumberOfValues() == fg.GetNumberOfFilenames() );
    writer->SetFileNames( filenames );
    filenames->Delete();
    writer->Write();
    if( verbose )  std::cerr << "Write out: " << gdcmfile << std::endl;

    writer->Delete();

    // Need to check we can still read this image back:
    gdcm::ImageReader r;
    r.SetFileName( gdcmfile.c_str() );
    if( !r.Read() )
      {
      std::cerr << "failed to read back:" << gdcmfile << std::endl;
      res = 1;
      }
    else
    {
      // ok could read the file, now check origin is ok:
      const gdcm::Image &image = r.GetImage();
      const double *origin = image.GetOrigin();
      if( origin )
      {
      vtkImageData * vtkimg = reader->GetOutput();
      const vtkFloatingPointType *vtkorigin = vtkimg->GetOrigin();
      if( fabs(vtkorigin[0] - origin[0]) > 1.e-3 
       || fabs(vtkorigin[1] - origin[1]) > 1.e-3 
       || fabs(vtkorigin[2] - origin[2]) > 1.e-3 )
      {
         std::cerr << "Problem:" << vtkorigin[0] << "," << vtkorigin[1] << "," << vtkorigin[2] ;
         std::cerr << " should be:" << origin[0] << "," << origin[1] << "," << origin[2] << std::endl ;
      res = 1;
      }
      }
    }
    }
  else
    {
    if( verbose )
      std::cerr << "vtkGDCMImageReader cannot read: " << filename << std::endl;
    }
  reader->Delete();

  return res;
}

int TestvtkGDCMImageWriter2(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMImageWrite2(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestvtkGDCMImageWrite2( filename );
    ++i;
    }

  return r;
}

