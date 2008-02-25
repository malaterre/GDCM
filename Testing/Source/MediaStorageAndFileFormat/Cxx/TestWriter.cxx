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
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"

//bool IsImpossibleToRewrite(const char *filename)
//{
//  const char *impossible;
//  int i = 0;
//  while( (impossible= gdcmBlackListWriterDataImages[i]) )
//    {
//    if( strcmp( impossible, filename ) == 0 )
//      {
//      return true;
//      }
//    ++i;
//    }
//  return false;
//}

int TestWrite(const char *subdir, const char* filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::Filename out(filename);
  // FIXME: we need to use the temp from the binary build instead...
  //std::string tmpdir = "/tmp/debug";
  std::string tmpdir;
  tmpdir = gdcm::Testing::GetTempDirectory();
  tmpdir += "/";
  tmpdir += subdir;
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

  gdcm::Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
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
    std::string subsubdir = subdir;
    subsubdir += "/";
    subsubdir += subdir;
    if( TestWrite(subsubdir.c_str(), outfilename.c_str() ) )
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

int TestWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestWrite(argv[0], filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestWrite(argv[0], filename );
    ++i;
    }

  return r;
}
