/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmCryptoFactory.h"
#include "Helper.h"

#include <string.h>

#include "gdcmFilename.h"
#include "gdcmTesting.h"

int TestCryptographicMessageSyntax(int, char *[])
{
  //gdcm::CryptographicMessageSyntax o;
  //(void)o;

  const char *input = "12345";
  size_t inputlen = 5;

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory& ossl = gdcm::CryptoFactory::getFactoryInstance(0);
  gdcm::CryptographicMessageSyntax& ocms = ossl.CreateCMSProvider();
  ocms.ParseKeyFile(keypath.c_str());
  ocms.ParseCertificateFile(certpath.c_str());
#endif

#ifdef WIN32
  gdcm::CryptoFactory& capi = gdcm::CryptoFactory::getFactoryInstance(1);
  gdcm::CryptographicMessageSyntax& ccms = capi.CreateCMSProvider();
  ccms.ParseCertificateFile(certpath.c_str());
  ccms.ParseKeyFile(keypath.c_str());
#endif
  
  char output[5000], decout[5000];
  size_t outlen = 5000, decoutlen = 5000;

  gdcm::CryptographicMessageSyntax::CipherTypes ciphers[] = {
    gdcm::CryptographicMessageSyntax::AES128_CIPHER,
    gdcm::CryptographicMessageSyntax::AES192_CIPHER,
    gdcm::CryptographicMessageSyntax::AES256_CIPHER,
    gdcm::CryptographicMessageSyntax::DES3_CIPHER,
    };

  char * test_vector;
  unsigned long tvlen;
  gdcm::Helper::LoadFileWin(encrypted_vector.c_str(), test_vector, tvlen);

#ifdef GDCM_USE_SYSTEM_OPENSSL
  for (int i = 0; i < 4; i++)
    {
    ocms.SetCipherType(ciphers[i]);
    ocms.Encrypt(output, outlen, input, inputlen);
    ocms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  ocms.Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(strncmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
#endif

#ifdef WIN32
  for (int i = 0; i < 4; i++)
    {
    ccms.SetCipherType(ciphers[i]);
    ccms.Encrypt(output, outlen, input, inputlen);
    ccms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  ocms.Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(strncmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
#endif

#ifdef WIN32
#ifdef GDCM_USE_SYSTEM_OPENSSL

  for (int i = 0; i < 4; i++)
    {
    ocms.SetCipherType(ciphers[i]);
    ccms.SetCipherType(ciphers[i]);
    ocms.Encrypt(output, outlen, input, inputlen);
    ccms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }

  // IMPORTANT: OpenSSL seems not to be able to decrypt the
  // messages with OAEP RSA padding, maybe that's only available
  // in the cms_* implementation.
  // ...
  // In CAPI can't find a way to specify the RSA padding
  /*for (int i = 0; i < 4; i++)
    {
    ocms.SetCipherType(ciphers[i]);
    ccms.SetCipherType(ciphers[i]);
    ccms.Encrypt(output, outlen, input, inputlen);
    ocms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, inputlen) == 0);

    }*/

#endif
#endif

  return 0;
}
