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
#include "gdcmDummyValueGenerator.h"
#include "gdcmTrace.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"
#include "gdcm_polarssl.h"

namespace gdcm
{

const char* DummyValueGenerator::Generate(const char *input)
{
  unsigned char output[16];
  char digest2[32+1];
  md5( (unsigned char*)input, strlen(input), output );
  for (int di = 0; di < 16; ++di)
    {
    sprintf(digest2+2*di, "%02x", output[di]);
    }
  digest2[2*16] = '\0';

  static char digest[32+1] = {};
  bool b = false;
  if( input )
    b = Testing::ComputeMD5(input, strlen(input), digest);

  assert( memcmp( digest, digest2, 33 ) == 0 );
  if( b )
    return digest;
  return 0;
}


} // end namespace gdcm
