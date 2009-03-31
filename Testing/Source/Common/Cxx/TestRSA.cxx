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
#include "gdcmRSA.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"

#include <stdlib.h>
#include <string.h> // memset


using gdcm::RSA;
struct MyRSA : public RSA
{
  int MySelfTest( int verbose ) { return SelfTest(verbose); }
};

int TestRSA(int argc, char *argv[])
{
  MyRSA myrsa;
  int ret = myrsa.MySelfTest( 0 );

  // By default on *nix system there should be a id_rsa file in $HOME/.ssh. Let's try parsing it:
  char *home = getenv("HOME");
  if(!home) return 1;

  std::string id_rsa_path = home;
  id_rsa_path += "/.ssh/id_rsa";

  if( !gdcm::System::FileExists( id_rsa_path.c_str() ) )
    {
    return 1;
    }

  gdcm::RSA rsa;
  if( rsa.X509ParseKeyfile( id_rsa_path.c_str() ) != 0 ) // success == 0
    {
    return 1;
    }
  if( rsa.CheckPubkey() != 0 || rsa.CheckPrivkey() != 0 )
    {
    return 1;
    }

  const unsigned int PT_LEN = 24;
  const unsigned int KEY_LEN = 256;
  unsigned char rsa_plaintext[PT_LEN];
  unsigned char rsa_decrypted[PT_LEN];
  unsigned char rsa_ciphertext[KEY_LEN];

  if( rsa.GetLenkey() != KEY_LEN ) return 1;

//#define RSA_PT  "\xAA\xBB\xCC\x03\x02\x01\x00\xFF\xFF\xFF\xFF\xFF" \
//                "\x11\x22\x33\x0A\x0B\x0C\xCC\xDD\xDD\xDD\xDD\xDD"
//
//  memcpy( rsa_plaintext, RSA_PT, PT_LEN );
  memset( rsa_plaintext, 0, PT_LEN );

  if( rsa.Pkcs1Encrypt( RSA::PUBLIC, PT_LEN, rsa_plaintext, rsa_ciphertext ) != 0 )
    {
    return 1;
    }

  for(unsigned int i = 0; i < KEY_LEN; ++i)
    std::cout << (int)rsa_ciphertext[i] << ",";
  std::cout << std::endl;

  int len;
    if( rsa.Pkcs1Decrypt( RSA::PRIVATE, &len,
                           rsa_ciphertext, rsa_decrypted,
			   sizeof(rsa_decrypted) ) != 0 )
    {

        return 1 ;
    }

    if( memcmp( rsa_decrypted, rsa_plaintext, len ) != 0 )
    {

        return 1 ;
    }


  return 0;
}

