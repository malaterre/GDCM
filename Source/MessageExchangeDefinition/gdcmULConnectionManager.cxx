/* 

The ULConnectionManager performs actions on the ULConnection given inputs from
the user and from the state of what's going on around the connection (ie,
timeouts of the ARTIM timer, responses from the peer across the connection, etc).

Its inputs are ULEvents, and it performs ULActions.

*/

#include "gdcmULConnectionManager.h"
#include "gdcmUserInformation.h"
#include "gdcmULEvent.h"
#include "gdcmPDUFactory.h"


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
  ULEvent theEvent(eAASSOCIATERequestLocalUser, NULL);
  EStateID theState = RunEventLoop(theEvent);

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
  EStateID theState = eStaDoesNotExist;
  do {
    mTransitions.HandleEvent(currentEvent, *mConnection);
    theState = mConnection->GetState();
    std::istream &is = *mConnection->GetProtocol();
    std::ostream &os = *mConnection->GetProtocol();
    
    //read the connection, as that's an event as well.
    //waiting for an object to come back across the connection, so that it can get handled.
    //ie, accept, reject, timeout, etc.
    //of course, if the connection is down, just leave the loop.
    //also leave the loop if nothing's waiting.
    //use the PDUFactory to create the appropriate pdu, which has its own
    //internal mechanisms for handling itself (but will, of course, be put inside the event object).
    //but, and here's the important thing, only read on the socket when we should.
    if (theState == eSta5WaitRemoteAssoc || theState == eSta7WaitRelease ||
      theState == eSta8WaitLocalRelease || theState == eSta13AwaitingClose){
      uint8_t itemtype = 0x0;
      try {
        is.read( (char*)&itemtype, 1 );
        //what happens if nothing's read?
        BasePDU* thePDU = PDUFactory::ConstructPDU(itemtype);
        if (thePDU != NULL){
          currentEvent.SetPDU(thePDU);
          thePDU->Read(is);
        } else {
          currentEvent.SetEvent(eEventDoesNotExist);
        }
        //now, we have to figure out the event that just happened based on the PDU that was received.
        currentEvent.SetEvent(PDUFactory::DetermineEventByPDU(thePDU));
        if (mConnection->GetTimer().GetHasExpired()){
          currentEvent.SetEvent(eARTIMTimerExpired);
        }
      }
      catch (...){
        //handle the exception, which is basically that nothing came in over the pipe.
      }
    }
    //this is crude, but as a special case, force the instantiation of a local connection
    //that doesn't need to be 8 individual steps) into one step.
    //so, if we're in sta4, just fire off that event
    if (theState == eSta4LocalAssocDone){
      currentEvent.SetEvent(eTransportConnConfirmLocal);
    }
  } while (currentEvent.GetEvent() != eEventDoesNotExist);

  return theState;
}