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
#include "gdcmConfigure.h" // for GDCM_DATA_ROOT
#include "vtkGDCMReader.h"
#include "vtkGDCMWriter.h"

#include "vtkImageData.h"
#include <vtksys/SystemTools.hxx>

#include "gdcmDataImages.h"

int TestvtkGDCMWrite(const char *filename)
{
  vtkGDCMReader *reader = vtkGDCMReader::New();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;
  reader->SetFileName( filename );
  reader->Update();

  reader->GetOutput()->Print( cout );

  vtkGDCMWriter *writer = vtkGDCMWriter::New();
  writer->SetInputConnection( reader->GetOutputPort() );
  std::string gdcmfile = vtksys::SystemTools::GetFilenamePath( filename );
  gdcmfile = "/tmp/vtkdcm";
  gdcmfile += '/';
  gdcmfile += vtksys::SystemTools::GetFilenameWithoutExtension( filename );
  gdcmfile += ".dcm";
  writer->SetFileName( gdcmfile.c_str() );
  writer->Write();

  reader->Delete();
  writer->Delete();

  return 0; 
}

int TestvtkGDCMWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMWrite(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestvtkGDCMWrite( filename );
    ++i;
    }

  return r;
}

