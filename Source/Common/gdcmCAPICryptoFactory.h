/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMCAPIFACTORY_H
#define GDCMCAPIFACTORY_H

#include <iostream>
#include "gdcmCryptoFactory.h"
#include "gdcmCAPICryptographicMessageSyntax.h"

//#include <Windows.h> //for linux different id needed

using namespace std;

namespace gdcm
{
class GDCM_EXPORT CAPICryptoFactory : public CryptoFactory
{
  //static CAPICryptoFactory asd;
public:
  CAPICryptoFactory(CryptoLibs id) : CryptoFactory(id)
    {
    cout << "CAPI Factory created (and registered?)" << endl;
    //CryptoFactory::AddLib(1, this);
    }
    
public:
  CryptographicMessageSyntax& CreateCMSProvider()
    {
    return *(new CAPICMS());
    }

  bool getStatus()
    {
    return 0;
    }

private:
  CAPICryptoFactory(){}

};
} // end namespace gdcm
#endif //GDCMCAPIFACTORY_H
