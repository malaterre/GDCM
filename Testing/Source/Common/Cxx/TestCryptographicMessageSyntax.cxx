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

static const gdcm::CryptographicMessageSyntax::CipherTypes ciphers[] = {
  gdcm::CryptographicMessageSyntax::AES128_CIPHER,
  gdcm::CryptographicMessageSyntax::AES192_CIPHER,
  gdcm::CryptographicMessageSyntax::AES256_CIPHER,
  gdcm::CryptographicMessageSyntax::DES3_CIPHER
  };

static std::pair<gdcm::CryptographicMessageSyntax::CipherTypes, std::string> cip2str_data[] = {
    std::make_pair(gdcm::CryptographicMessageSyntax::AES128_CIPHER, "AES128"),
    std::make_pair(gdcm::CryptographicMessageSyntax::AES192_CIPHER, "AES192"),
    std::make_pair(gdcm::CryptographicMessageSyntax::AES256_CIPHER, "AES256"),
    std::make_pair(gdcm::CryptographicMessageSyntax::DES3_CIPHER,   "3DES")
};

static std::map<gdcm::CryptographicMessageSyntax::CipherTypes, std::string> cip2str(cip2str_data,
    cip2str_data + sizeof cip2str_data / sizeof cip2str_data[0]);

const char * const tstr = "12345";
const int tstr_l = strlen(tstr);
#define BUFSZ 5000

bool TestCMSProvider(gdcm::CryptographicMessageSyntax& cms, const char * provName)
{
  bool ret = true;
  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    cms.SetCipherType(ciphers[i]);
    bool encryptSuccess = cms.Encrypt(encout, encoutlen, tstr, tstr_l);
    if (!encryptSuccess)
      {
      gdcmWarningMacro(provName << " using " << cip2str[ciphers[i]] << ": encryption failed");
      ret = false;
      break;
      }
    bool decryptSuccess = cms.Decrypt(decout, decoutlen, encout, encoutlen);
    if (!decryptSuccess)
      {
      std::cerr << provName << " using " << cip2str[ciphers[i]] << ": decryption failed" << std::endl;
      ret = false;
      break;
      }
    if (decoutlen != tstr_l)
      {
      std::cerr << provName << " using " << cip2str[ciphers[i]] << ": decryted length different from original (" << decoutlen << " != " << tstr_l << ")" << std::endl;
      }
    if (memcmp(tstr, decout, tstr_l) != 0)
      {
      std::cerr << provName << " using " << cip2str[ciphers[i]] << ": decryted data different from original" << std::endl;
      }
    }
  char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
  size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
  //cms.Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(memcmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
  
  return true;
}

int TestCryptographicMessageSyntax(int, char *[])
{
  std::string certpath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/certificate.pem" );
  std::string keypath = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/privatekey.pem" );
  std::string encrypted_vector = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/encrypted_text" );

  char * test_vector;
  size_t tvlen;
  if (!LoadFile(encrypted_vector.c_str(), test_vector, tvlen))
    {
    /////////////////???
    }

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ocms(ossl->CreateCMSProvider());
  ocms->ParseKeyFile(keypath.c_str());
  ocms->ParseCertificateFile(certpath.c_str());
  TestCMSProvider(*ocms, "OpenSSL");
#endif

#ifdef WIN32
  gdcm::CryptoFactory* capi = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::CAPI);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ccms(capi->CreateCMSProvider());
  ccms->ParseCertificateFile(certpath.c_str());
  ccms->ParseKeyFile(keypath.c_str());
  TestCMSProvider(*ccms, "CAPI");
#endif
  
