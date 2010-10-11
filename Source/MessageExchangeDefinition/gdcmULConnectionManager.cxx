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
#include "gdcmReader.h"
#include "gdcmAAssociateRQPDU.h"


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
                                              const unsigned short& inConnectPort, const double& inTimeout, 
                                              const EConnectionType& inConnectionType, const gdcm::DataSet& inDS)
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


  // Warning PresentationContextID is important
  // this is a sort of uniq key used by the recevier. Eg.
  // if one push_pack
  //  (1, Secondary)
  //  (1, Verification)
  // Then the last one is prefered (DCMTK 3.5.5)

  // The following only works for C-STORE / C-ECHO
  // however it does not make much sense to add a lot of abstract syntax
  // when doing only C-ECHO.
  // FIXME is there a way to know here if we are in C-ECHO ?
  //there is now!
  //the presentation context will now be part of the connection, so that this 
  //initialization for the association-rq will use parameters from the connection

  gdcm::network::AbstractSyntax as;

  std::vector<PresentationContext> pcVector;
  PresentationContext pc;
  gdcm::network::TransferSyntax_ ts;
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  pc.AddTransferSyntax( ts );
  ts.SetNameFromUID( gdcm::UIDs::ExplicitVRLittleEndian );
  //pc.AddTransferSyntax( ts ); // we do not support explicit (mm)
  switch (inConnectionType){
    case eEcho:
        pc.SetPresentationContextID( eVerificationSOPClass );
        as.SetNameFromUID( gdcm::UIDs::VerificationSOPClass );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
      break;
    case eFind:
        pc.SetPresentationContextID( ePatientRootQueryRetrieveInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::PatientRootQueryRetrieveInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID(eStudyRootQueryRetrieveInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::StudyRootQueryRetrieveInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID( ePatientStudyOnlyQueryRetrieveInformationModelFINDRetired );
        as.SetNameFromUID( gdcm::UIDs::PatientStudyOnlyQueryRetrieveInformationModelFINDRetired );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID( eModalityWorklistInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::ModalityWorklistInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID( eGeneralPurposeWorklistInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::GeneralPurposeWorklistInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
      break;
      //our spec does not require C-GET support
//    case eGet:
//      break;
    case eMove:
        // should we also send stuff from FIND ?
        // E: Move PresCtx but no Find (accepting for now) 
        pc.SetPresentationContextID( ePatientRootQueryRetrieveInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::PatientRootQueryRetrieveInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        // move
        pc.SetPresentationContextID( ePatientRootQueryRetrieveInformationModelMOVE );
        as.SetNameFromUID( gdcm::UIDs::PatientRootQueryRetrieveInformationModelMOVE );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID( eStudyRootQueryRetrieveInformationModelFIND );
        as.SetNameFromUID( gdcm::UIDs::StudyRootQueryRetrieveInformationModelFIND );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
        pc.SetPresentationContextID( eStudyRootQueryRetrieveInformationModelMOVE );
        as.SetNameFromUID( gdcm::UIDs::StudyRootQueryRetrieveInformationModelMOVE );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
      break;
    case eStore:
      std::string uidName;
        pc.SetPresentationContextID( PresentationContext::AssignPresentationContextID(inDS, uidName) );
        as.SetNameFromUIDString( uidName );
        pc.SetAbstractSyntax( as );
        pcVector.push_back(pc);
      break;
  }
  mConnection->SetPresentationContexts(pcVector);


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
std::vector<PresentationDataValue> ULConnectionManager::SendEcho(){

  vector<BasePDU*> theDataPDU = PDUFactory::CreateCEchoPDU(*mConnection);//pass NULL for C-Echo
  ULEvent theEvent(ePDATArequest, theDataPDU);

  EStateID theState = RunEventLoop(theEvent);

  //theEvent should contain the PDU for the echo!
  
  if (theState == eSta6TransferReady){//ie, finished the transitions
    return PDUFactory::GetPDVs(theEvent.GetPDUs());
  } else {
    std::vector<PresentationDataValue> empty;
    return empty;
  }
}

bool ULConnectionManager::SendMove(gdcm::DataSet *inDataSet)
{
  vector<BasePDU*> theDataPDU = PDUFactory::CreateCMovePDU( *mConnection, inDataSet );
  ULEvent theEvent(ePDATArequest, theDataPDU);

  EStateID theState = RunEventLoop(theEvent);
  return (theState == eSta6TransferReady);//ie, finished the transitions
}
std::vector<gdcm::DataSet> ULConnectionManager::SendFind(gdcm::DataSet *inDataSet)
{
  vector<BasePDU*> theDataPDU = PDUFactory::CreateCFindPDU( *mConnection, inDataSet );
  ULEvent theEvent(ePDATArequest, theDataPDU);

  EStateID theState = RunEventLoop(theEvent);
  std::vector<BasePDU*> theData;
  if (theState == eSta6TransferReady){//ie, finished the transitions
    //with find, the results now come down the wire. 
    //the pdu we already have from the event will tell us how many to expect.
    std::vector<gdcm::DataSet> theFindRSP = PresentationDataValue::ConcatenatePDVBlobs(PDUFactory::GetPDVs(theEvent.GetPDUs()));
    //theFindRSP[0].Print(std::cout);
    std::istream &is = *mConnection->GetProtocol();
    while (!is.eof()){
      uint8_t itemtype = 0x0;
      is.read( (char*)&itemtype, 1 );
      //what happens if nothing's read?
      BasePDU* thePDU = PDUFactory::ConstructPDU(itemtype);
      if (thePDU != NULL){
        thePDU->Read(is);
        theData.push_back(thePDU);
      } else{
        break;
      }
    }
    
    std::vector<gdcm::DataSet> theCompleteFindResponse = 
      PresentationDataValue::ConcatenatePDVBlobs(PDUFactory::GetPDVs(theData));
    //note that it's the responsibility of the event to delete the PDU in theFindRSP
    for (int i = 0; i < theData.size(); i++){
      delete theData[i];
    }
    std::vector<gdcm::DataSet> final = theFindRSP;
    final.insert(final.end(), theCompleteFindResponse.begin(), theCompleteFindResponse.end());
    return final;
  } else {
    std::vector<gdcm::DataSet> empty;
    return empty;
  }
}

bool ULConnectionManager::SendStore(gdcm::DataSet *inDataSet)
{
  vector<BasePDU*> theDataPDU = PDUFactory::CreateCStorePDU( *mConnection, inDataSet );
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
    std::vector<BasePDU*> incomingPDUs;
    if (waitingForEvent){
      while (waitingForEvent){//loop for reading in the events that come down the wire
        uint8_t itemtype = 0x0;
        try {
          is.read( (char*)&itemtype, 1 );
          //what happens if nothing's read?
          BasePDU* thePDU = PDUFactory::ConstructPDU(itemtype);
          if (thePDU != NULL){
            incomingPDUs.push_back(thePDU);
            thePDU->Read(is);
            //thePDU->Print(std::cout);
            if (thePDU->IsLastFragment()) waitingForEvent = false;
          } else {
            waitingForEvent = false; //because no PDU means not waiting anymore
          }
        }
        catch (...){
          //handle the exception, which is basically that nothing came in over the pipe.
        }
      }
      //now, we have to figure out the event that just happened based on the PDU that was received.
      assert(!incomingPDUs.empty());
      currentEvent.SetEvent(PDUFactory::DetermineEventByPDU(incomingPDUs[0]));
      currentEvent.SetPDU(incomingPDUs);
      if (mConnection->GetTimer().GetHasExpired()){
        currentEvent.SetEvent(eARTIMTimerExpired);
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
