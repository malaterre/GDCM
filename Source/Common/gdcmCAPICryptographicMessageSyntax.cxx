/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "gdcmCAPICryptographicMessageSyntax.h"

namespace gdcm
{

CAPICMS::~CAPICMS() {
  for (vector<PCCERT_CONTEXT>::iterator it = certifList.begin(); it != certifList.end(); it++)
    {
    if (! CertFreeCertificateContext(*it))
      {
      printf("Error at releasing certificate context.");
      }
    }
  //relese CSP
  if (!CryptReleaseContext(hProv, 0))
    {
    printf("Error when releasing context: 0x%x", GetLastError());
    }
}

void CAPICMS::Encrypt()
{}

void CAPICMS::Decrypt()
{
  cout << "Decrypt with CAPI" << endl;
}

bool CAPICMS::ParseCertificateFile( const char *filename ) {
  bool ret = true;
  BYTE * certHexBuf = NULL;
  DWORD certHexBufLen;

  BYTE * certBin = NULL;
  DWORD certBinLen;

  try
  {
    if (!Helper::LoadFileWin(filename, certHexBuf, certHexBufLen))
      {
      //return false;
      throw NULL;
      }

    // Call to get the needed amount of space
    if ( !CryptStringToBinaryA( (LPCSTR)certHexBuf, 0, CRYPT_STRING_BASE64_ANY, NULL, &certBinLen, NULL, NULL ) )
      {
      fprintf( stderr, "CryptStringToBinary failed. Err: %dn", GetLastError() );
      //return false;
      throw NULL;
      }
    cout << certBinLen;
    certBin = new BYTE[certBinLen];
    
    // Convert from PEM format to DER format - removes header and footer and decodes from base64
    if ( !CryptStringToBinaryA( (LPCSTR)certHexBuf, 0, CRYPT_STRING_BASE64_ANY, certBin, &certBinLen, NULL, NULL ) )
      {
      fprintf( stderr, "CryptStringToBinary failed. Err: %dn", GetLastError() );
      //return false;
      throw NULL;
      }

    PCCERT_CONTEXT certContext = NULL;
    certContext = CertCreateCertificateContext(X509_ASN_ENCODING, (BYTE*)certBin, certBinLen);

    if (certContext == NULL)
      {
      cout << "error at creating context" << hex << GetLastError();
      //return false;
      throw NULL;
      }

    certifList.push_back(certContext);
  }
  catch (void *)
  {
    ret =false;
  }

  if (certBin) delete[] certBin;
  if (certHexBuf) delete[] certHexBuf;

  return ret;
}

bool CAPICMS::ParseKeyFile( const char *filename ) {
  bool ret = true;
  BYTE * keyHexBuffer;
  DWORD keyHexBufferLen, keyBinBufferLen, keyBlobLen;
  LPBYTE keyBinBuffer, keyBlob;
  HCRYPTKEY hKey = NULL;
  try {
    if (!Helper::LoadFileWin(filename, keyHexBuffer, keyHexBufferLen))
      {
      //return false;
      throw NULL;
      }

    if (!CryptStringToBinaryA((LPCSTR)keyHexBuffer, 0, CRYPT_STRING_BASE64_ANY, NULL, &keyBinBufferLen, NULL, NULL))
      {
      printf("Failed to convert BASE64 private key. Error 0x%.8X\n", GetLastError());
      throw NULL;
      }

    keyBinBuffer = new BYTE[keyBinBufferLen];
    if (!CryptStringToBinaryA((LPCSTR)keyHexBuffer, 0, CRYPT_STRING_BASE64_ANY, keyBinBuffer, &keyBinBufferLen, NULL, NULL))
      {
      printf("Failed to convert BASE64 private key. Error 0x%.8X\n", GetLastError());
      throw NULL;
      }

    if (!CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, keyBinBuffer, keyBinBufferLen, 0, NULL, NULL, &keyBlobLen))
      {
      printf("Failed to parse private key. Error 0x%.8X\n", GetLastError());
      throw NULL;
      }
        
    keyBlob = (LPBYTE) LocalAlloc(0, keyBlobLen);
    if (!CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, keyBinBuffer, keyBinBufferLen, 0, NULL, keyBlob, &keyBlobLen))
      {
      printf("Failed to parse private key. Error 0x%.8X\n", GetLastError());
      throw NULL;
      }

