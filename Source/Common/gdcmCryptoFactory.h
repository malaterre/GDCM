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


#include <map>
#include <string>
#include "gdcmCryptographicMessageSyntax.h"
#include <iostream>
using namespace std;

namespace gdcm
{
class GDCM_EXPORT CryptoFactory
{
public:
  CryptoFactory(){}
  virtual CryptographicMessageSyntax& CreateCMSProvider() = 0;
  virtual bool getStatus() = 0;

  static std::map<int, CryptoFactory*>& getMap()
  {
    static std::map<int, CryptoFactory*> libs;
    return libs;
  }
  static void AddLib(int id, CryptoFactory* f)
    {
    //libs.insert(pair<int, CryptoFactory*>(id, f));
    getMap().insert(pair<int, CryptoFactory*>(id, f));
    }
  static CryptoFactory& getFactoryInstance(int id)
    {
    //if (libs[id] == NULL) 
    if (getMap()[id] == NULL) 
    {
      cout << "No crypto library registered by id " << id << endl;
      exit(0);
    }
    //return *libs[id];
    return *getMap()[id];
    }
};
//map<int, CryptoFactory*> CryptoFactory::libs;
}
#endif //GDCMCRYPTOFACTORY_H
