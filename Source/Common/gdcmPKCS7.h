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
#ifndef __gdcmPKCS7_h
#define __gdcmPKCS7_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for PKCS7 encryption
 *
 * http://www.openssl.org/docs/crypto/PKCS7_encrypt.html
 */
//-----------------------------------------------------------------------------
class PKCS7Internals;
class X509;
class GDCM_EXPORT PKCS7
{
public :
  PKCS7();
  ~PKCS7();

  typedef enum {
    DES_CIPHER,    // DES
    DES3_CIPHER,   // Triple DES
    AES128_CIPHER, // CBC AES
    AES192_CIPHER, // '   '
    AES256_CIPHER  // '   '
  } CipherTypes;

  void SetCipherType( CipherTypes type);
  CipherTypes GetCipherType() const;

  void SetCertificate( X509 *cert );
  const X509 *GetCertificate( ) const;

  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const;

protected:

private:
  PKCS7Internals *Internals;

private:
  PKCS7(const PKCS7&);  // Not implemented.
  void operator=(const PKCS7&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmPKCS7_h
