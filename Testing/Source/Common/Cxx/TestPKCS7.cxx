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
#include "gdcmTesting.h"
#include "gdcmSystem.h"

#include <fstream>

#include <string.h>

int TestPKCS7(int argc, char *argv[])
{
  gdcm::PKCS7 p7;

  const char msg[] = "Hello World";

  char out[512];
  size_t len;
  bool b = p7.Encrypt( out, len, msg, strlen(msg) );
  if( !b ) return 1;
  if( len > 512 ) return 1;

  std::ofstream of( "/tmp/debug.der", std::ios::binary );
  of.write( out, len );
  of.close();

  return 0;
}

