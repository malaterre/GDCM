
//this class contains all the information about a particular connection
//as established by the user.  That is, it's:
// User Information
// Calling AE Title
// Called AE Title
// IP address/computer name
// IP Port
//A connection must be established with this information, that's subsequently
//placed into various primitives for actual communication.
#include "gdcmULConnectionInfo.h" 
#include <socket++/sockinet.h>//for setting up the local socket

using namespace gdcm::network;

ULConnectionInfo::ULConnectionInfo(){
  memset(mCallingAETitle, 0, 16);
  memset(mCalledAETitle, 0, 16);
}
      
      //it is possible to misinitialize this object, so
      //have it return false if something breaks (ie, given AEs are bigger than 16 characters,
      //no name or IP address).
bool ULConnectionInfo::Initialize(UserInformation inUserInformation,
        const char inCalledAETitle[16], const char inCallingAETitle[16],
        unsigned long inCalledIPAddress, int inCalledIPPort,
        std::string inCalledComputerName)
{
  if (inCalledIPAddress == 0 && inCalledComputerName.empty()){
    return false;
  }
  //if (strcpy_s(mCalledAETitle, 16, inCalledAETitle) != 0) return false;
  strncpy(mCalledAETitle, inCalledAETitle, 16);
  //if (strcpy_s(mCallingAETitle, 16, inCallingAETitle) != 0) return false;
  strncpy(mCallingAETitle, inCallingAETitle, 16);
  mCalledComputerName = inCalledComputerName;
  mCalledIPPort = inCalledIPPort;
  mCalledIPAddress = inCalledIPAddress;

  //test to see if the given computer name is actually an IP address
  if (mCalledIPAddress == 0 && !mCalledComputerName.empty()){
    mCalledIPAddress = inet_addr(mCalledComputerName.c_str());
  //  if (mCalledIPAddress != 0)
  //    mCalledComputerName = "";
  }

  mUserInformation = inUserInformation;
  return true;
}

UserInformation ULConnectionInfo::GetUserInformation() const{
  return mUserInformation;
}
const char* ULConnectionInfo::GetCalledAETitle() const{
  return mCalledAETitle;
}
const char* ULConnectionInfo::GetCallingAETitle() const{
  return mCallingAETitle;
}

unsigned long ULConnectionInfo::GetCalledIPAddress() const{
  return mCalledIPAddress;
}
int ULConnectionInfo::GetCalledIPPort() const{
  return mCalledIPPort;
}
std::string ULConnectionInfo::GetCalledComputerName() const{
  return mCalledComputerName;
}
