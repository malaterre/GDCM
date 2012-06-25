/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMCAPICMS_H
#define GDCMCAPICMS_H


#include <iostream>
#include "gdcmCryptographicMessageSyntax.h"

#include <Windows.h>
#include <WinCrypt.h>
#include <vector>

#include "Helper.h"

//#include "cms.asn1\EnvelopedData.h"

#pragma comment(lib, "Crypt32.lib")

namespace gdcm
{
class CAPICMS : public CryptographicMessageSyntax
{
public:
  CAPICMS() {
  initialized = Initialize();
  hRsaPrivK = 0;
  }

  ~CAPICMS();

  void Encrypt();
  void Decrypt();

public:
  // X.509
  bool ParseCertificateFile( const char *filename );
public:
  bool ParseKeyFile( const char *filename );

  /// create a PKCS#7 envelopedData structure
  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;

  // params: sym enc alg, 
  // [rsa:oeap]
  bool EncryptXP(char *output, size_t &outlen, const char *array, size_t len);
  
  // Using external private key
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) {
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
        printf("The message is an enveloped message. Proceed. \n");
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
          printf("Unsing OAEP padding");
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

private:
  static ALG_ID getAlgIdByObjId(char * pszObjId)
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

  LPSTR getCipherObjId() const;

private:
  bool initialized;
  HCRYPTPROV hProv;
  vector<PCCERT_CONTEXT> certifList;
  //PCCERT_CONTEXT certt;
  //PCCERT_CONTEXT * certa;
  HCRYPTKEY hRsaPrivK;

  bool Initialize();
};
}

#endif //GDCMCAPICMS_H
