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
}

AES::~AES()
{
  delete Internals;
}

inline bool aes_check_params(const unsigned char *key, int keysize)
{
  if(!key) return false;
  switch(keysize)
    {
    case 128:
    case 192:
    case 256:
      return true;
    default:
      ;
    }
  return false;
}

bool AES::SetkeyEnc(const unsigned char *key, int keysize )
{
  bool ok = aes_check_params(key, keysize);
  if( ok )
    aes_setkey_enc( &Internals->ctx, const_cast<unsigned char*>(key), keysize );
  return ok;
}

bool AES::SetkeyDec(const unsigned char *key, int keysize )
{
  bool ok = aes_check_params(key, keysize);
  if( ok )
    aes_setkey_dec( &Internals->ctx, const_cast<unsigned char*>(key), keysize );
  return ok;
}

void AES::CryptEcb(
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] ) const
{
aes_crypt_ecb( &Internals->ctx,
                    mode,
                    const_cast<unsigned char*>(input),
                    output );
}

void AES::CryptCbc(
                    int mode,
                    int length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output ) const
{
aes_crypt_cbc( &Internals->ctx,
                    mode,
                    length,
                    iv,
                    const_cast<unsigned char*>(input),
                    output );

}

void AES::CryptCfb128(
                       int mode,
                       int length,
                       int &iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output ) const
{
aes_crypt_cfb128( &Internals->ctx,
                       mode,
                       length,
                       &iv_off,
                       iv,
                       const_cast<unsigned char*>(input),
                       output );

}

int AES::SelfTest( int verbose ) const
{
  return aes_self_test( verbose );
}

} // end namespace gdcm
