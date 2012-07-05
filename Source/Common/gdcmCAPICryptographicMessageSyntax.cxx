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
    if (!Helper::LoadFileWin(filename, (char *&)certHexBuf, certHexBufLen))
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
    if (!Helper::LoadFileWin(filename, (char *&)keyHexBuffer, keyHexBufferLen))
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

bool CAPICMS::Decrypt(char *output, size_t &outlen, const char *array, size_t len) {
  /*CRYPT_DATA_BLOB EncryptedMessageBlob;
  EncryptedMessageBlob.cbData = len;
  EncryptedMessageBlob.pbData = (BYTE*) array; //???*/
  bool ret = true;
  HCRYPTMSG hMsg = NULL;
  PCMSG_CMS_RECIPIENT_INFO recipientInfo = NULL;
  PCRYPT_ALGORITHM_IDENTIFIER cekAlg = NULL;
  BYTE* bareContent = NULL;

  try
    {
    if (! (hMsg = CryptMsgOpenToDecode(CRYPT_ASN_ENCODING | X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, CMSG_ENVELOPED_DATA_PKCS_1_5_VERSION, NULL, NULL, NULL)) )
      {
      printf("MsgOpenToDecode failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
    
    if(! CryptMsgUpdate(hMsg, (BYTE*)array, len, TRUE))
      {
      printf("MsgUpdate failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
    

    DWORD dwMessageType, cbMessageTypeLen;
    if(! CryptMsgGetParam(hMsg, CMSG_TYPE_PARAM, 0, &dwMessageType, &cbMessageTypeLen)) 
      {
      printf("CryptMsgGetParam CMSG_TYPE_PARAM failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }

    if(dwMessageType == CMSG_ENVELOPED) 
      {
      //printf("The message is an enveloped message. Proceed. \n");
      }
    else 
      {
      printf("Wrong message type ( != CMSG_ENVELOPED )\n");
      //return false;
      throw NULL;
      }

    ALG_ID kekAlg;
    DWORD kekAlgLen;
    if(! CryptGetKeyParam(hRsaPrivK, KP_ALGID, (BYTE*)&kekAlg, &kekAlgLen, 0)) 
      {
      printf("MsgGetParam KP_ALGID failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
    if (kekAlg != CALG_RSA_KEYX) 
      {
      printf("Key encryption algorithm is not RSA.");
      //return false;
      throw NULL;
      }

        //DWORD kl, klLen;
  //CryptGetKeyParam(hRsaPrivK, KP_BLOCKLEN, (BYTE*)&kl, &klLen, 0);
  //printf("%d\n", kl);
    
    DWORD nrOfRecipeints, nrOfRecipientsLen;
    if(! CryptMsgGetParam(hMsg, CMSG_RECIPIENT_COUNT_PARAM, 0, &nrOfRecipeints, &nrOfRecipientsLen))
      {
      printf("Decode CMSG_RECIPIENT_COUNT_PARAM failed with error 0x%.8X\n", GetLastError());
      throw NULL;
      }
      ///////////////////////////////////////////////////////////
    DWORD cekLen;
    BYTE* cek = NULL;
    for (DWORD i=0; i < nrOfRecipeints; i++)
      {
      if (recipientInfo) delete[] recipientInfo;

      DWORD cbRecipientInfoLen;
      if(! CryptMsgGetParam(hMsg, CMSG_CMS_RECIPIENT_INFO_PARAM, i, NULL, &cbRecipientInfoLen))
        {
        printf("MsgGetParam CMSG_CMS_RECIPIENT_INFO_PARAM size failed with error 0x%.8X\n", GetLastError());
        //return false;
        throw NULL;
        }
      recipientInfo = (PCMSG_CMS_RECIPIENT_INFO) new BYTE[cbRecipientInfoLen]; // null check ??
      if(! CryptMsgGetParam(hMsg, CMSG_CMS_RECIPIENT_INFO_PARAM, i, recipientInfo, &cbRecipientInfoLen))
        {
        printf("MsgGetParam CMSG_CMS_RECIPIENT_INFO_PARAM failed with error 0x%.8X\n", GetLastError());
        return false;
        }

      DWORD rsaPadding = NULL;
      if (strcmp(recipientInfo->pKeyTrans->KeyEncryptionAlgorithm.pszObjId, szOID_RSAES_OAEP) == 0)
        {
        //printf("Using OAEP padding");
        rsaPadding = CRYPT_OAEP;
        }

        //Helper::PrintHex(recipientInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.pbData, recipientInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.cbData);
    
  //cek - content encryption key
      cekLen = recipientInfo->pKeyTrans->EncryptedKey.cbData;
      cek = recipientInfo->pKeyTrans->EncryptedKey.pbData;
    
      Helper::ReverseBytes(cek, cekLen);

      /*if (! CryptDecrypt(hRsaPrivK, NULL, TRUE, rsaPadding, cek, &cekLen))
        {
        printf("Decrypt content encryption key failed with error 0x%.8X\n", GetLastError());
        //return false;
        //throw NULL;
        }*/
      if (CryptDecrypt(hRsaPrivK, NULL, TRUE, rsaPadding, cek, &cekLen))
        break;
      } // end loop recipients
          
  //printf("AES key len =  %d\n", cekLen);
  //printf("-----------AES KEY---------------");
  //Helper::PrintHex(cek, cekLen);
  //printf("--------------------------");

    DWORD cekAlgLen;
    if(! CryptMsgGetParam(hMsg, CMSG_ENVELOPE_ALGORITHM_PARAM, 0, NULL, &cekAlgLen))
      {
      printf("MsgGetParam CMSG_ENVELOPE_ALGORITHM_PARAM failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
    cekAlg = (PCRYPT_ALGORITHM_IDENTIFIER) new BYTE[cekAlgLen];
    if(! CryptMsgGetParam(hMsg, CMSG_ENVELOPE_ALGORITHM_PARAM, 0, cekAlg, &cekAlgLen))
      {
      printf("MsgGetParam CMSG_ENVELOPE_ALGORITHM_PARAM failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }

    //Helper::ReverseBytes(cek, cekLen);

  //printf(cekAlg->pszObjId"\n");
  //CMSG_ENVELOPE_ALGORITHM_PARAM

//    char pbKeyData[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
//    DWORD cbKeyData = 16;
    HCRYPTKEY hCEK;
    struct {
    BLOBHEADER header;
    DWORD cbKeySize;
    BYTE rgbKeyData[32]; //max -> 256 bit aes
    } keyBlob = {0};

    keyBlob.header.bType = PLAINTEXTKEYBLOB;
    keyBlob.header.bVersion = CUR_BLOB_VERSION;
    keyBlob.header.reserved = 0;
      // CALG_AES_128 is used as an example. You would set this to the 
  // algorithm id that corresponds to the one used by the key.
    keyBlob.header.aiKeyAlg = getAlgIdByObjId(cekAlg->pszObjId);  //CALG_AES_128;
    keyBlob.cbKeySize = cekLen;//16;
    memcpy(keyBlob.rgbKeyData, cek, cekLen);

    //cout << "--------AES KEY------------"<< endl;
    //Helper::PrintHex(cek, cekLen);
    //cout << "--------------------"<< endl;
    //printf("\n%d\n", cekAlg->Parameters.cbData);
    //printf("\n\n\n");

    if (!CryptImportKey(hProv, (BYTE*)&keyBlob, sizeof(keyBlob), NULL, NULL, &hCEK))
      {
      fprintf( stderr, "Import AES key failed. Err: 0x%.8X", GetLastError() );
      throw NULL;
      }

    //Helper::PrintHex(cekAlg->Parameters.pbData+2, cekAlg->Parameters.cbData-2);

    if(! CryptSetKeyParam(hCEK, KP_IV, (BYTE *) cekAlg->Parameters.pbData+2, 0)) //+2 for ASN header ???
      {
      printf("SetKeyParam KP_IV failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }

    DWORD dwMode = CRYPT_MODE_CBC;
    if(! CryptSetKeyParam(hCEK, KP_MODE, (BYTE*) &dwMode, 0))
      {
      printf("SetKeyParam KP_MODE failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }

  /*BOOL hr;
  if (hr == FALSE)
      throw "Unable to set IV";

  hr = CryptSetKeyParam(hCEK, KP_MODE, (BYTE*) &dwMode, 0);
  if (hr == FALSE)
      throw "Unable to set mode";*/

  //BYTE pbPT[48] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0xxxxxxxxxxxxxxxx";
  //DWORD pbPTLen = 32;
  //DWORD dwBufLen = 48;

  /*if (!CryptEncrypt(hCEK, NULL, TRUE, NULL, pbPT, &pbPTLen, dwBufLen))
  {
    printf("Encryption failed. Err: 0x%.8X", GetLastError());
  }*/

  //for (int i = 0; i < 16; i++) printf("%x",pbPT[i]);
  //CMSG_BARE_CONTENT_PARAM
    
    DWORD bareContentLen;
    if(! CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, NULL, &bareContentLen))
      {
      printf("MsgGetParam CMSG_BARE_CONTENT_PARAM size failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
    bareContent = new BYTE[bareContentLen];
    if(! CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, bareContent, &bareContentLen))
      {
      printf("MsgGetParam CMSG_BARE_CONTENT_PARAM failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }

    //cout << "--------CONTENT------------"<< endl;
    //Helper::PrintHex(bareContent, bareContentLen);
    //cout << "--------------------"<< endl;
    
    //Helper::HexToBin((BYTE*)"41510D3DA446963CDC3F3C30C92D150B", 16, bareContent, bareContentLen);
    
    //BYTE* cont;
    //DWORD contLen;
    //Helper::LoadFileWin("data.txt", cont, contLen);

    //Helper::PrintHex(cont, contLen);


      //for (int i = 0; i < bareContentLen; i++) printf("%c", bareContent[i]);
  //printf();
    //cout << "content len = " << bareContentLen << endl; 

    //Helper::ReverseBytes(bareContent, bareContentLen);
    //Helper::ReverseBytes(cont, contLen);

    //if (! CryptDecrypt(hCEK, NULL, TRUE, NULL, cont, &contLen))
    if (! CryptDecrypt(hCEK, NULL, TRUE, NULL, bareContent, &bareContentLen))
      {
      printf("Decrypting data failed with error 0x%.8X\n", GetLastError());
      //return false;
      throw NULL;
      }
      //array = (const char*)bareContent;
      memcpy(output, bareContent, bareContentLen);
      //release bareContent
      outlen = bareContentLen;
    }
    catch (void*)
      {
      ret = false;
      }
    if (hMsg) CryptMsgClose(hMsg);
    //if (recipientInfo) delete[] recipientInfo;
    //bareContent
    //cekAlg
  //for (int i = 0; i < bareContentLen; i++)
  //  printf("%c", bareContent[i]);

  /*
  BYTE InnerType[100];
  DWORD cbInnerTypeLen = 100;
  //DWORD dwMessageType, cbMessageTypeLen;
  if(! CryptMsgGetParam(
      hMsg,                  // handle to the message
      CMSG_BARE_CONTENT_PARAM,    // parameter type
      0,                     // index
      InnerType,                  
      &cbInnerTypeLen))           // size of the returned information
  {
      printf("Decode CMSG_INNER_CONTENT_TYPE_PARAM failed with error 0x%.8X\n", GetLastError());
  }

  printf("%d ++ %s\n", cbMessageTypeLen, (char*)InnerType);

  CMSG_CTRL_DECRYPT_PARA decPara;// = {0}
  memset(&decPara, 0, sizeof(decPara));
  decPara.hCryptProv = hProv;
  decPara.cbSize = sizeof(decPara);
  //decPara.dwKeySpec = AT_KEYEXCHANGE;
  decPara.dwRecipientIndex = 0;
  */

  /*if (!CryptMsgControl(hMsg, CMSG_CTRL_DECRYPT, CMSG_CONTENT_PARAM, &decPara))
  {
    printf("CryptMsgControl failed with error 0x%.8X\n", GetLastError());
  }

  BYTE dout[1000];
  DWORD doutLen;
  if(! CryptMsgGetParam(
      hMsg,                  // handle to the message
      CMSG_CONTENT_PARAM,    // parameter type
      0,                     // index
      dout,                  
      &doutLen))           // size of the returned information
  {
      printf("Decode CMSG_CONTENT_PARAM failed with error 0x%.8X\n", GetLastError());
  }*/

  //printf("%d\n", doutLen);
  //printf((char*)dout);

  //CryptMsgClose(hMsg);

  /*if(dwMessageType == CMSG_DATA)
  {
        printf("The message is a data message. Proceed. \n");
  }
  else
  {
      printf("Wrong message type");
  }*/


  /* if(! CryptMsgGetParam(
      hMsg,                  // handle to the message
      CMSG_CONTENT_PARAM,    // parameter type
      0,                     // index
      NULL,                  
      &cbDecoded))           // size of the returned information
  {
      printf("Decode CMSG_CONTENT_PARAM failed. \n");
  }

  if(!(pbDecoded = (BYTE *) malloc(cbDecoded)))
  {
      MyHandleError("Decode memory allocation failed.");
  }

  ;*/

  return ret;
}

ALG_ID CAPICMS::getAlgIdByObjId(char * pszObjId)
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
