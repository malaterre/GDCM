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

#pragma comment(lib, "Crypt32.lib")

namespace gdcm
{
class GDCM_EXPORT CAPICMS : public CryptographicMessageSyntax
{
public:
  CAPICMS();
  ~CAPICMS();

  // X.509
  bool ParseCertificateFile( const char *filename );
  bool ParseKeyFile( const char *filename );

  /// create a PKCS#7 envelopedData structure
  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool EncryptXP(char *output, size_t &outlen, const char *array, size_t len); // params: sym enc alg, [rsa:oeap]
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const;

private:
  static ALG_ID getAlgIdByObjId(const char * pszObjId);
  LPSTR getCipherObjId() const;

private:
  bool initialized;
  HCRYPTPROV hProv;
  vector<PCCERT_CONTEXT> certifList;
  HCRYPTKEY hRsaPrivK;

  bool Initialize();
};
}

#endif //GDCMCAPICMS_H
