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
#include "gdcmSimpleSubjectWatcher.h"

class MyWatcher : public gdcm::SimpleSubjectWatcher
{
public:
  MyWatcher(gdcm::Subject * s):gdcm::SimpleSubjectWatcher(s,"MyWatcher"){}

  virtual void ShowData(gdcm::Subject *caller, gdcm::Event &evt)
    {
    try {
      const gdcm::DataEvent &d = dynamic_cast<const gdcm::DataEvent&>(evt);
      const char *v = d.GetData();
      if( v ) {
        size_t l = d.GetDataLength();
        std::string s ( v, l );
        std::cerr << "Receive: " << s << std::endl;
      }
      else
        {
        std::string s = "Please send me over";
        }
    }
    catch(std::exception & ) {
      assert(0);
      }
    }
};

int TestServiceClassUser(int argc, char *argv[])
{
  gdcm::SmartPointer<gdcm::ServiceClassUser> scup = new gdcm::ServiceClassUser;
  gdcm::ServiceClassUser &scu = *scup;
  MyWatcher watcher( &scu );
  //gdcm::SimpleSubjectWatcher w( &scu, "Test" );

  // receive data
  scu.Receive();
  // send data
  //gdcm::DataEvent data;
  scu.Send();

  return 0;
}
