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
#include <memory>

namespace gdcm
{

CAPICMS::CAPICMS() : hRsaPrivK(0)
{
  initialized = Initialize();
}

CAPICMS::~CAPICMS() {
  for (vector<PCCERT_CONTEXT>::iterator it = certifList.begin(); it != certifList.end(); ++it)
    {
    if (! CertFreeCertificateContext(*it))
      {
      printf("Error at releasing certificate context.");
      }
    }

  if (hRsaPrivK) CryptDestroyKey(hRsaPrivK);

  if (!CryptReleaseContext(hProv, 0))
    {
    printf("Error when releasing context: 0x%x", GetLastError());
    }
}

bool CAPICMS::ParseCertificateFile( const char *filename ) {
  bool ret = false;
  BYTE *certHexBuf = NULL, *certBin = NULL;
  DWORD certHexBufLen, certBinLen;

  if ( !LoadFile(filename, certHexBuf, certHexBufLen) )
    goto err;

  // Call to get the needed amount of space
  if ( !CryptStringToBinaryA( (LPCSTR)certHexBuf, 0, CRYPT_STRING_BASE64_ANY, NULL, &certBinLen, NULL, NULL ) )
    {
    fprintf( stderr, "CryptStringToBinary failed. Err: %dn", GetLastError() );
    goto err;
    }
  certBin = new BYTE[certBinLen];
  // Convert from PEM format to DER format - removes header and footer and decodes from base64
  if ( !CryptStringToBinaryA( (LPCSTR)certHexBuf, 0, CRYPT_STRING_BASE64_ANY, certBin, &certBinLen, NULL, NULL ) )
    {
    fprintf( stderr, "CryptStringToBinary failed. Err: %dn", GetLastError() );
    goto err;
    }
    
  PCCERT_CONTEXT certContext = NULL;
  certContext = CertCreateCertificateContext(X509_ASN_ENCODING, certBin, certBinLen);
  if (certContext == NULL)
    {
    cout << "error at creating context" << hex << GetLastError();
    goto err;
    }
  certifList.push_back(certContext);

  ret = true;

err:
  if (certBin) delete[] certBin;
  if (certHexBuf) delete[] certHexBuf;

  return ret;
}

bool CAPICMS::ParseKeyFile( const char *filename ) {
  bool ret = false;
  BYTE *keyHexBuffer = NULL, *keyBinBuffer = NULL, *keyBlob = NULL;
  DWORD keyHexBufferLen, keyBinBufferLen, keyBlobLen;
  HCRYPTKEY hKey = NULL;
  
  if (!LoadFile(filename, keyHexBuffer, keyHexBufferLen))
    goto err;

  if ( !CryptStringToBinaryA((LPCSTR)keyHexBuffer, 0, CRYPT_STRING_BASE64_ANY, NULL, &keyBinBufferLen, NULL, NULL) )
    {
    printf("Failed to convert BASE64 private key. Error 0x%.8X\n", GetLastError());
    goto err;
    }
  keyBinBuffer = new BYTE[keyBinBufferLen];
  if ( !CryptStringToBinaryA((LPCSTR)keyHexBuffer, 0, CRYPT_STRING_BASE64_ANY, keyBinBuffer, &keyBinBufferLen, NULL, NULL) )
    {
    printf("Failed to convert BASE64 private key. Error 0x%.8X\n", GetLastError());
    goto err;
    }

  if (!CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, keyBinBuffer, keyBinBufferLen, 0, NULL, NULL, &keyBlobLen))
    {
    printf("Failed to parse private key. Error 0x%.8X\n", GetLastError());
    goto err;
    }
  keyBlob = new BYTE[keyBlobLen];
  if (!CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, keyBinBuffer, keyBinBufferLen, 0, NULL, keyBlob, &keyBlobLen))
    {
    printf("Failed to parse private key. Error 0x%.8X\n", GetLastError());
    goto err;
    }

  if (!CryptImportKey(hProv, keyBlob, keyBlobLen, NULL, 0, &hKey))
    {
    printf("CryptImportKey failed with error 0x%.8X\n", GetLastError());
    goto err;
    }
  if (hRsaPrivK) CryptDestroyKey(hRsaPrivK);
  hRsaPrivK = hKey;
  
  ret = true;
  