    if (!CryptImportKey(hProv, keyBlob, keyBlobLen, NULL, 0, &hKey))
      {
      printf("CryptImportKey failed with error 0x%.8X\n", GetLastError());
      throw NULL;
      }
    if (hRsaPrivK) CryptDestroyKey(hRsaPrivK);
    hRsaPrivK = hKey;
  }
  catch (void*)
    {
    ret = false;
    }
  if (keyBinBuffer) delete[] keyBinBuffer;
  return ret;
}

bool CAPICMS::Encrypt(char *output, size_t &outlen, const char *array, size_t len) const {
  //DWORD EncryptAlgSize;
  CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm = {0};
  //EncryptAlgSize = sizeof(EncryptAlgorithm);
  //memset(&EncryptAlgorithm, 0, EncryptAlgSize);
  EncryptAlgorithm.pszObjId = getCipherObjId();

  CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams = {0};
  //DWORD EncryptParamsSize;
  //EncryptParamsSize = sizeof(EncryptParams);
  //memset(&EncryptParams, 0, EncryptParamsSize);
  EncryptParams.cbSize = sizeof(EncryptParams);//EncryptParamsSize;
  EncryptParams.dwMsgEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;
  EncryptParams.hCryptProv = hProv;
  EncryptParams.ContentEncryptionAlgorithm = EncryptAlgorithm;

  if(! CryptEncryptMessage(&EncryptParams, certifList.size(), (PCCERT_CONTEXT *)&certifList[0], (BYTE *)array, len, (BYTE *)output, (DWORD *)&outlen) )
    {
    printf("Failed to parse private key. Error 0x%.8X\n", GetLastError());
    return false;
    }
  return true;
}

