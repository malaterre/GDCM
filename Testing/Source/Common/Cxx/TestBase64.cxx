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

#include <string.h>

int TestBase64(int argc, char *argv[])
{
  const char str[] = "GDCM Test Base64 Encoding";
  gdcm::Base64 base64;

  int l1 = gdcm::Base64::GetEncodeLength( str, sizeof(str) );
  if( l1 != 37 ) return 1;

  char buffer[256];
  if( l1 > sizeof(buffer) ) return 1;

  int l2 = gdcm::Base64::Encode( buffer, sizeof(buffer), str, sizeof(str) );
  if( l2 != 0 ) return 1;

  size_t lbuffer = strlen(buffer);
  if( lbuffer != l1 - 1 ) return 1;

  int l3 = gdcm::Base64::GetDecodeLength( buffer, l1 - 1 );
  if( l3 != 26 ) return 1;
  if( l3 != sizeof(str) ) return 1;

  char buffer2[256];
  if( l3 > sizeof(buffer2) ) return 1;
  int l4 = gdcm::Base64::Decode( buffer2, sizeof(buffer2), buffer, l1 - 1);
  if( l4 != 0 ) return 1;

  if( strcmp( str, buffer2 ) != 0 )
    {
    return 1;
    }

  return 0;
}