err:
  if (keyHexBuffer) delete[] keyHexBuffer;
  if (keyBinBuffer) delete[] keyBinBuffer;
  if (keyBlob) delete[] keyBlob;
  return ret;
}

bool CAPICMS::Encrypt(char *output, size_t &outlen, const char *array, size_t len) const 
{
  CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm = {0};
  EncryptAlgorithm.pszObjId = getCipherObjId();
  
  CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams = {0};
  EncryptParams.cbSize = sizeof(EncryptParams);
  EncryptParams.dwMsgEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;
  EncryptParams.hCryptProv = hProv;
  EncryptParams.ContentEncryptionAlgorithm = EncryptAlgorithm;

  if(! CryptEncryptMessage(&EncryptParams, certifList.size(), (PCCERT_CONTEXT *)&certifList[0], (BYTE *)array, len, (BYTE *)output, (DWORD *)&outlen) )
    {
    printf("Couldn't encrypt message. Error 0x%.8X\n", GetLastError());
    if (GetLastError() == CRYPT_E_UNKNOWN_ALGO)
      {
      gdcmErrorMacro("Unknown encryption algorithm. If on Windows XP please use only 3DES.");
      }
    return false;
    }
  return true;
}

bool CAPICMS::Decrypt(char *output, size_t &outlen, const char *array, size_t len) const 
{
  bool ret = false;
  HCRYPTMSG hMsg = NULL;
  PCMSG_CMS_RECIPIENT_INFO recipientInfo = NULL;
  PCRYPT_ALGORITHM_IDENTIFIER cekAlg = NULL;
  BYTE* bareContent = NULL;
  struct {
    BLOBHEADER header;
    DWORD cbKeySize;
    BYTE rgbKeyData[32]; //the maximum is 256 bit for aes
  } keyBlob = {0};

  if (! (hMsg = CryptMsgOpenToDecode(CRYPT_ASN_ENCODING | X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, CMSG_ENVELOPED_DATA_PKCS_1_5_VERSION, NULL, NULL, NULL)) )
    {
    printf("MsgOpenToDecode failed with error 0x%.8X\n", GetLastError());
    goto err;
    }
    
  if(! CryptMsgUpdate(hMsg, (BYTE*)array, len, TRUE))
    {
    printf("MsgUpdate failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  DWORD dwMessageType, cbMessageTypeLen;
  if(! CryptMsgGetParam(hMsg, CMSG_TYPE_PARAM, 0, &dwMessageType, &cbMessageTypeLen)) 
    {
    printf("CryptMsgGetParam CMSG_TYPE_PARAM failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  if(dwMessageType != CMSG_ENVELOPED) 
    {
    printf("Wrong message type ( != CMSG_ENVELOPED )\n");
    goto err;
    }

  ALG_ID kekAlg;
  DWORD kekAlgLen;
  if(! CryptGetKeyParam(hRsaPrivK, KP_ALGID, (BYTE*)&kekAlg, &kekAlgLen, 0)) 
    {
    printf("MsgGetParam KP_ALGID failed with error 0x%.8X\n", GetLastError());
    goto err;
    }
  if (kekAlg != CALG_RSA_KEYX) 
    {
    printf("Key encryption algorithm is not RSA.");
    goto err;
    }

  DWORD nrOfRecipeints, nrOfRecipientsLen;
  if(! CryptMsgGetParam(hMsg, CMSG_RECIPIENT_COUNT_PARAM, 0, &nrOfRecipeints, &nrOfRecipientsLen))
    {
    printf("Decode CMSG_RECIPIENT_COUNT_PARAM failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  DWORD cekLen;
  BYTE* cek = NULL;
  BOOL foundRecipient = FALSE;
  for (DWORD i=0; i < nrOfRecipeints; i++)
    {
    if (recipientInfo) delete[] recipientInfo;

    DWORD cbRecipientInfoLen;
    if(! CryptMsgGetParam(hMsg, CMSG_CMS_RECIPIENT_INFO_PARAM, i, NULL, &cbRecipientInfoLen))
      {
      printf("MsgGetParam CMSG_CMS_RECIPIENT_INFO_PARAM size failed with error 0x%.8X\n", GetLastError());
      goto err;
      }
    recipientInfo = (PCMSG_CMS_RECIPIENT_INFO) new BYTE[cbRecipientInfoLen];
    if(! CryptMsgGetParam(hMsg, CMSG_CMS_RECIPIENT_INFO_PARAM, i, recipientInfo, &cbRecipientInfoLen))
      {
      printf("MsgGetParam CMSG_CMS_RECIPIENT_INFO_PARAM failed with error 0x%.8X\n", GetLastError());
      goto err;
      }

    DWORD rsaPadding = NULL;
    if (strcmp(recipientInfo->pKeyTrans->KeyEncryptionAlgorithm.pszObjId, szOID_RSAES_OAEP) == 0)
      {
      rsaPadding = CRYPT_OAEP;
      }

    //cek - content encryption key
    cekLen = recipientInfo->pKeyTrans->EncryptedKey.cbData;
    cek = recipientInfo->pKeyTrans->EncryptedKey.pbData;
    ReverseBytes(cek, cekLen);

    if (foundRecipient = CryptDecrypt(hRsaPrivK, NULL, TRUE, rsaPadding, cek, &cekLen))
      break;
    } // end loop recipients
  
  if (!foundRecipient)
    {
      gdcmErrorMacro( "No recipient found with the specified private key." );
      goto err;
    }

  DWORD cekAlgLen;
  if(! CryptMsgGetParam(hMsg, CMSG_ENVELOPE_ALGORITHM_PARAM, 0, NULL, &cekAlgLen))
    {
    printf("MsgGetParam CMSG_ENVELOPE_ALGORITHM_PARAM failed with error 0x%.8X\n", GetLastError());
    goto err;
    }
  cekAlg = (PCRYPT_ALGORITHM_IDENTIFIER) new BYTE[cekAlgLen];
  if(! CryptMsgGetParam(hMsg, CMSG_ENVELOPE_ALGORITHM_PARAM, 0, cekAlg, &cekAlgLen))
    {
    printf("MsgGetParam CMSG_ENVELOPE_ALGORITHM_PARAM failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  HCRYPTKEY hCEK;
  keyBlob.header.bType = PLAINTEXTKEYBLOB;
  keyBlob.header.bVersion = CUR_BLOB_VERSION;
  keyBlob.header.reserved = 0;
  keyBlob.header.aiKeyAlg = getAlgIdByObjId(cekAlg->pszObjId);
  keyBlob.cbKeySize = cekLen;
  assert(cekLen <= 32);
  memcpy(keyBlob.rgbKeyData, cek, cekLen);

  if (!CryptImportKey(hProv, (BYTE*)&keyBlob, sizeof(keyBlob), NULL, NULL, &hCEK))
    {
    fprintf( stderr, "Import AES key failed. Err: 0x%.8X", GetLastError() );
    goto err;
    }

  if(! CryptSetKeyParam(hCEK, KP_IV, (BYTE *) cekAlg->Parameters.pbData+2, 0)) //+2 for ASN header ???
    {
    printf("SetKeyParam KP_IV failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  DWORD dwMode = CRYPT_MODE_CBC;
  if(! CryptSetKeyParam(hCEK, KP_MODE, (BYTE*) &dwMode, 0))
    {
    printf("SetKeyParam KP_MODE failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  DWORD bareContentLen;
  if(! CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, NULL, &bareContentLen))
    {
    printf("MsgGetParam CMSG_BARE_CONTENT_PARAM size failed with error 0x%.8X\n", GetLastError());
    goto err;
    }
  bareContent = new BYTE[bareContentLen];
  if(! CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, bareContent, &bareContentLen))
    {
    printf("MsgGetParam CMSG_BARE_CONTENT_PARAM failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

  if (! CryptDecrypt(hCEK, NULL, TRUE, NULL, bareContent, &bareContentLen))
    {
    printf("Decrypting data failed with error 0x%.8X\n", GetLastError());
    goto err;
    }

    if (bareContentLen > outlen)
    {
    gdcmErrorMacro( "Supplied output buffer too small: " << bareContentLen << " bytes needed." );
    goto err;
    }

    memcpy(output, bareContent, bareContentLen);
    outlen = bareContentLen;
     
    ret = true;
err:
    if (hMsg) CryptMsgClose(hMsg);
    if (recipientInfo) delete[] recipientInfo;
    if (bareContent) delete[] bareContent;
    if (cekAlg) delete[] cekAlg;

  return ret;
}

ALG_ID CAPICMS::getAlgIdByObjId(const char * pszObjId)
{
  if (strcmp(pszObjId, szOID_NIST_AES128_CBC) == 0)
    {
    return CALG_AES_128;
    }
  else if (strcmp(pszObjId, szOID_NIST_AES192_CBC) == 0)
    {
    return CALG_AES_192;
    }
  else if (strcmp(pszObjId, szOID_NIST_AES256_CBC) == 0)
    {
    return CALG_AES_256;
    }
  else if (strcmp(pszObjId, szOID_RSA_DES_EDE3_CBC) == 0)
    {
    return CALG_3DES;
    }
  return 0;
}

LPSTR CAPICMS::getCipherObjId() const
{
  if (cipherType == AES128_CIPHER)
    {
    return szOID_NIST_AES128_CBC;
    }
  else if (cipherType == AES192_CIPHER)
    {
    return szOID_NIST_AES192_CBC;
    }
  else if (cipherType == AES256_CIPHER)
    {
    return szOID_NIST_AES256_CBC;
    }
  else if (cipherType == DES3_CIPHER)
    {
    return szOID_RSA_DES_EDE3_CBC;
    }
  return 0;
}

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
  else if (dwResult == NTE_KEYSET_NOT_DEF)
    {
      //Probably WinXP
      if (!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV_XP /*"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)"*/, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) //CRYPT_VERIFYCONTEXT aes decr in cryptmsgcontrol not working
      {
      dwResult = GetLastError();
      if (dwResult == NTE_BAD_KEYSET)
        {
        if (!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV_XP /*"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)"*/, PROV_RSA_AES, CRYPT_NEWKEYSET | CRYPT_VERIFYCONTEXT))
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
    }
    else 
      {
      dwResult = GetLastError();
      return false;
      }
    }
  return true;
}

void CAPICMS::ReverseBytes(BYTE* data, DWORD len)
{
  BYTE temp;
  for (DWORD i = 0; i < len/2; i++)
  {
    temp = data[len-i-1];
    data[len-i-1] = data[i];
    data[i] = temp;
  }
}

bool CAPICMS::LoadFile(const char * filename, BYTE* & buffer, DWORD & bufLen)
{
  FILE * f = fopen(filename, "rb");
  if (f == NULL)
    {
    gdcmErrorMacro("Couldn't open the file: " << filename);
    return false;
    }
  fseek(f, 0L, SEEK_END);
  long sz = ftell(f);
  //fseek(f, 0L, SEEK_SET);
  rewind(f);
  /*if (bufLen < sz)
    {
    printf("Buffer too small to load the file: %d < %d\n", bufLen, sz);
    return false;
    }
    */
  buffer = new BYTE[sz];
  bufLen = sz;

  while (sz)
  {
    sz -= fread(buffer + bufLen - sz, sizeof(BYTE), sz, f);
  }

  return true;
}

}
