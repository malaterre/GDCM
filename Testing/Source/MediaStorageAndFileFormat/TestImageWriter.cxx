/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmFileMetaInformation.h"

#include "gdcmDataImages.h"

int TestImageWrite(const char* filename)
{
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
  const gdcm::FileMetaInformation &header = reader.GetHeader();
  gdcm::TS::MSType ms = header.GetMediaStorageType();
  bool isImage = gdcm::TS::IsImage( ms );
  if( isImage )
  {
     std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
  }
  else
  {
	  // not an image give up...
	  return 0;
  }
    }

  gdcm::Filename out(filename);
  std::string tmpdir = "/tmp/debug";
  std::string outfilename = tmpdir;
  outfilename += "/";
  outfilename += out.GetName();
  if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
    {
    if( !gdcm::System::MakeDirectory( tmpdir.c_str() ) )
      {
      std::cerr << "Error cannot execute test" << std::endl;
      std::cerr << "Last error was: " << gdcm::System::GetLastSystemError()
        << std::endl;
      return 1;
      }
    }

  gdcm::ImageWriter writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetPreamble( reader.GetPreamble() );
  writer.SetHeader( reader.GetHeader() );
  writer.SetDataSet( reader.GetDataSet() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  // Ok we have now two files let's compare their md5 sum:
  char digest[33], outdigest[33];
  gdcm::System::ComputeFileMD5(filename, digest);
  gdcm::System::ComputeFileMD5(outfilename.c_str(), outdigest);
  if( strcmp(digest, outdigest) )
    {
    // too bad the file is not identical, so let's be paranoid and
    // try to reread-rewrite this just-writen file:
    // TODO: Copy file gdcm::System::CopyFile( );
    if( TestImageWrite( outfilename.c_str() ) )
      {
      std::cerr << filename << " and "
        << outfilename << " are different\n";
      return 1;
      }
    // In theory I need to compare the two documents to check they
    // are identical... TODO
    std::cerr << filename << " and "
      << outfilename << " should be compatible\n";
    return 0;
    }
  else
    {
    std::cerr << filename << " and "
      << outfilename << " are identical\n";
    return 0;
    }
}

int TestImageWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestImageWrite(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestImageWrite( filename );
    ++i;
    }

  return r;
}

