/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMOPENSSLFACTORY_H
#define GDCMOPENSSLFACTORY_H

#include <iostream>
#include "gdcmCryptoFactory.h"
#include "gdcmOpenSSLCryptographicMessageSyntax.h"

using namespace std;

namespace gdcm
{
class GDCM_EXPORT OpenSSLCryptoFactory : public CryptoFactory
{
public:
  OpenSSLCryptoFactory(CryptoLibs id) : CryptoFactory(id)
  {
    cout << "OpenSSL Factory created (and registered?)" << endl;
    //CryptoFactory::AddLib(0, this);
  }
    
public:
  CryptographicMessageSyntax& CreateCMSProvider()
  {
    return *(new OpenSSLCMS());
  }

  bool getStatus()
  {
    return 0;
  }

private:
  OpenSSLCryptoFactory(){}
};
}

#endif //GDCMOPENSSLFACTORY_H
