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

int Base64::GetEncodeLength(const char *src, int slen )
{
  int dlen = 0;
  int r = base64_encode( NULL, &dlen, (unsigned char*)(src), slen );
  if( r == POLARSSL_ERR_BASE64_INVALID_CHARACTER )
    return -1;
  return dlen;
}

int Base64::Encode( char *dst, int dlen,
                   const char *src, int  slen )
{
  return base64_encode( (unsigned char*)dst, &dlen, (unsigned char*)(src), slen );
}

int Base64::GetDecodeLength( const char *src, int  slen )
{
  int dlen = 0;
  int r = base64_decode( NULL, &dlen, (unsigned char*)(src), slen );
  if( r == POLARSSL_ERR_BASE64_INVALID_CHARACTER )
    return -1;
  return dlen;
}

int Base64::Decode( char *dst, int dlen,
                   const char *src, int  slen )
{
  return base64_decode( (unsigned char*)dst, &dlen, (unsigned char*)(src), slen );
}


int Base64::SelfTest( int verbose ) const
{
  return base64_self_test( verbose );
}


} // end namespace gdcm
