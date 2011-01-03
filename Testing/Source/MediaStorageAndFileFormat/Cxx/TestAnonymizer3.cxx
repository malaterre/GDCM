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
#include "gdcmFileDerivation.h"
#include "gdcmSystem.h"

int TestAnonymizer3(int argc, char *argv[])
{
  using namespace gdcm;
  gdcm::Global& g = gdcm::Global::GetInstance();
  if( !g.LoadResourcesFiles() )
    {
    return 1;
    }
  const char *directory = gdcm::Testing::GetDataRoot();
  std::string sfilename = std::string(directory) + "/012345.002.050.dcm";
  const char *filename = sfilename.c_str();

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );

  // Create directory first:
  const char subdir[] = "TestAnonymizer3";
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  const char subdir2[] = "TestAnonymizer3Lossy";
  std::string tmpdir2 = Testing::GetTempDirectory( subdir2 );
  if( !System::FileIsDirectory( tmpdir2.c_str() ) )
    {
    System::MakeDirectory( tmpdir2.c_str() );
    //return 1;
    }
  std::string outfilenamelossy = Testing::GetTempFilename( filename, subdir2 );
  std::string outfilename2 = "/tmp/d.dcm";

// Encrypt
{
  gdcm::CryptographicMessageSyntax cms;
  if( !cms.ParseCertificateFile( certpath.c_str() ) )
    {
    return 1;
    }

  gdcm::SmartPointer<gdcm::Anonymizer> ano = new gdcm::Anonymizer;
  ano->SetCryptographicMessageSyntax( &cms );

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
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( ano.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  const File& file = reader.GetFile();

  FileDerivation fd;
  fd.SetFile( file );
  // FIXME hardcoded:
  fd.AddReference( "1.2.840.10008.5.1.4.1.1.4",
    "1.2.840.113619.2.5.1762386977.1328.985934491.693" );

  // CID 7202 Source Image Purposes of Reference
  // {"DCM",121320,"Uncompressed predecessor"},
  fd.SetPurposeOfReferenceCodeSequenceCodeValue( 121320 );

  // CID 7203 Image Derivation
  // { "DCM",113040,"Lossy Compression" },
  fd.SetDerivationCodeSequenceCodeValue( 113040 );
  fd.SetDerivationDescription( "lossy conversion" );
  if( !fd.Derive() )
    {
    std::cerr << "Sorry could not derive using input info" << std::endl;
    return 1;
    }

  writer.SetFileName( outfilename2.c_str() );
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
