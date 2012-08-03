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
#include <string.h>
#include <memory>

#include "gdcmFilename.h"
#include "gdcmTesting.h"

static bool LoadFile(const char * filename, char* & buffer, size_t & bufLen)
{
  FILE * f = fopen(filename, "rb");
  if (f == NULL)
    {
    gdcmErrorMacro("Couldn't open the file: " << filename);
    return false;
    }
  fseek(f, 0L, SEEK_END);
  long sz = ftell(f);
  rewind(f);
  buffer = new char[sz];
  bufLen = sz;
  while (sz)
    sz -= fread(buffer + bufLen - sz, sizeof(char), sz, f);
  return true;
}

int TestCryptographicMessageSyntax(int, char *[])
{
  const char *input = "12345";
  size_t inputlen = 5;

  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSLP7)->CreateCMSProvider();//FIXME: destroy

  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ocms(ossl->CreateCMSProvider());
  assert(ocms->ParseKeyFile(keypath.c_str()));
  assert(ocms->ParseCertificateFile(certpath.c_str()));
#endif

#ifdef WIN32
  gdcm::CryptoFactory* capi = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::CAPI);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ccms(capi->CreateCMSProvider());
  assert(ccms->ParseCertificateFile(certpath.c_str()));
  assert(ccms->ParseKeyFile(keypath.c_str()));
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
  size_t tvlen;
  assert(LoadFile(encrypted_vector.c_str(), test_vector, tvlen));

#ifdef GDCM_USE_SYSTEM_OPENSSL
  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    assert(ocms->Encrypt(output, outlen, input, inputlen));
    assert(ocms->Decrypt(decout, decoutlen, output, outlen));
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  decoutlen = 5000;
  assert(ocms->Decrypt(decout, decoutlen, test_vector, tvlen));
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(strncmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
#endif

#ifdef WIN32
  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ccms->SetCipherType(ciphers[i]);
    assert(ccms->Encrypt(output, outlen, input, inputlen));
    assert(ccms->Decrypt(decout, decoutlen, output, outlen));
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  decoutlen = 5000;
  assert(ocms->Decrypt(decout, decoutlen, test_vector, tvlen));
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
    assert(ocms->Encrypt(output, outlen, input, inputlen));
    assert(ccms->Decrypt(decout, decoutlen, output, outlen));
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }

  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    ccms->SetCipherType(ciphers[i]);
    assert(ccms->Encrypt(output, outlen, input, inputlen));
    assert(ocms->Decrypt(decout, decoutlen, output, outlen));
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

  std::string encrypted_dicomdir = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/DICOMDIR" );
  std::string encrypted_image = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/IMAGES/IMAGE1" );

  char output[5000], decout[5000];
  size_t outlen = 5000, decoutlen = 5000;

  gdcm::CryptographicMessageSyntax::CipherTypes ciphers[] = {
    gdcm::CryptographicMessageSyntax::AES128_CIPHER,
    gdcm::CryptographicMessageSyntax::AES192_CIPHER,
    gdcm::CryptographicMessageSyntax::AES256_CIPHER,
    gdcm::CryptographicMessageSyntax::DES3_CIPHER,
    };

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ocms(ossl->CreateCMSProvider());

  assert(ocms->SetPassword("password"));
  for (int i = 0; i < 4; i++)
    {
    outlen = 5000;
    decoutlen = 5000;
    ocms->SetCipherType(ciphers[i]);
    assert(ocms->Encrypt(output, outlen, input, inputlen));
    assert(ocms->Decrypt(decout, decoutlen, output, outlen));
    assert(decoutlen == inputlen);
    assert(strncmp(input, decout, inputlen) == 0);
    }
  char * ddir = new char[5000];
  size_t ddirlen = 5000;
  assert(LoadFile(encrypted_dicomdir.c_str(), ddir, ddirlen));
  outlen = 5000;
  assert(ocms->Decrypt(output, outlen, ddir, ddirlen));
  assert(outlen > 0);
#endif

  return 0;
}
