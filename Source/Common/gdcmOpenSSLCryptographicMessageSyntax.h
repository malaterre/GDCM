/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMOPENSSLCMS_H
#define GDCMOPENSSLCMS_H

#include <iostream>
#include "gdcmCryptographicMessageSyntax.h"
//#include "gdcmTypes.h"
using namespace std;
#include <openssl/cms.h>
#include <openssl/evp.h>
namespace gdcm
{
class CryptographicMessageSyntaxInternals;
//-----------------------------------------------------------------------------

/**
 * \brief
 * Class for CryptographicMessageSyntax encryption. This is just a simple
 * wrapper around openssl PKCS7_encrypt functionalities
 *
 * See online documentation
 * http://www.openssl.org/docs/crypto/PKCS7_encrypt.html
 *
 */

class GDCM_EXPORT OpenSSLCMS : public CryptographicMessageSyntax
{
public:
  OpenSSLCMS();
  ~OpenSSLCMS();
  
    // X.509
  bool ParseCertificateFile( const char *filename );
  bool ParseKeyFile( const char *filename );

  /// Set Cipher Type.
  /// Default is: AES256_CIPHER
  void SetCipherType(CipherTypes type);
  //CipherTypes GetCipherType() const;

  /// create a PKCS#7 envelopedData structure
  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool EncryptXP(char *output, size_t &outlen, const char *array, size_t len) { return false;}

private:
  ::stack_st_X509 *recips;//STACK_OF(X509) *recips;
  ::EVP_PKEY *pkey;
  const EVP_CIPHER *cipher;

private:
  OpenSSLCMS(const OpenSSLCMS&);  // Not implemented.
  void operator=(const OpenSSLCMS&);  // Not implemented.
  const EVP_CIPHER *CreateCipher( CryptographicMessageSyntax::CipherTypes ciphertype);

};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //GDCMOPENSSLCMS_H
