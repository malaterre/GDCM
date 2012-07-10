/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMCRYPTOFACTORY_H
#define GDCMCRYPTOFACTORY_H


#include "gdcmCryptographicMessageSyntax.h"
#include <map>

namespace gdcm
{
class GDCM_EXPORT CryptoFactory
{
public:
  virtual CryptographicMessageSyntax& CreateCMSProvider() = 0;

  virtual bool getStatus() = 0;

  static CryptoFactory& getFactoryInstance(int id);

  enum CryptoLibs {OPENSSL, CAPI};

protected:
  CryptoFactory(CryptoLibs id)
  {
    AddLib(id, this);
  }

  static std::map<int, CryptoFactory*>& getMap()
  {
    static std::map<int, CryptoFactory*> libs;
    return libs;
  }

  static void AddLib(int id, CryptoFactory* f)
  {
    getMap().insert(pair<int, CryptoFactory*>(id, f));
  }

protected:
  CryptoFactory(){}
};
}
#endif //GDCMCRYPTOFACTORY_H
