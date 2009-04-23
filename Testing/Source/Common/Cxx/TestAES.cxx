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
#include "gdcmAES.h"
#include "gdcmTesting.h"
#include <string.h>

using gdcm::AES;
struct MyAES : public AES
{
  int MySelfTest( int verbose ) { return SelfTest(verbose); }
  int MySimpleTest( int verbose ) { return SimpleTest( verbose ); }
};

int TestAES(int argc, char *argv[])
{
  gdcm::AES aes;
  const unsigned int KEY_LEN = 256;
  char key[ KEY_LEN  / 8] = {};
  if( !aes.SetkeyEnc( key, KEY_LEN ) ) return 1;

  char iv[16] = {};
  const char plainTextRef[] = "Single\1\2 block msg2";
  assert( sizeof(plainTextRef) <= 2*16 && sizeof(plainTextRef) >= 16 );
  char plainText[32*16] = {};
  memcpy( plainText, plainTextRef, sizeof(plainTextRef) );
  char buf[32*16]         = {};
  aes.CryptCbc( AES::ENCRYPT, 16*32, iv, plainText, buf );

  char buf2[32*16]            = {};
  memset(iv, 0, 16 );
  if( !aes.SetkeyDec( key, KEY_LEN ) ) return 1;
  aes.CryptCbc( AES::DECRYPT, 16*32, iv, buf, buf2);

  std::cout << buf2 << std::endl;
  int ret = 0;
  if( memcmp( plainText, buf2, sizeof(plainTextRef) ) != 0 )
    {
    ++ret;
    }

  MyAES myaes;
  ret += myaes.MySelfTest( 0 );
  ret += myaes.MySimpleTest( 0 );

  return ret;
}

