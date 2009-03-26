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

using gdcm::AES;
struct MyAES : public AES
{
  int MySelfTest( int verbose ) { return SelfTest(verbose); }
};

int TestAES(int argc, char *argv[])
{
  gdcm::AES aes;
  unsigned char key[32] = {};
  unsigned char buf[64];
  aes.SetkeyEnc( key, 128 );
  aes.CryptEcb( AES::DECRYPT, buf, buf );

  MyAES myaes;
  int ret = myaes.MySelfTest( 0 );

  return ret;
}

