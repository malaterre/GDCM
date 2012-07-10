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
#include <map>

#ifdef WIN32
#include "gdcmCAPICryptoFactory.h"
#endif
#include "gdcmOpenSSLCryptoFactory.h"

namespace gdcm
{
  CryptoFactory& CryptoFactory::getFactoryInstance(int id)
  {
    #ifdef WIN32
    static CAPICryptoFactory capi(CryptoFactory::CAPI);
    #endif
    static OpenSSLCryptoFactory ossl(CryptoFactory::OPENSSL);

    if (getMap()[id] == NULL) 
      {
      cout << "No crypto library registered by id " << id << endl;
      exit(0);
      }
    return *getMap()[id];
  }
}
