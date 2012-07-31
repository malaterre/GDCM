/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMOPENSSLP7FACTORY_H
#define GDCMOPENSSLP7FACTORY_H

#include <iostream>
#include "gdcmCryptoFactory.h"
#include "gdcmOpenSSLCryptographicMessageSyntax.h"

using namespace std;

namespace gdcm
{
class GDCM_EXPORT OpenSSLP7CryptoFactory : public CryptoFactory
{
public:
  OpenSSLP7CryptoFactory(CryptoLib id) : CryptoFactory(id)
  {
    gdcmDebugMacro( "OpenSSL (PKCS7) Factory registered." << endl );
    //CryptoFactory::AddLib(0, this);
  }
    
public:
  CryptographicMessageSyntax* CreateCMSProvider()
  {
    return new OpenSSLCMS();
  }

private:
  OpenSSLP7CryptoFactory(){}
};
}

#endif //GDCMOPENSSLP7FACTORY_H
