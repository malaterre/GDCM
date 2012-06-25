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


#define GDCM_EXPORT 



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

  void Encrypt()
  {
  cout << "Encrypt with OpenSSL" << endl;
  }
  void Decrypt()
  {}
  
    // X.509
  bool ParseCertificateFile( const char *filename );
  bool ParseKeyFile( const char *filename );

  /// Set Cipher Type.
  /// Default is: AES256_CIPHER
  //void SetCipherType(CipherTypes type);
  //CipherTypes GetCipherType() const;

  /// create a PKCS#7 envelopedData structure
  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len);
  bool EncryptXP(char *output, size_t &outlen, const char *array, size_t len) { return false;}

  private:
  CryptographicMessageSyntaxInternals *Internals;

  private:
  OpenSSLCMS(const OpenSSLCMS&);  // Not implemented.
  void operator=(const OpenSSLCMS&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //GDCMOPENSSLCMS_H