/*
#ifdef GDCM_USE_SYSTEM_OPENSSL
{  
  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    ocms->SetCipherType(ciphers[i]);
    bool encryptSuccess = ocms->Encrypt(encout, encoutlen, tstr, tstr_l);
    if (!encryptSuccess)
      {
      gdcmWarningMacro("Encryption with OpenSSL failed using " << cip2str[ciphers[i]]);
      break;
      }
    bool decryptSuccess = ocms->Decrypt(decout, decoutlen, encout, encoutlen);
    if (!decryptSuccess)
      {
      std::cerr << "Encryption with OpenSSL failed using " << cip2str[ciphers[i]];
      break;
      }
    assert(decoutlen == tstr_l);
    assert(memcmp(tstr, decout, tstr_l) == 0);
    }
  char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
  size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
  ocms->Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(memcmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
}
#endif*/

/*#ifdef WIN32
{  
  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    ccms->SetCipherType(ciphers[i]);
    ccms->Encrypt(encout, encoutlen, tstr, tstr_l);
    ccms->Decrypt(decout, decoutlen, encout, encoutlen);
    assert(decoutlen == tstr_l);
    assert(memcmp(tstr, decout, tstr_l) == 0);
    }
  char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
  size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
  ocms->Decrypt(decout, decoutlen, test_vector, tvlen);
  assert(decoutlen == strlen("1234567890abcdefghijklmnopqrstuvwxyz"));
  assert(memcmp(decout, "1234567890abcdefghijklmnopqrstuvwxyz", strlen("1234567890abcdefghijklmnopqrstuvwxyz")) == 0);
}
#endif*/

#ifdef WIN32
#ifdef GDCM_USE_SYSTEM_OPENSSL

  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    ocms->SetCipherType(ciphers[i]);
    ccms->SetCipherType(ciphers[i]);
    ocms->Encrypt(encout, encoutlen, tstr, tstr_l);
    ccms->Decrypt(decout, decoutlen, encout, encoutlen);
    assert(decoutlen == tstr_l);
    assert(memcmp(tstr, decout, tstr_l) == 0);
    }

  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    ocms->SetCipherType(ciphers[i]);
    ccms->SetCipherType(ciphers[i]);
    ccms->Encrypt(encout, encoutlen, tstr, tstr_l);
    ocms->Decrypt(decout, decoutlen, encout, encoutlen);
    assert(decoutlen == tstr_l);
    assert(memcmp(tstr, decout, tstr_l) == 0);
    }

#endif
#endif

  return 0;
}

int TestPasswordBasedEncryption(int, char *[])
{
  std::string encrypted_dicomdir = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/DICOMDIR" );
  std::string encrypted_image = gdcm::Filename::Join(gdcm::Testing::GetSourceDirectory(), "/Testing/Source/Data/securedicomfileset/IMAGES/IMAGE1" );

  //char encout[5000], decout[5000];
  //size_t outlen = 5000, decoutlen = 5000;

#ifdef GDCM_USE_SYSTEM_OPENSSL
  gdcm::CryptoFactory* ossl = gdcm::CryptoFactory::getFactoryInstance(gdcm::CryptoFactory::OPENSSL);
  std::auto_ptr<gdcm::CryptographicMessageSyntax> ocms(ossl->CreateCMSProvider());

  ocms->SetPassword("password");
  for (int i = 0; i < 4; i++)
    {
    char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
    size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
    ocms->SetCipherType(ciphers[i]);
    ocms->Encrypt(encout, encoutlen, tstr, tstr_l);
    ocms->Decrypt(decout, decoutlen, encout, encoutlen);
    assert(decoutlen == tstr_l);
    assert(memcmp(tstr, decout, tstr_l) == 0);
    }
  char encout[BUFSZ] = {0}, decout[BUFSZ] = {0};
  size_t encoutlen = BUFSZ, decoutlen = BUFSZ;
  char * ddir = new char[5000];
  size_t ddirlen = 5000;
  LoadFile(encrypted_dicomdir.c_str(), ddir, ddirlen);
  assert(ocms->Decrypt(encout, encoutlen, ddir, ddirlen));
  assert(encoutlen > 0);
#endif

  return 0;
}
