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

  return (theState == eSta6TransferReady);//ie, finished the transitions
}


//send the Data PDU associated with Echo (ie, a default DataPDU)
//this lets the user confirm that the connection is alive.
//the user should look to cout to see the response of the echo command
bool ULConnectionManager::SendEcho(){

  BasePDU* theDataPDU = PDUFactory::ConstructDataPDU(NULL);//pass NULL for C-Echo
  ULEvent theEvent(ePDATArequest, theDataPDU);

  EStateID theState = RunEventLoop(theEvent);
  return (theState == eSta6TransferReady);//ie, finished the transitions
}


bool ULConnectionManager::BreakConnection(const double& inTimeOut){
  BasePDU* thePDU = PDUFactory::ConstructReleasePDU();
  ULEvent theEvent(eARELEASERequest, thePDU);
  mConnection->GetTimer().SetTimeout(inTimeOut);

  EStateID theState = RunEventLoop(theEvent);
  return (theState == eSta1Idle);//ie, finished the transitions
}

void ULConnectionManager::BreakConnectionNow(){
  BasePDU* thePDU = PDUFactory::ConstructAbortPDU();
  ULEvent theEvent(eAABORTRequest, thePDU);

  EStateID theState = RunEventLoop(theEvent);
}


//event handler loop.
//will just keep running until the current event is nonexistent.
//at which point, it will return the current state of the connection
//to do this, execute an event, and then see if there's a response on the 
//incoming connection (with a reasonable amount of timeout).
//if no response, assume that the connection is broken.
//if there's a response, then yay.
//note that this is the ARTIM timeout event
EStateID ULConnectionManager::RunEventLoop(ULEvent& currentEvent){
  EStateID theState = eStaDoesNotExist;
  bool waitingForEvent;
  EEventID raisedEvent;
  do {
    mTransitions.HandleEvent(currentEvent, *mConnection, waitingForEvent, raisedEvent);
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
    if (waitingForEvent){
      uint8_t itemtype = 0x0;
      try {
        is.read( (char*)&itemtype, 1 );
        //what happens if nothing's read?
        BasePDU* thePDU = PDUFactory::ConstructPDU(itemtype);
        if (thePDU != NULL){
          currentEvent.SetPDU(thePDU);
          thePDU->Read(is);
          thePDU->Print(std::cout);
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
    else {
      currentEvent.SetEvent(raisedEvent);//actions that cause transitions in the state table
      //locally just raise local events that will therefore cause the trigger to be pulled.
    }
  } while (currentEvent.GetEvent() != eEventDoesNotExist && theState != eStaDoesNotExist && 
    theState != eSta13AwaitingClose && theState != eSta6TransferReady && theState != eSta1Idle);
  //stop when the AE is done, or when ready to transfer data (ie, the next PDU should be sent in), 
  //or when the connection is idle after a disconnection.

  return theState;
}
