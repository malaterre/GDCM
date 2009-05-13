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

#ifdef GDCM_USE_SYSTEM_OPENSSL
// http://www.openssl.org/docs/crypto/BIO_f_base64.html
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#endif

#if 0
#include "gdcm_polarssl.h"
#endif
#include <string.h>

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
#if 0
  int dlen = 0;
  int r = base64_encode( NULL, &dlen, (unsigned char*)(src), slen );
  if( r == POLARSSL_ERR_BASE64_INVALID_CHARACTER )
    return -1;
  return dlen;
#endif

#ifdef GDCM_USE_SYSTEM_OPENSSL
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, src, slen);
  (void)BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);
  int dlen = bptr->length;
  BIO_free_all(b64);
  return dlen;
#endif
  return -1;
}

int Base64::Encode( char *dst, int dlen,
                   const char *src, int  slen )
{
#if 0
  return base64_encode( (unsigned char*)dst, &dlen, (unsigned char*)(src), slen );
#endif

#ifdef GDCM_USE_SYSTEM_OPENSSL
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, src, slen);
  (void)BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  if( dlen < bptr->length ) return -1;

  memcpy(dst, bptr->data, bptr->length-1);
  dst[bptr->length-1] = 0;

  BIO_free_all(b64);
  return 0;
#else
 return -1;
#endif
}

int Base64::GetDecodeLength( const char *src, int  slen )
{
#if 0
  int dlen = 0;
  int r = base64_decode( NULL, &dlen, (unsigned char*)(src), slen );
  if( r == POLARSSL_ERR_BASE64_INVALID_CHARACTER )
    return -1;
  return dlen;
#endif

#ifdef GDCM_USE_SYSTEM_OPENSSL
  BIO *b64, *bmem;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new_mem_buf((char*)src, slen);
  bmem = BIO_push(b64, bmem);
  char *output = new char[ slen ];
  BIO_read(bmem, output, slen );

  int len = strlen(output);
  BIO_free_all(bmem);

  delete[] output;
  return len;
#else
  return -1;
#endif
}

int Base64::Decode( char *dst, int dlen,
                   const char *src, int  slen )
{
#if 0
  return base64_decode( (unsigned char*)dst, &dlen, (unsigned char*)(src), slen );
#endif

#ifdef GDCM_USE_SYSTEM_OPENSSL
  BIO *b64, *bmem;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new_mem_buf((char*)src, slen);
  bmem = BIO_push(b64, bmem);

  char *output = new char[ slen ];
  BIO_read(bmem, output, slen);

  int len = strlen(output);

  if( len > dlen ) return -1;
  memcpy(dst, output, len);
  delete[] output;

  BIO_free_all(bmem);
  return 0;
#else
  return -1;
#endif
}


//int Base64::SelfTest( int verbose ) const
//{
//  return base64_self_test( verbose );
//}


} // end namespace gdcm
