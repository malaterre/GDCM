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
#include "gdcmMD5.h"
#include "gdcm_polarssl.h"

/*
 */
namespace gdcm
{

class MD5Internals
{
public:
};

MD5::MD5()
{
  Internals = new MD5Internals;
}

MD5::~MD5()
{
  delete Internals;
}

bool MD5::Compute(const char *buffer, unsigned long buf_len, char digest[33])
{
  if( !buffer || !buf_len )
    {
    return false;
    }
  unsigned char output[16];

  md5( (unsigned char*)buffer, buf_len, output);

  for (int di = 0; di < 16; ++di)
    {
    sprintf(digest+2*di, "%02x", output[di]);
    }
  digest[2*16] = '\0';

  return true;
}



} // end namespace gdcm
