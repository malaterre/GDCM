
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