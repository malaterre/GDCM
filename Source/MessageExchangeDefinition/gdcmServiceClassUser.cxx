/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmServiceClassUser.h"
#include "gdcmDataEvent.h"

namespace gdcm
{

class ServiceClassUserInternals
{
public:
  std::string hostname;
  int port;
  std::string aetitle;
  std::string calledaetitle;
};

ServiceClassUser::ServiceClassUser()
{
  Internals = new ServiceClassUserInternals;
}

ServiceClassUser::~ServiceClassUser()
{
  delete Internals;
}

void ServiceClassUser::Receive()
{
  std::string senddata = "gdcm is great";

  const DataEvent data( senddata.c_str(), senddata.size() );
  this->InvokeEvent( data );
}

void ServiceClassUser::Send()
{
  DataEvent data;
  this->InvokeEvent( data );

  const char *v = data.GetData();
  size_t l = data.GetDataLength();
  std::string s ( v, l );
  std::cerr << "Sending: " << s << std::endl;

}

} // end namespace gdcm