bool CAPICMS::EncryptXP(char *output, size_t &outlen, const char *array, size_t len) {
  char *cont = "12345";

  CMSG_ENVELOPED_ENCODE_INFO encodeInfo = {0};
  encodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
  encodeInfo.ContentEncryptionAlgorithm.pszObjId = szOID_NIST_AES128_CBC;//szOID_RSA_DES_EDE3_CBC;//
  //encodeInfo.ContentEncryptionAlgorithm.Parameters = 
  encodeInfo.cRecipients = 0;
  encodeInfo.rgpRecipients = NULL;
  encodeInfo.hCryptProv = hProv;
  encodeInfo.pvEncryptionAuxInfo = NULL;
    

  DWORD cbLEN;
  if (! (cbLEN = CryptMsgCalculateEncodedLength(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, CMSG_ENVELOPED, &encodeInfo, szOID_RSA_envelopedData, 5)))
  {
    printf("MsgCalculateEncodedLength failed with error 0x%.8X\n", GetLastError());
  }
    
  //printf("%d\n", cbLEN);

  if (! CryptMsgOpenToEncode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, CMSG_ENVELOPED, &encodeInfo, szOID_RSA_envelopedData, NULL))
  {
    printf("MsgOpenToEncode failed with error 0x%.8X\n", GetLastError());
  }

  BYTE out[1000];
  DWORD olen = 1000;
  CRYPT_CONTENT_INFO eci = {0};
  eci.pszObjId = szOID_NIST_AES128_CBC"\x04\x01""d";
  eci.Content.pbData = (BYTE*)"12345";
  eci.Content.cbData = 5;
  if (! CryptEncodeObjectEx(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING, PKCS_CONTENT_INFO, &eci, NULL, NULL, out, &olen))
  {
    printf("CryptEncodeObjectEx PKCS_CONTENT_INFO failed with error 0x%.8X\n", GetLastError());
  }

  CRYPT_DER_BLOB derb = {0};
  derb.pbData = (BYTE*)"1234";
  derb.cbData = 4;

  CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY cis;
  cis.pszObjId = szOID_NIST_AES128_CBC;
  cis.rgValue = &derb;
  olen = 1000;
  if (! CryptEncodeObjectEx(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING, PKCS_CONTENT_INFO_SEQUENCE_OF_ANY, &cis, NULL, NULL, out, &olen))
  {
    printf("CryptEncodeObjectEx SEQUENCE_OF_ANY failed with error 0x%.8X\n", GetLastError());
  }

  CRYPT_OID_INFO oi;
  //oi.

  //CryptRegisterOIDInfo(

  PCCRYPT_OID_INFO inf = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, szOID_NIST_AES128_CBC, 0);
  cout << inf->pszOID << endl;

  /*CRYPT_DATA_BLOB db;
  db.pbData = (BYTE*)"qqq";
  db.cbData = 3;

  if (! CryptEncodeObjectEx(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING, X509_OCTET_STRING, &db, NULL, NULL, out, &olen))
  {
    printf("CryptEncodeObjectEx X509_OCTET_STRING failed with error 0x%.8X\n", GetLastError());
  }*/

  Helper::PrintHex(out, olen);
  Helper::DumpToFile("D:\\Desktop\\exp1", out, olen);
    
  return false;
    
  DWORD EncryptAlgSize;
  CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm;
  EncryptAlgSize = sizeof(EncryptAlgorithm);
  memset(&EncryptAlgorithm, 0, EncryptAlgSize);
  //EncryptAlgorithm.pszObjId = szOID_RSA_RC4;
  EncryptAlgorithm.pszObjId = "2.16.840.1.101.3.4.1.2";//szOID_RSA_DES_EDE3_CBC;

  CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams;
  DWORD EncryptParamsSize;
  EncryptParamsSize = sizeof(EncryptParams);
  memset(&EncryptParams, 0, EncryptParamsSize);
  EncryptParams.cbSize = EncryptParamsSize;
  EncryptParams.dwMsgEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;
  EncryptParams.hCryptProv = hProv;
  EncryptParams.ContentEncryptionAlgorithm = EncryptAlgorithm;

  //BOOL ret = CryptEncryptMessage(&EncryptParams, 1/*certList.size()*/, /*(PCCERT_CONTEXT [])certList.front()*/ certa, (BYTE *)array, len, (BYTE *)output, (DWORD *)&outlen);
    
  DWORD err = GetLastError();

  //cout << "Enc rez: " << rt << endl;

  return false;
}

LPSTR CAPICMS::getCipherObjId() const
{
  if (cipherType == CipherTypes::AES128_CIPHER)
    {
    return szOID_NIST_AES128_CBC;
    }
  else if (cipherType == CipherTypes::AES192_CIPHER)
    {
    return szOID_NIST_AES192_CBC;
    }
  else if (cipherType == CipherTypes::AES256_CIPHER)
    {
    return szOID_NIST_AES256_CBC;
    }
  else if (cipherType == CipherTypes::DES3_CIPHER)
    {
    return szOID_RSA_DES_EDE3_CBC;
    }
  return 0;
}

// Need to append L" (Prototype)" to the provider type in Windows XP.
bool CAPICMS::Initialize() {
  DWORD dwResult;
  if (!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) //CRYPT_VERIFYCONTEXT aes decr in cryptmsgcontrol not working
    {
    dwResult = GetLastError();
    if (dwResult == NTE_BAD_KEYSET)
      {
      if (!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET | CRYPT_VERIFYCONTEXT))
        {
        dwResult = GetLastError();
        cout << "Error [0x%x]: CryptAcquireContext() failed.";
        return false;
        }
      }
    else 
      {
      dwResult = GetLastError();
      return false;
      }
    }
  initialized = true;
  return true;
}
}
