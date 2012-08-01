/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include <iostream>
using namespace std;

#include "gdcmCryptoFactory.h"

#ifdef WIN32
#include "gdcmCAPICryptoFactory.h"
#endif

#ifdef GDCM_USE_SYSTEM_OPENSSL
#include "gdcmOpenSSLCryptoFactory.h"
#include "gdcmOpenSSLP7CryptoFactory.h"
#endif

namespace gdcm
{

CryptoFactory* CryptoFactory::getFactoryInstance(CryptoLib id)
{
#ifdef WIN32
  static CAPICryptoFactory capi(CryptoFactory::CAPI);
#endif
#ifdef GDCM_USE_SYSTEM_OPENSSL
  static OpenSSLCryptoFactory ossl(CryptoFactory::OPENSSL);
  static OpenSSLP7CryptoFactory osslp7(CryptoFactory::OPENSSLP7);
#endif
  std::map<CryptoLib, CryptoFactory*>::iterator it = getInstanceMap().find(id);
  if (it == getInstanceMap().end())
    {
    //std::cout << "No crypto factory registered with id " << id << std::endl;
    return NULL;
    }
  assert(it->second);
  return it->second;
}

}
