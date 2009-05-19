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
#ifndef __gdcmCryptographicMessageSyntax_h
#define __gdcmCryptographicMessageSyntax_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for CryptographicMessageSyntax encryption
 *
 * http://www.openssl.org/docs/crypto/PKCS7_encrypt.html
 */
//-----------------------------------------------------------------------------
class CryptographicMessageSyntaxInternals;
class GDCM_EXPORT CryptographicMessageSyntax
{
public :
  CryptographicMessageSyntax();
  ~CryptographicMessageSyntax();

  // X.509
  bool ParseCertificateFile( const char *filename );
  bool ParseKeyFile( const char *filename );

  typedef enum {
    DES_CIPHER,    // DES
    DES3_CIPHER,   // Triple DES
    AES128_CIPHER, // CBC AES
    AES192_CIPHER, // '   '
    AES256_CIPHER  // '   '
  } CipherTypes;

  void SetCipherType( CipherTypes type);
  CipherTypes GetCipherType() const;

  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const;

private:
  CryptographicMessageSyntaxInternals *Internals;
private:
  CryptographicMessageSyntax(const CryptographicMessageSyntax&);  // Not implemented.
  void operator=(const CryptographicMessageSyntax&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmCryptographicMessageSyntax_h
