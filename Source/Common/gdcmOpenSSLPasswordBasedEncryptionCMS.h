/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef gdcmOpenSSLPasswordBasedEncryptionCMS_H
#define gdcmOpenSSLPasswordBasedEncryptionCMS_H

#include <iostream>
using namespace std;

#include "gdcmTypes.h"
#include "gdcmPasswordBasedEncryptionCMS.h"

#include <openssl\bio.h>
#include <openssl\cms.h>
#include <openssl\err.h>
#include <openssl\pem.h>
#include <openssl\rand.h>

namespace gdcm
{
class GDCM_EXPORT OpenSSLPasswordBasedEncryptionCMS : public PasswordBasedEncryptionCMS
{
public:
  OpenSSLPasswordBasedEncryptionCMS() : password(NULL), internalCipherType(CreateCipher(cipherType))
  {
  }

  ~OpenSSLPasswordBasedEncryptionCMS()
  {
    if (password) delete[] password;
  }

  //TODO: character limitations for PBE ???
  void SetPassword(const char * pass)
  {
    SetPassword(pass, strlen(pass));
  }

  void SetPassword(const char * pass, size_t passLen)
  {
    assert(pass);

    if (password)
      {
      delete[] password;
      }

    passwordLength = passLen;
    password = new char[passLen];
    memcpy(password, pass, passLen);
  }

  /// create a PKCS#7 envelopedData structure
  virtual bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const 
  {
    if (password == NULL) throw; //or assert
    BIO *in = NULL, *out = NULL;
    CMS_ContentInfo *cms = NULL;
    int flags = (CMS_BINARY | CMS_PARTIAL); //CMS_DETACHED
    bool ret = false;

    // RAND_status() and RAND_event() return 1 if the PRNG has been seeded with
    // enough data, 0 otherwise.
    if( !RAND_status() )
      {
      gdcmErrorMacro( "PRNG was not seeded properly" );
      outlen = 0;
      return false;
      }

    //load randomness ?
    if( len > (size_t)std::numeric_limits<int>::max() )
      {
      gdcmErrorMacro( "len is too big: " << len );
      return false;
      }

    in = BIO_new_mem_buf((void*)array, (int)len);
    if(!in)
      {
      gdcmErrorMacro( "BIO_new_mem_buf" );
      goto err;
      }

    out = BIO_new(BIO_s_mem());
    if (!out)
      {
      gdcmErrorMacro( "Error at creating the output memory buffer." );
      goto err;
      }

    cms = CMS_encrypt(NULL, in, internalCipherType, flags);
    if (!cms)
      {
      gdcmErrorMacro( "Error at creating the CMS strucutre." );
      goto err;
      }

    unsigned char* pwri_tmp = (unsigned char *)BUF_memdup(password, passwordLength);
    
    if (!pwri_tmp)
      goto err;

    if (!CMS_add0_recipient_password(cms,
        -1, NID_undef, NID_undef,
          pwri_tmp, passwordLength, NULL))
      goto err;
    pwri_tmp = NULL;

    if (!CMS_final(cms, in, NULL, flags))
      goto err;

    if (!i2d_CMS_bio(out, cms))
      {
      gdcmErrorMacro( "Error at writing CMS structure to output." );
      return false;
      }

    BUF_MEM *bptr;
    BIO_get_mem_ptr(out, &bptr);

    if (bptr->length > outlen)
      {
      //TODO: how to treat this ???
      gdcmErrorMacro( "Supplied output buffer too small: " << bptr->length << " bytes needed." );
      goto err;
      }
    memcpy(output, bptr->data, bptr->length);
    outlen = bptr->length;
  
    ret = true;

    err:

    if (!ret)
      {
      fprintf(stderr, "Error Encrypting Data\n");
      ERR_print_errors_fp(stderr);
      outlen = 0;
      }

    if (cms)
      CMS_ContentInfo_free(cms);

    if (in)
      BIO_free(in);
    if (out)
      BIO_free(out);

    return ret;
  }

  virtual bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const
  {
    BIO *in = NULL, *out = NULL;
    CMS_ContentInfo *cms = NULL;
    bool ret = false;
    int flags = CMS_DETACHED | CMS_BINARY;

    in = BIO_new_mem_buf((void*)array, (int)len);
    if(!in)
      {
      gdcmErrorMacro( "BIO_new_mem_buf" );
      goto err;
      }

    cms = d2i_CMS_bio(in, NULL);
    if (!cms)
      {
      gdcmErrorMacro( "Error when parsing the CMS structure." );
      goto err;
      }

    out = BIO_new(BIO_s_mem());
    if (!out)
      {
      gdcmErrorMacro( "Error at creating the output memory buffer." );
      goto err;
      }

    if (!CMS_decrypt_set1_password(cms, (unsigned char*)password, passwordLength))
      {
      gdcmErrorMacro( "Error at setting the decryption password." );
      goto err;
      }

    if (!CMS_decrypt(cms, NULL, NULL, NULL, out, flags))
      {
      gdcmErrorMacro( "Error at decrypting CMS structure" );
      goto err;
      }

    BUF_MEM *bptr;
    BIO_get_mem_ptr(out, &bptr);

    if (bptr->length > outlen)
      {
      gdcmErrorMacro( "Supplied output buffer too small: " << bptr->length << " bytes needed." );
      goto err;
      //TODO: how to treat this ???
      }
    memcpy(output, bptr->data, bptr->length);
    outlen = bptr->length;
    ret = true;

    err:

    if (!ret)
      {
      fprintf(stderr, "Error Decrypting Data\n");
      //ERR_print_errors_fp(stderr);
      outlen = 0;
      }

    if (cms)
      CMS_ContentInfo_free(cms);

    if (in)
      BIO_free(in);
    if (out)
      BIO_free(out);

    return ret;
  }

  virtual void SetCipherType(CipherTypes type)
  { 
    internalCipherType = CreateCipher(type);
    //TODO: how to handle error ? use exceptions or not ?
    if (internalCipherType == NULL) throw;
    cipherType = type;
  }

  //TODO: virtual ???
  CipherTypes GetCipherType() const
  {
    return cipherType;
  }

private:
  static const EVP_CIPHER* CreateCipher( PasswordBasedEncryptionCMS::CipherTypes ciphertype)
  {
    const EVP_CIPHER *cipher = 0;
    switch( ciphertype )
      {
    case PasswordBasedEncryptionCMS::DES_CIPHER:    // DES
      cipher = EVP_des_cbc();
      break;
    case PasswordBasedEncryptionCMS::DES3_CIPHER:   // Triple DES
      cipher = EVP_des_ede3_cbc();
      break;
    case PasswordBasedEncryptionCMS::AES128_CIPHER: // CBC AES
      cipher = EVP_aes_128_cbc();
      break;
    case PasswordBasedEncryptionCMS::AES192_CIPHER: // '   '
      cipher = EVP_aes_192_cbc();
      break;
    case PasswordBasedEncryptionCMS::AES256_CIPHER: // '   '
      cipher = EVP_aes_256_cbc();
      break;
      }
    return cipher;
  }

protected:
  CipherTypes cipherType;
  const EVP_CIPHER *internalCipherType;
  char * password;
  size_t passwordLength;

};
}

#endif //GDCMCMS_H
