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

//#include <Windows.h> //for linux different id needed

using namespace std;

namespace gdcm
{
class OpenSSLCryptoFactory : public CryptoFactory
{
public:
  OpenSSLCryptoFactory()
    {
    //HMODULE libInst = LoadLibrary(L"libeay32.dll");

    /*if (libInst != NULL)
      {
      cout << "OpenSSL successfully loaded." << endl;
      }
    else
      {
      cout << "OpenSSL Library not found." << endl;
      }*/
    
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

    //friend class CryptoFactory;
};
}

#endif //GDCMOPENSSLFACTORY_H
