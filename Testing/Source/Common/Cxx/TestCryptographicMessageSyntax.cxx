/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCryptoFactory.h"
#include "Helper.h"

#include <string.h>

#include "gdcmFilename.h"
#include "gdcmTesting.h"

int TestCryptographicMessageSyntax(int, char *[])
{
  const char *input = "12345";
  size_t inputlen = 5;

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  auto_ptr<gdcm::CryptographicMessageSyntax> ocms(ossl->CreateCMSProvider());
  ocms->ParseKeyFile(keypath.c_str());
  ocms->ParseCertificateFile(certpath.c_str());
#endif

#ifdef WIN32
  gdcm::CryptoFactory* capi = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::CAPI);
  auto_ptr<gdcm::CryptographicMessageSyntax> ccms(capi->CreateCMSProvider());
  ccms->ParseCertificateFile(certpath.c_str());
  ccms->ParseKeyFile(keypath.c_str());
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
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    ocms->Encrypt(output, outlen, input, inputlen);
    ocms->Decrypt(decout, decoutlen, output, outlen);
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  decoutlen = 5000;
  ocms->Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(strncmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
#endif

#ifdef WIN32
  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ccms->SetCipherType(ciphers[i]);
    ccms->Encrypt(output, outlen, input, inputlen);
    ccms->Decrypt(decout, decoutlen, output, outlen);
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  decoutlen = 5000;
  ocms->Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(strncmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
#endif

#ifdef WIN32
#ifdef GDCM_USE_SYSTEM_OPENSSL

  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    ccms->SetCipherType(ciphers[i]);
    ocms->Encrypt(output, outlen, input, inputlen);
    ccms->Decrypt(decout, decoutlen, output, outlen);
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }

  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    ccms->SetCipherType(ciphers[i]);
    ccms->Encrypt(output, outlen, input, inputlen);
    ocms->Decrypt(decout, decoutlen, output, outlen);
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }

#endif
#endif

  return 0;
}

int TestPasswordBasedEncryption(int, char *[])
{
  const char *input = "12345";
  size_t inputlen = 5;

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

  std::string encrypted_dicomdir = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/DICOMDIR" );
  std::string encrypted_image = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/IMAGES/IMAGE1" );

  char output[5000], decout[5000];
  size_t outlen = 5000, decoutlen = 5000;

  gdcm::PasswordBasedEncryptionCMS::CipherTypes ciphers[] = {
    gdcm::PasswordBasedEncryptionCMS::AES128_CIPHER,
    gdcm::PasswordBasedEncryptionCMS::AES192_CIPHER,
    gdcm::PasswordBasedEncryptionCMS::AES256_CIPHER,
    gdcm::PasswordBasedEncryptionCMS::DES3_CIPHER,
    };

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  auto_ptr<gdcm::PasswordBasedEncryptionCMS> opbe(ossl->CreatePBECMSProvider());

  opbe->SetPassword("password");
  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    opbe->SetCipherType(ciphers[i]);
    opbe->Encrypt(output, outlen, input, inputlen);
    //if (i == 0)
    //  {
    //  gdcm::Helper::DumpToFile("D:\\passdump", (unsigned char *) output, outlen);
    //  }
    opbe->Decrypt(decout, decoutlen, output, outlen);
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  char * ddir = new char[5000];
  unsigned long ddirlen = 5000;
  gdcm::Helper::LoadFileWin(encrypted_dicomdir.c_str(), ddir, ddirlen);
  outlen = 5000;
  assert(opbe->Decrypt(output, outlen, ddir, ddirlen));
  assert(outlen > 0);
#endif

  return 0;
}
