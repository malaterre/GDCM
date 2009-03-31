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
                       int mode, int  ilen,
                       const unsigned char *input,
                       unsigned char *output ) const
{

  return 
rsa_pkcs1_encrypt( &Internals->ctx,
                       mode, ilen,
                       const_cast<unsigned char*>(input),
                       output );

}

int RSA::Pkcs1Decrypt(
                       int mode, int *olen,
                       const unsigned char *input,
                       unsigned char *output,
		       int output_max_len)
{
return 
 rsa_pkcs1_decrypt( &Internals->ctx,
                       mode, olen,
                       const_cast<unsigned char *>(input),
                       output,
		       output_max_len);
 
}

int RSA::X509ParseKey(
                   const unsigned char *buf, int buflen,
                   const unsigned char *pwd, int pwdlen )
{

return x509parse_key( &Internals->ctx,
                   const_cast<unsigned char*>(buf), buflen,
                   const_cast<unsigned char*>(pwd), pwdlen );

}

int RSA::X509ParseKeyfile( const char *path, const char *password )
{
  return x509parse_keyfile( &Internals->ctx, const_cast<char*>(path), const_cast<char*>(password) );
}

int RSA::SelfTest( int verbose ) const
{
  return rsa_self_test( verbose );
}


} // end namespace gdcm
