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
#include "gdcmSHA1.h"
#include "gdcm_polarssl.h"

/*
 */
namespace gdcm
{

class SHA1Internals
{
public:
sha1_context ctx;
};

SHA1::SHA1()
{
  Internals = new SHA1Internals;
}

SHA1::~SHA1()
{
  delete Internals;
}

bool SHA1::Compute(const char *buffer, unsigned long buf_len, char digest[])
{
  if( !buffer || !buf_len )
    {
    return false;
    }

  unsigned char output[20];

  sha1( (unsigned char*)buffer, buf_len, output);

  for (int di = 0; di < 20; ++di)
    {
    sprintf(digest+2*di, "%02x", output[di]);
    }
  digest[2*20] = '\0';

  return true;
}



} // end namespace gdcm
