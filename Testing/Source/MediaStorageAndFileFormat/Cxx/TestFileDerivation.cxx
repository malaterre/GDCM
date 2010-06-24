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
#include "gdcmFileDerivation.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"

int TestFileDerive(const char *subdir, const char* filename)
{
  using gdcm::Reader;
  using gdcm::Writer;
  using gdcm::Testing;
  using gdcm::System;
  using gdcm::FileDerivation;
  Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    return 1;
    }

  FileDerivation fd;
  fd.SetFile( reader.GetFile() );
  // Setup some actions:
  if( !fd.Derive() )
    {
    return 1;
    }

  // Create directory first:
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
 
  // now let's try to read it back in:
  Reader reader2;
  reader2.SetFileName( outfilename.c_str() );
  if ( !reader2.Read() )
    {
    std::cerr << "Could not reread written file: " << outfilename << std::endl;
    return 1;
    }

  return 0;
}

int TestFileDerivation( int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestFileDerive( argv[0], filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestFileDerive( argv[0], filename );
    ++i;
    }

  return r;
  return 0;
}

