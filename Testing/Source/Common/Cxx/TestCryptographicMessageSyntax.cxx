/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmCryptoFactory.h"

#include <string.h>

#include "gdcmFilename.h"
#include "gdcmTesting.h"

int TestCryptographicMessageSyntax(int, char *[])
{
  //gdcm::CryptographicMessageSyntax o;
  //(void)o;

  const char *input = "12345";

  gdcm::CryptoFactory& ossl = gdcm::CryptoFactory::getFactoryInstance(0);
  gdcm::CryptographicMessageSyntax& ocms = ossl.CreateCMSProvider();

  gdcm::CryptoFactory& capi = gdcm::CryptoFactory::getFactoryInstance(1);
  gdcm::CryptographicMessageSyntax& ccms = capi.CreateCMSProvider();
    
  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );

  ccms.ParseCertificateFile(certpath.c_str());
  ocms.ParseCertificateFile(certpath.c_str());
  ccms.ParseKeyFile(keypath.c_str());
  ocms.ParseKeyFile(keypath.c_str());
  
  char output[5000], decout[5000];
  size_t outlen = 5000, decoutlen = 5000;

  gdcm::CryptographicMessageSyntax::CipherTypes ciphers[] = {
    gdcm::CryptographicMessageSyntax::AES128_CIPHER,
    gdcm::CryptographicMessageSyntax::AES192_CIPHER,
    gdcm::CryptographicMessageSyntax::AES256_CIPHER,
    gdcm::CryptographicMessageSyntax::DES3_CIPHER
    };
  //int cipher = CryptographicMessageSyntax::CipherTypes::AES128_CIPHER;

  for (int i = 0; i < 4; i++)
  {
    ocms.SetCipherType(ciphers[i]);
    ccms.SetCipherType(ciphers[i]);
    ocms.Encrypt(output, outlen, input, 5);
    ccms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, 5) == 0);
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
    ccms.Encrypt(output, outlen, input, 5);
    ocms.Decrypt(decout, decoutlen, output, outlen);
    assert(strncmp(input, decout, 5) == 0);

    if (i == 0) gdcm::Helper::DumpToFile("D:\\ossldump.bin", (BYTE*)output, outlen);
  }*/

  return 0;
}
