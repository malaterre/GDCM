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

// http://www.mail-archive.com/list@xyssl.org/msg00027.html
/*

// Use XySSL 
#include "xyssl/aes.h"
#include "xyssl/md5.h"
#include "xyssl/rsa.h"
#include "xyssl/sha1.h"

// Convert to OpenSSL interface
#define SHA_CTX                            sha1_context
#define SHA1_Init( _CTX_ )                 sha1_starts( (_CTX_) )
#define SHA1_Update( _CTX_, _BUF_, _LEN_ ) sha1_update( (_CTX_), (unsigned 
char*)(_BUF_), (_LEN_) )
#define SHA1_Final( _OUT_, _CTX_ )         sha1_finish( (_CTX_), (_OUT_) )

#define MD5_CTX                           md5_context
#define MD5_Init( _CTX_ )                 md5_starts( (_CTX_) )
#define MD5_Update( _CTX_, _BUF_, _LEN_ ) md5_update( (_CTX_), (unsigned 
char*)(_BUF_), (_LEN_) )
#define MD5_Final( _OUT_, _CTX_ )         md5_finish( (_CTX_), (_OUT_) )

#define AES_SIZE       16
#define AES_BLOCK_SIZE 16
#define AES_KEY                                                          
aes_context
#define AES_set_encrypt_key( _KEY_, _KEYSIZE_, _CTX_ )                   
aes_setkey_enc( (_CTX_), (_KEY_), (_KEYSIZE_) )
#define AES_set_decrypt_key( _KEY_, _KEYSIZE_, _CTX_ )                   
aes_setkey_dec( (_CTX_), (_KEY_), (_KEYSIZE_) )
#define AES_cbc_encrypt( _INPUT_, _OUTPUT_, _LEN_, _CTX_, _IV_, _MODE_ ) 
aes_crypt_cbc( (_CTX_), (_MODE_), (_LEN_), (_IV_), (_INPUT_), (_OUTPUT_) )

// Define fake, pass-through RSA
inline int __RSA_Passthrough( void* output, void* input, int size ) { memcpy( 
output, input, size ); return size; }
inline rsa_context* d2i_RSA_PUBKEY( void* ignore, unsigned char** bufferPtr, 
int len )
{
    // Not a general purpose parser -- only parses public key from *exactly*
    //     openssl\openssl genrsa  -out privatekey.pem  512 (or 1024)
    //     openssl\openssl rsa -in privatekey.pem -out privatekey.der -outform 
der
    //     openssl\openssl rsa -in privatekey.pem -out publickey.der -outform 
der -pubout
    if( ignore != 0  ) return 0;
    if( len != 94 && len != 162 ) return 0;
    unsigned char* buffer = *(unsigned char**)bufferPtr;
    rsa_context* context = new rsa_context;
    memset( context, 0, sizeof(rsa_context) );
    if( (len ==  94 && !mpi_read_binary( &context->N, &buffer[25],  64 ) && 
!mpi_read_binary( &context->E, &buffer[91],  3 )) ||
        (len == 162 && !mpi_read_binary( &context->N, &buffer[29], 128 ) && 
!mpi_read_binary( &context->E, &buffer[159], 3 )) )
    {
        // Success
        context->len = ( mpi_msb( &context->N ) + 7 ) >> 3;
        return context;
    }
    else
    {
        // Failed, clean up
        delete context;
        return 0;        
    }
}
#define RSA_PKCS1_PADDING                                            1 // 
ignored; always encrypt with this
#define RSA_size( _CTX_ )                                        (_CTX_)->len
#define RSA                                                      rsa_context
#define d2i_RSAPrivateKey( a, b, c )                             new rsa_context
inline int RSA_public_decrypt ( int size, unsigned char* input, unsigned char* 
output, RSA* key, int ignore ) { int outsize=size; if( !rsa_pkcs1_decrypt( key, 
RSA_PUBLIC,  &outsize, input, output ) ) return outsize; else return -1; }
inline int RSA_private_decrypt( int size, unsigned char* input, unsigned char* 
output, RSA* key, int ignore ) { int outsize=size; if( !rsa_pkcs1_decrypt( key, 
RSA_PRIVATE, &outsize, input, output ) ) return outsize; else return -1; }
inline int RSA_public_encrypt ( int size, unsigned char* input, unsigned char* 
output, RSA* key, int ignore ) { if( !rsa_pkcs1_encrypt( key, RSA_PUBLIC,  
size, input, output ) ) return RSA_size(key); else return -1; }
inline int RSA_private_encrypt( int size, unsigned char* input, unsigned char* 
output, RSA* key, int ignore ) { if( !rsa_pkcs1_encrypt( key, RSA_PRIVATE, 
size, input, output ) ) return RSA_size(key); else return -1; }
#define RSA_free( _CTX_ )                                         delete (_CTX_)
#define RSA_blinding_off( _IGNORE_ )
#define ERR_get_error( )                                         "**FIXME: RSA 
disabled"

*/

} // end namespace gdcm
