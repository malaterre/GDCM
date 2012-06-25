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
class CAPICryptoFactory : public CryptoFactory
{
public:
  CAPICryptoFactory()
    {
    cout << "CAPI Factory creted" << endl;
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

};
} // end namespace gdcm
#endif //GDCMCAPIFACTORY_H
