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
#include "vtkMedicalImageProperties.h"

#include "vtkPNGWriter.h"
#include "vtkImageData.h"
//#include <vtksys/SystemTools.hxx>

#include "gdcmFilename.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"

int TestvtkGDCMImageRead(const char *filename, bool verbose)
{
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;
  reader->SetFileName( filename );
  reader->Update();

  reader->GetOutput()->Print( cout );
  if( verbose ) reader->GetMedicalImageProperties()->Print( cout );

  if( verbose )
    {
    // Create directory first:
    const char subdir[] = "TestvtkGDCMImageReader";
    std::string tmpdir = gdcm::Testing::GetTempDirectory( subdir );
    if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
      {
      gdcm::System::MakeDirectory( tmpdir.c_str() );
      //return 1;
      }
    std::string pngfile = gdcm::Testing::GetTempFilename( filename, subdir );

    vtkPNGWriter *writer = vtkPNGWriter::New();
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
    writer->SetInputConnection( reader->GetOutputPort() );
#else
    writer->SetInput( reader->GetOutput() );
#endif
    pngfile += ".png";
    writer->SetFileName( pngfile.c_str() );
    writer->Write();
    writer->Delete();
    cout << "Wrote PNG output into:" << pngfile << std::endl;
    }

  reader->Delete();
  return 0; 
}

int TestvtkGDCMImageReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMImageRead(filename, true);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestvtkGDCMImageRead( filename, false );
    ++i;
    }

  return r;
}
