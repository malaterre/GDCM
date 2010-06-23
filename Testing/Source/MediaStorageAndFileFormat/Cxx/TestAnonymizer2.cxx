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
#include "gdcmAnonymizer.h"
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmFilename.h"
#include "gdcmTesting.h"
#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmSmartPointer.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmGlobal.h"
#include "gdcmSystem.h"

namespace gdcm
{
int TestAnonymize2(const char *subdir, const char *filename)
{
  gdcm::Global& g = gdcm::Global::GetInstance();
  if( !g.LoadResourcesFiles() )
    {
    return 1;
    }

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );

  // Create directory first:
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  // Create directory first:
  const char subdir2[] = "TestAnonymizer2_2";
  std::string tmpdir2 = Testing::GetTempDirectory( subdir2 );
  if( !System::FileIsDirectory( tmpdir2.c_str() ) )
    {
    System::MakeDirectory( tmpdir2.c_str() );
    //return 1;
    }
  std::string outfilename2 = Testing::GetTempFilename( filename, subdir2 );

// Encrypt
{
  gdcm::CryptographicMessageSyntax cms;
  if( !cms.ParseCertificateFile( certpath.c_str() ) )
    {
    return 1;
    }

  gdcm::SmartPointer<gdcm::Anonymizer> ano = new gdcm::Anonymizer;
  ano->SetCryptographicMessageSyntax( &cms );

  //gdcm::SimpleSubjectWatcher watcher(ano, "Anonymizer");

  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Could not read: " << filename << std::endl;
    return 1;
    }

  ano->SetFile( reader.GetFile() );
  if( !ano->BasicApplicationLevelConfidentialityProfile() )
    {
    return 1;
    }

  gdcm::Writer writer;
  //writer.SetFileName( "/tmp/ano.dcm" );
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
}
// Decrypt
{
  gdcm::CryptographicMessageSyntax cms;
  if( !cms.ParseKeyFile( keypath.c_str() ) )
    {
    return 1;
    }

  gdcm::SmartPointer<gdcm::Anonymizer> ano = new gdcm::Anonymizer;
  ano->SetCryptographicMessageSyntax( &cms );

  //gdcm::SimpleSubjectWatcher watcher(ano, "Anonymizer");

  gdcm::Reader reader;
  reader.SetFileName( outfilename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Could not read: " << outfilename << std::endl;
    return 1;
    }

  ano->SetFile( reader.GetFile() );
  if( !ano->BasicApplicationLevelConfidentialityProfile(false) )
    {
    return 1;
    }

  // TODO Need to compare filename to decrypted one.
  gdcm::Writer writer;
  writer.SetFileName( outfilename2.c_str() );
  writer.SetFile( reader.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename2 << std::endl;
    return 1;
    }
}

  return 0;
}
}

int TestAnonymizer2(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return gdcm::TestAnonymize2(argv[0], filename);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += gdcm::TestAnonymize2( argv[0], filename );
    ++i;
    }

  return r;
}

