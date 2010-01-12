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

int TestAnonymizer2(int argc, char *argv[])
{
  gdcm::Global& g = gdcm::Global::GetInstance();
  if( !g.LoadResourcesFiles() )
    {
    return 1;
    }

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );

  gdcm::CryptographicMessageSyntax cms;
  if( !cms.ParseCertificateFile( certpath.c_str() ) )
    {
    return 1;
    }

  gdcm::SmartPointer<gdcm::Anonymizer> ano = new gdcm::Anonymizer;
  ano->SetCryptographicMessageSyntax( &cms );

  gdcm::SimpleSubjectWatcher watcher(ano, "Anonymizer");

  gdcm::Reader reader;
  const char *filename = argv[1];
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
  writer.SetFileName( "/tmp/ano.dcm" );
  writer.SetFile( reader.GetFile() );
  writer.Write();

  return 0;
}

