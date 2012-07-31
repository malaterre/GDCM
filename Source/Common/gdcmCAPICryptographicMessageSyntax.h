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

//#include <iostream>
#include "gdcmCryptographicMessageSyntax.h"
#include <Windows.h>
#include <WinCrypt.h>
#include <vector>

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

  // PBE
  virtual bool SetPassword(const char * pass)
  {
    return false;
  }
  virtual bool SetPassword(const char * pass, size_t passLen)
  {
    return false;
  }

  /// create a PKCS#7 envelopedData structure
  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len) const;
  bool Decrypt(char *output, size_t &outlen, const char *array, size_t len) const;

private:
  bool Initialize();
  static ALG_ID getAlgIdByObjId(const char * pszObjId);
  LPSTR getCipherObjId() const;
  static void ReverseBytes(BYTE* data, DWORD len);
  static bool LoadFile(const char * filename, BYTE* & buffer, DWORD & bufLen);

private:
  bool initialized;
  HCRYPTPROV hProv;
  vector<PCCERT_CONTEXT> certifList;
  HCRYPTKEY hRsaPrivK;

};
}

#endif //GDCMCAPICMS_H
