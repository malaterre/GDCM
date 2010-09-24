/* 

The ULConnectionManager performs actions on the ULConnection given inputs from
the user and from the state of what's going on around the connection (ie,
timeouts of the ARTIM timer, responses from the peer across the connection, etc).

Its inputs are ULEvents, and it performs ULActions.

*/

#include "gdcmULConnectionManager.h"
#include "gdcmUserInformation.h"
#include "gdcmULEvent.h"


using namespace gdcm::network;


ULConnectionManager::ULConnectionManager(){
  mConnection = NULL;
}
      
ULConnectionManager::~ULConnectionManager(){
  if (mConnection != NULL){
    delete mConnection;
    mConnection = NULL;
  }
}

bool ULConnectionManager::EstablishConnection(const std::string& inAETitle,  const std::string& inConnectAETitle, 
                                              const std::string& inComputerName, const long& inIPAddress, 
                                              const unsigned short& inConnectPort, const double& inTimeout)
{
  //generate a ULConnectionInfo object
  UserInformation userInfo;
  ULConnectionInfo connectInfo;
  if (inConnectAETitle.size() > 16) return false;//too long an AETitle, probably need better failure message
  if (inAETitle.size() > 16) return false; //as above
  if (!connectInfo.Initialize(userInfo, inConnectAETitle.c_str(), 
    inAETitle.c_str(), inIPAddress, inConnectPort, inComputerName)){
    return false;
  }

  if (mConnection!= NULL){
    delete mConnection;
  }
  mConnection = new ULConnection(connectInfo);

  mConnection->GetTimer().SetTimeout(inTimeout);

  //now, try to establish a connection by starting the transition table and the event loop.
  //here's the thing
  //if there's nothing on the event loop, assume that it's done & the function can exit.
  //otherwise, keep rolling the event loop

  

  return true;
}


//event handler loop.
//will just keep running until the current event is nonexistent.
//at which point, it will return the current state of the connection
//to do this, execute an event, and then see if there's a response on the 
//incoming connection (with a reasonable amount of timeout).
//if no response, assume that the connection is broken.
//if there's a response, then yay.
//note that this is the ARTIM timeout event
EStateID ULConnectionManager::RunEventLoop(ULEvent& inEvent){
  ULEvent currentEvent = inEvent;
  do {

    EStateID theState = mTransitions.HandleEvent(currentEvent, *mConnection);
    
    if (mConnection->GetTimer().GetHasExpired()){
      currentEvent.SetEvent(eARTIMTimerExpired);
    }
  } while (currentEvent.GetEvent() != eEventDoesNotExist);
}