#ifndef GDCMCMS_H
#define GDCMCMS_H

#include <iostream>
using namespace std;

#include "gdcmTypes.h"

namespace gdcm
{
class GDCM_EXPORT CryptographicMessageSyntax
{
public:
  
  CryptographicMessageSyntax() : cipherType(AES128_CIPHER)
  {
  }

  virtual ~CryptographicMessageSyntax() {}

  typedef enum {
    DES_CIPHER,    // DES
    DES3_CIPHER,   // Triple DES
    AES128_CIPHER, // CBC AES
    AES192_CIPHER, // '   '
    AES256_CIPHER  // '   '
  } CipherTypes;

     // X.509
  virtual bool ParseCertificateFile( const char *filename ) = 0;
  virtual bool ParseKeyFile( const char *filename ) = 0;

  /// create a PKCS#7 envelopedData structure
  virtual bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const = 0;
  virtual bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const = 0;
  virtual bool EncryptXP(char *output, size_t &outlen, const char *array, size_t len) = 0;

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

};
}

#endif //GDCMCMS_H