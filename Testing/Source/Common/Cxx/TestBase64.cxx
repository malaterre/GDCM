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
#include "gdcmBase64.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"

#include <fstream>
#include <string.h> // strstr

using gdcm::Base64;
struct MyBase64 : public Base64
{
  int MySelfTest( int verbose ) { return SelfTest(verbose); }
};

int TestBase64(int argc, char *argv[])
{
  MyBase64 mybase64;
  int ret = mybase64.MySelfTest( 0 );


#if 0
  char *s1, *s2;
  const char begin[] = "-----BEGIN PGP PUBLIC KEY BLOCK-----";
  const char end[] = "-----END PGP PUBLIC KEY BLOCK-----";
  std::ifstream is( "/tmp/pubkey.txt" );
  int buffer_len = 1808;
  char *buffer = new char [ buffer_len ];
  is.read( buffer, buffer_len );
  s1 = strstr( buffer, begin );
  s2 = strstr( buffer, end );

  // http://lists.gnupg.org/pipermail/gnupg-devel/2005-February/021837.html
  s1 += sizeof( begin );
  if( *s1 == '\r' ) s1++;
  if( *s1 == '\n' ) s1++;
  const char version[] = "Version: GnuPG v1.4.6 (GNU/Linux)";
  const char dummy[] = "=BNsD";
  if( strncmp( s1, version, sizeof(version) - 1 ) == 0 )
    {
    s1 += sizeof(version) - 1;
    }

  while( *s1 == '\r' || *s1 == '\n' )
    {
    ++s1;
    }

  Base64 b64;
  int len = b64.GetDecodeLength(s1, 26 * 65 /*s2 - s1 - strlen(dummy) - 2*/ );
  std::cout << "len=" << len << std::endl;
  
  char *out = new char[ len ];
  int b = b64.Decode( out, len, s1, 26*65 );
  std::cout << "out=" << out << std::endl;
 
  delete[] out;

  delete[] buffer;
#endif

  return ret;
}

