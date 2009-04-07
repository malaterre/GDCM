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
#include "gdcm_polarssl.h"

/*
 */
namespace gdcm
{

class Base64Internals
{
public:
};

Base64::Base64()
{
  Internals = new Base64Internals;
}

Base64::~Base64()
{
  delete Internals;
}

int Base64::GetEncodeLength(const unsigned char *src, int  slen )
{
  int dlen = 0;
  int r = base64_encode( NULL, &dlen, const_cast<unsigned char*>(src), slen );
  if( r == 0 )
    return dlen;
  return -1;
}

int Base64::Encode( unsigned char *dst, int dlen,
                   const unsigned char *src, int  slen )
{
  return base64_encode( dst, &dlen, const_cast<unsigned char*>(src), slen );
}

int Base64::GetDecodeLength( const unsigned char *src, int  slen )
{
  int dlen = 0;
  int r = base64_decode( NULL, &dlen, const_cast<unsigned char*>(src), slen );
  if( r == 0 )
    return dlen;
  return -1;
}

int Base64::Decode( unsigned char *dst, int dlen,
                   const unsigned char *src, int  slen )
{
  return base64_decode( dst, &dlen, const_cast<unsigned char*>(src), slen );
}


int Base64::SelfTest( int verbose ) const
{
  return base64_self_test( verbose );
}


} // end namespace gdcm
