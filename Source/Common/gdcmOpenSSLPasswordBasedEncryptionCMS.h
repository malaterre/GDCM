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
  OpenSSLPasswordBasedEncryptionCMS() : password(NULL)
  {
  }

  typedef enum {
    DES_CIPHER,    // DES
    DES3_CIPHER,   // Triple DES
    AES128_CIPHER, // CBC AES
    AES192_CIPHER, // '   '
    AES256_CIPHER  // '   '
  } CipherTypes;

  //TODO: character limitations for PBE ???
  void SetPassword(const char * pass)
  {
    passwordLength = strlen(pass);
    password = new char[passwordLength + 1];
    //if (password == NULL)
    memcpy(password, pass, passwordLength);
  }
  void SetPassword(const char * pass, size_t passLen)
  {
    passwordLength = passLen;
    password = new char[passLen];
    //if (password == NULL)
    memcpy(password, pass, passLen);
  }

  /// create a PKCS#7 envelopedData structure
  virtual bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const 
  {
    if (password == NULL) throw;
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
    /*if( len > (size_t)std::numeric_limits<int>::max() )
      {
      gdcmErrorMacro( "len is too big: " << len );
      return false;
      }*/

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

    const EVP_CIPHER *cipher = EVP_des_ede3_cbc();
    cms = CMS_encrypt(NULL, in, cipher, flags);
    if (!cms)
      {
      gdcmErrorMacro( "Error at creating the CMS strucutre." );
      goto err;
      }

    unsigned char* pwri_tmp = (unsigned char *)BUF_strdup((char *)password);
    if (!pwri_tmp)
      goto err;

    if (!CMS_add0_recipient_password(cms,
        -1, NID_undef, NID_undef,
          pwri_tmp, -1, NULL))
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
      fprintf(stderr, "Error Decrypting Data\n");
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
    /*if( len > (size_t)std::numeric_limits<int>::max() )
      {
      gdcmErrorMacro( "len is too big: " << len );
      return false;
      }*/

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

    const EVP_CIPHER *cipher = EVP_des_ede3_cbc();
    cms = CMS_encrypt(NULL, in, cipher, flags);
    if (!cms)
      {
      gdcmErrorMacro( "Error at creating the CMS strucutre." );
      goto err;
      }

    unsigned char* pwri_tmp = (unsigned char *)BUF_strdup((char *)password);
    if (!pwri_tmp)
      goto err;

    if (!CMS_add0_recipient_password(cms,
        -1, NID_undef, NID_undef,
          pwri_tmp, -1, NULL))
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
      fprintf(stderr, "Error Decrypting Data\n");
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

  virtual void SetCipherType(CipherTypes type)
  {
    cipherType = type;
  }

  //TODO: virtual ???
  CipherTypes GetCipherType() const
  {
    return cipherType;
  }

protected:
  CipherTypes cipherType;
  char * password;
  size_t passwordLength;

};
}

#endif //GDCMCMS_H
