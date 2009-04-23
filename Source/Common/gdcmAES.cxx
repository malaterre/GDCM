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
#include "gdcmAES.h"
#include "gdcm_polarssl.h"
#include <string.h> // memset

/*
 * Ok for now I'll try the following implementation:
 * http://polarssl.org/
 * It respects:
 *  - Open Source
 *  - Portable C
 *  - BSD license
 *
 * See also:
 * http://polarssl.org/?page=show_source&type=source&file=aes
 */
namespace gdcm
{

// PIMPL
class AESInternals
{
public:
  aes_context ctx;
};

AES::AES()
{
  Internals = new AESInternals;
  Internals->ctx.nr = 0;
  Internals->ctx.rk = 0;
  assert( sizeof( Internals->ctx.buf ) == 68 * sizeof(long) );
  memset( Internals->ctx.buf, 0, sizeof( Internals->ctx.buf ) );
}

AES::~AES()
{
  delete Internals;
}

inline bool aes_check_struct(aes_context *ctx)
{
  switch( ctx->nr )
    {
  case 10:
  case 12:
  case 14:
    return true;
    }
  return false;
}

inline bool aes_check_params(const char *key, unsigned int keysize)
{
  if(key)
    {
    switch(keysize)
      {
    case 128:
    case 192:
    case 256:
      return true;
    default:
      ;
      }
    }
  // all other case:
  return false;
}

bool AES::SetkeyEnc(const char *key, unsigned int keysize )
{
  bool ok = aes_check_params(key, keysize * 8);
  if( ok )
    {
    aes_setkey_enc( &Internals->ctx, (unsigned char*)(key), keysize * 8 );
    assert( aes_check_struct( &Internals->ctx ) );
    }
  return ok;
}

bool AES::SetkeyDec(const char *key, unsigned int keysize )
{
  bool ok = aes_check_params(key, keysize * 8);
  if( ok )
    {
    aes_setkey_dec( &Internals->ctx, (unsigned char*)(key), keysize * 8 );
    assert( aes_check_struct( &Internals->ctx ) );
    }
  return ok;
}

bool AES::CryptEcb(
                    int mode,
                    const char input[16],
                    char output[16] ) const
{
  if( !aes_check_struct( &Internals->ctx ) ) return false;
  aes_crypt_ecb( &Internals->ctx,
    mode,
    (unsigned char*)(input),
    (unsigned char*)output );
  return true;
}

bool AES::CryptCbc(
                    int mode,
                    unsigned int length,
                    char iv[16],
                    const char *input,
                    char *output ) const
{
  if( !aes_check_struct( &Internals->ctx ) ) return false;
  if( length % 16 != 0 ) return false;
  aes_crypt_cbc( &Internals->ctx,
    mode,
    length,
    (unsigned char*)iv,
    (unsigned char*)(input),
    (unsigned char*)output );

  return true;
}

bool AES::CryptCfb128(
                       int mode,
                       unsigned int length,
                       unsigned int &iv_off,
                       char iv[16],
                       const char *input,
                       char *output ) const
{
  if( !aes_check_struct( &Internals->ctx ) ) return false;
  int iv_off_int;
  aes_crypt_cfb128( &Internals->ctx,
    mode,
    length,
    &iv_off_int,
    (unsigned char*)iv,
    (unsigned char*)(input),
    (unsigned char*)output );
  iv_off = iv_off_int;

  return true;
}

int AES::SimpleTest(int verbose) const
{
  aes_context ctx;

  unsigned char plainText[] = "Single block msg";
  unsigned char plainText2[16+1] = {};
  unsigned char initVector[16] = {};
  unsigned char tempInitVector[16];
  unsigned char cipherText[16+1];
  unsigned char keyText[32] = {};

  // Encrypt
  memset(cipherText,0,16+1);
  memset(tempInitVector,0,16);
  memcpy(tempInitVector,initVector,16);
  aes_setkey_enc( &ctx, keyText, 128*2 );
  aes_crypt_cbc( &ctx, AES_ENCRYPT, 16, tempInitVector, plainText, cipherText );
  if(verbose)
    printf("Ciphertext:\n");
  //if(verbose)
  //  printf("%s\n",ciphertext); 

  // Decrypt
  memset(tempInitVector,0,16);
  memset(plainText,0,16);
  memcpy(tempInitVector,initVector,sizeof(tempInitVector));
  aes_setkey_dec( &ctx, keyText, 128*2 );
  aes_crypt_cbc( &ctx, AES_DECRYPT, 16, tempInitVector, cipherText, plainText2 );
  if(verbose)
    printf("Plaintext:\n");
  if(verbose)
    printf("%s\n",plainText2); 
  return 0;
}

int AES::SelfTest( int verbose ) const
{
  return aes_self_test( verbose );
}

void AES::operator=(const AES& aes)
{
  Internals->ctx = aes.Internals->ctx;
}

} // end namespace gdcm
