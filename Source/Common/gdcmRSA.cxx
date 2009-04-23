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
#include "gdcmRSA.h"
#include "gdcmX509.h"
#include "gdcm_polarssl.h"
#include <string.h>
#include <iostream>

/*
 */
namespace gdcm
{

class RSAInternals
{
public:
rsa_context ctx;
};

RSA::RSA()
{
  Internals = new RSAInternals;
  memset( &Internals->ctx, 0, sizeof( rsa_context ) );
}

RSA::~RSA()
{
  rsa_free( &Internals->ctx );

  delete Internals;
}

int RSA::CheckPubkey( ) const
{
  return rsa_check_pubkey( &Internals->ctx );
}

int RSA::CheckPrivkey() const
{
  return rsa_check_privkey( &Internals->ctx );
}

unsigned int RSA::GetLenkey() const
{
  return Internals->ctx.len;
}

int RSA::Pkcs1Encrypt( 
                       int mode, unsigned int ilen,
                       const char *input,
                       char *output ) const
{
  return 
    rsa_pkcs1_encrypt( &Internals->ctx,
      mode, ilen,
      (unsigned char*)input,
      (unsigned char*)output );
}

int RSA::Pkcs1Decrypt(
                       int mode, unsigned int &olen,
                       const char *input,
                       char *output,
                       unsigned int output_max_len)
{
  int olen_int;
  int val = 
    rsa_pkcs1_decrypt( &Internals->ctx,
      mode, &olen_int,
      (unsigned char *)(input),
      (unsigned char*)output,
      output_max_len);
  olen = olen_int;
  return val;
}

int RSA::X509ParseKey(
                   const char *buf, unsigned int buflen,
                   const char *pwd, unsigned int pwdlen )
{
  return x509parse_key( &Internals->ctx,
    (unsigned char*)(buf), buflen,
    (unsigned char*)(pwd), pwdlen );
}

int RSA::X509ParseKeyfile( const char *path, const char *password )
{
  int format = x509parse_keyfile( &Internals->ctx, const_cast<char*>(path), const_cast<char*>(password) );
  switch( format )
    {
    case 0:
      return 0; // no error
    case POLARSSL_ERR_X509_KEY_PASSWORD_REQUIRED:
      return X509::ERR_X509_KEY_PASSWORD_REQUIRED;
    case POLARSSL_ERR_X509_KEY_PASSWORD_MISMATCH:
      return X509::ERR_X509_KEY_PASSWORD_MISMATCH;
    }
  return -1; // some other error
}

int RSA::X509WriteKeyfile( const char *path, int format )
{
  int polarssl_format = 0;
  // remap
  switch( format )
    {
    case( OUTPUT_DER ):
      polarssl_format = X509_OUTPUT_DER;
      break;
    case( OUTPUT_PEM ):
      polarssl_format = X509_OUTPUT_PEM;
      break;
    }
  return x509write_keyfile( &Internals->ctx,
                       const_cast<char*>(path),
                       polarssl_format );

}

int RSA::SelfTest( int verbose ) const
{
  return rsa_self_test( verbose );
}


} // end namespace gdcm
