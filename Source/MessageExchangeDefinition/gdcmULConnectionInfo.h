/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

//this class contains all the information about a particular connection
//as established by the user.  That is, it's:
// User Information
// Calling AE Title
// Called AE Title
// IP address/computer name
// IP Port
//A connection must be established with this information, that's subsequently
//placed into various primitives for actual communication.
#ifndef ULCONNECTIONINFO_H
#define ULCONNECTIONINFO_H

#include "gdcmUserInformation.h"
#include <string>

namespace gdcm{
  namespace network {
    class ULConnectionInfo {
      UserInformation mUserInformation;

      char mCalledAETitle[16];
      char mCallingAETitle[16];

      unsigned long mCalledIPAddress;
      int mCalledIPPort;
      std::string mCalledComputerName; //either the IP or the name has to be filled in
    public:
      ULConnectionInfo();

      //it is possible to misinitialize this object, so
      //have it return false if something breaks (ie, given AEs are bigger than 16 characters,
      //no name or IP address).
      bool Initialize(UserInformation inUserInformation,
        const char inCalledAETitle[16], const char inCallingAETitle[16],
        unsigned long inCalledIPAddress, int inCalledIPPort,
        std::string inCalledComputerName);

      UserInformation GetUserInformation() const;
      const char* GetCalledAETitle() const;
      const char* GetCallingAETitle() const;

      unsigned long GetCalledIPAddress() const;
      int GetCalledIPPort() const;
      std::string GetCalledComputerName() const;

    };
  }
}

#endif //ULCONNECTIONINFO_H
