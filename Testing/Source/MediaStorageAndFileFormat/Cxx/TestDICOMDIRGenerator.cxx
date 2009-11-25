/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDICOMDIRGenerator.h"
#include "gdcmDirectory.h"
#include "gdcmTesting.h"

int TestDICOMDIRGenerator(int argc, char *argv[])
{
  (void)argc;
  const char *directory = gdcm::Testing::GetDataRoot();
  (void)argv;
  gdcm::DICOMDIRGenerator gen;

  gdcm::Directory::FilenamesType filenames;
    gdcm::Directory dir;
  int recursive = 0;
  unsigned int nfiles = 1;
    nfiles = dir.Load(directory, recursive);
    filenames = dir.GetFilenames();
  gen.SetFilenames( filenames );
  gen.SetDescriptor( "MyDescriptor" );
  if( !gen.Generate() )
    {
    return 1;
    }

//  gdcm::Writer writer;
//  writer.SetFile( gen.GetFile() );
//  writer.SetFileName( outfilename.c_str() );
//  if( !writer.Write() )
//    {
//    return 1;
//    }


  return 0;
}

