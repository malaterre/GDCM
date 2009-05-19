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
#include "gdcmPKCS7.h"
#include "gdcmX509.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"

#include <fstream>

#include <string.h>
#include <stdlib.h>

int TestPKCS7(int argc, char *argv[])
{
  gdcm::X509 x509;
  std::string cert = gdcm::Testing::GetSourceDirectory();
  cert += "/Testing/Source/Data/certificate.pem";
  if( !x509.ParseCertificateFile( cert.c_str() ) )
    {
    return 1;
    }
  gdcm::PKCS7 p7;
  p7.SetCertificate( &x509 );

  const char msg[] = "Hello World";

  char out[512];
  size_t len;
  bool b = p7.Encrypt( out, len, msg, strlen(msg) );
  if( !b ) return 1;
  if( len > 512 ) return 1;

  //std::ofstream of( "/tmp/debug.der", std::ios::binary );
  //of.write( out, len );
  //of.close();

  std::string privkey = gdcm::Testing::GetSourceDirectory();
  privkey += "/Testing/Source/Data/privatekey.pem";
  if( !x509.ParseKeyFile( privkey.c_str() ) )
    {
    return 1;
    }

  char out2[512];
  size_t len2;
  bool b2 = p7.Decrypt( out2, len2, out, len );
  if( !b2 ) return 1;

  if( memcmp( msg, out2, strlen( msg ) ) != 0 )
    {
    return 1;
    }

  return 0;
}

