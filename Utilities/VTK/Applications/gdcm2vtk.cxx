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
  writer->Write();

  writer->Delete();
  imgreader->Delete();

  return 0;
}

