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

class CryptoLibraryNotFound : public Exception {};

class GDCM_EXPORT CryptoFactory
{
public:
  enum CryptoLib {OPENSSL, CAPI, OPENSSLP7};

  virtual CryptographicMessageSyntax* CreateCMSProvider() = 0;
  static CryptoFactory* getFactoryInstance(CryptoLib id);

protected:
  CryptoFactory(CryptoLib id)
  {
    AddLib(id, this);
  }

  static std::map<CryptoLib, CryptoFactory*>& getInstanceMap()
  {
    static std::map<CryptoLib, CryptoFactory*> libs;
    return libs;
  }

  static void AddLib(CryptoLib id, CryptoFactory* f)
  {
    getInstanceMap().insert(pair<CryptoLib, CryptoFactory*>(id, f));
  }

protected:
  CryptoFactory(){}
  ~CryptoFactory(){};
};
}
#endif //GDCMCRYPTOFACTORY_H
