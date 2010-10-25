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
#include "gdcmULConnectionManager.h"

#include "gdcmUserInformation.h"
#include "gdcmULEvent.h"
#include "gdcmPDUFactory.h"
#include "gdcmReader.h"
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAttribute.h"

#include <vector>

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
  std::vector<gdcm::DataSet> empty;
  EStateID theState = RunEventLoop(theEvent, empty);

  return (theState == eSta6TransferReady);//ie, finished the transitions
}


//send the Data PDU associated with Echo (ie, a default DataPDU)
//this lets the user confirm that the connection is alive.
//the user should look to cout to see the response of the echo command
std::vector<PresentationDataValue> ULConnectionManager::SendEcho(){

  std::vector<BasePDU*> theDataPDU = PDUFactory::CreateCEchoPDU(*mConnection);//pass NULL for C-Echo
  ULEvent theEvent(ePDATArequest, theDataPDU);

  std::vector<gdcm::DataSet> empty;
  EStateID theState = RunEventLoop(theEvent, empty);
  //theEvent should contain the PDU for the echo!
  
  if (theState == eSta6TransferReady){//ie, finished the transitions
    return PDUFactory::GetPDVs(theEvent.GetPDUs());
  } else {
    std::vector<PresentationDataValue> empty;
    return empty;
  }
}

std::vector<gdcm::DataSet>  ULConnectionManager::SendMove(gdcm::DataSet *inDataSet)
{
  std::vector<BasePDU*> theDataPDU = PDUFactory::CreateCMovePDU( *mConnection, inDataSet );
  ULEvent theEvent(ePDATArequest, theDataPDU);

  std::vector<gdcm::DataSet> theResult;
  EStateID theState = RunEventLoop(theEvent, theResult);
  return theResult;
}
std::vector<gdcm::DataSet> ULConnectionManager::SendFind(gdcm::DataSet *inDataSet)
{
  std::vector<BasePDU*> theDataPDU = PDUFactory::CreateCFindPDU( *mConnection, inDataSet );
  ULEvent theEvent(ePDATArequest, theDataPDU);

  std::vector<gdcm::DataSet> theResult;
  EStateID theState = RunEventLoop(theEvent, theResult);
  return theResult;
}

std::vector<gdcm::DataSet> ULConnectionManager::SendStore(gdcm::DataSet *inDataSet)
{
  std::vector<BasePDU*> theDataPDU = PDUFactory::CreateCStorePDU( *mConnection, inDataSet );
  ULEvent theEvent(ePDATArequest, theDataPDU);

  std::vector<gdcm::DataSet> theResult;
  EStateID theState = RunEventLoop(theEvent, theResult);
  return theResult;
}

bool ULConnectionManager::BreakConnection(const double& inTimeOut){
  BasePDU* thePDU = PDUFactory::ConstructReleasePDU();
  ULEvent theEvent(eARELEASERequest, thePDU);
  mConnection->GetTimer().SetTimeout(inTimeOut);

  std::vector<gdcm::DataSet> empty;
  EStateID theState = RunEventLoop(theEvent, empty);
  return (theState == eSta1Idle);//ie, finished the transitions
}

void ULConnectionManager::BreakConnectionNow(){
  BasePDU* thePDU = PDUFactory::ConstructAbortPDU();
  ULEvent theEvent(eAABORTRequest, thePDU);

  std::vector<gdcm::DataSet> empty;
  EStateID theState = RunEventLoop(theEvent, empty);
}


//event handler loop.
//will just keep running until the current event is nonexistent.
//at which point, it will return the current state of the connection
//to do this, execute an event, and then see if there's a response on the 
//incoming connection (with a reasonable amount of timeout).
//if no response, assume that the connection is broken.
//if there's a response, then yay.
//note that this is the ARTIM timeout event
EStateID ULConnectionManager::RunEventLoop(ULEvent& currentEvent, std::vector<gdcm::DataSet>& outDataSet){
  EStateID theState = eStaDoesNotExist;
  bool waitingForEvent;
  EEventID raisedEvent;

  bool receivingData = false;
  bool justWaiting = false;
  //when receiving data from a find, etc, then justWaiting is true and only receiving is done
  //eventually, could add cancel into the mix... but that would be through a callback or something similar
  do {
    if (!justWaiting){
      mTransitions.HandleEvent(currentEvent, *mConnection, waitingForEvent, raisedEvent);
    }
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
            thePDU->Print(std::cout);
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
      if (!incomingPDUs.empty()){
        currentEvent.SetEvent(PDUFactory::DetermineEventByPDU(incomingPDUs[0]));
        currentEvent.SetPDU(incomingPDUs);
        if (mConnection->GetTimer().GetHasExpired()){
          currentEvent.SetEvent(eARTIMTimerExpired);
        }
        if (theState == eSta6TransferReady){//ie, finished the transitions
          //with find, the results now come down the wire. 
          //the pdu we already have from the event will tell us how many to expect.
          uint32_t pendingDE1, pendingDE2, success, theVal;
          pendingDE1 = 0xff01;
          pendingDE2 = 0xff00;
          success = 0x0000;
          theVal = pendingDE1;
          DataSet theRSP = PresentationDataValue::ConcatenatePDVBlobs(PDUFactory::GetPDVs(currentEvent.GetPDUs()));
          if (theRSP.FindDataElement(gdcm::Tag(0x0, 0x0900))){
            gdcm::DataElement de = theRSP.GetDataElement(gdcm::Tag(0x0,0x0900));
            gdcm::Attribute<0x0,0x0900> at;
            at.SetFromDataElement( de );
            theVal = at.GetValues()[0];
            //if theVal is Pending or Success, then we need to enter the loop below,
            //because we need the data PDUs.
            //so, the loop below is a do/while loop; there should be at least a second packet 
            //with the dataset, even if the status is 'success'
            //success == 0000H
          }
          receivingData = false;
          justWaiting = false;
          if (theVal == pendingDE1 || theVal == pendingDE2) {
            receivingData = true; //wait for more data as more PDUs (findrsps, for instance)
            justWaiting = true;
            waitingForEvent = true;
          }
#if 0
          if( theVal == 0xff00 ) // MM FIX C-MOVE
            {
            (void)theVal;
            receivingData = false;
            justWaiting = false;

            waitingForEvent = false;
            }
#endif
          if (theVal == pendingDE1 || theVal == pendingDE2 /*|| theVal == success*/){//keep looping if we haven't succeeded or failed; these are the values for 'pending'
            //first, dynamically cast that pdu in the event
            //should be a data pdu
            //then, look for tag 0x0,0x900

            //only add datasets that are _not_ part of the network response
            std::vector<gdcm::DataSet> final;
            std::vector<BasePDU*> theData;
            BasePDU* thePDU;//outside the loop for the do/while stopping condition
            bool interrupted = false;
            do {
              uint8_t itemtype = 0x0;
              is.read( (char*)&itemtype, 1 );
              //what happens if nothing's read?
              thePDU = PDUFactory::ConstructPDU(itemtype);
              if (itemtype != 0x4 && thePDU != NULL){ //ie, not a pdatapdu
                std::vector<BasePDU*> interruptingPDUs;
                currentEvent.SetEvent(PDUFactory::DetermineEventByPDU(interruptingPDUs[0]));
                currentEvent.SetPDU(interruptingPDUs);
                interrupted= true;
                break;
              }
              if (thePDU != NULL){
                thePDU->Read(is);
                theData.push_back(thePDU);
              } else{
                break;
              }
              //!!!need to handle incoming PDUs that are not data, ie, an abort
            } while(/*!is.eof() &&*/ !thePDU->IsLastFragment());
            if (!interrupted){//ie, if the remote server didn't hang up 
              DataSet theCompleteFindResponse = 
                PresentationDataValue::ConcatenatePDVBlobs(PDUFactory::GetPDVs(theData));
              //note that it's the responsibility of the event to delete the PDU in theFindRSP
              for (int i = 0; i < theData.size(); i++){
                delete theData[i];
              }
              outDataSet.push_back(theCompleteFindResponse);
            }
          }
        }
      } else {
        raisedEvent = eEventDoesNotExist;
        waitingForEvent = false;
      }
    }
    else {
      currentEvent.SetEvent(raisedEvent);//actions that cause transitions in the state table
      //locally just raise local events that will therefore cause the trigger to be pulled.
    }
  } while (currentEvent.GetEvent() != eEventDoesNotExist && 
    theState != eStaDoesNotExist && theState != eSta13AwaitingClose && theState != eSta1Idle &&
    (theState != eSta6TransferReady || (theState == eSta6TransferReady && receivingData )));
  //stop when the AE is done, or when ready to transfer data (ie, the next PDU should be sent in), 
  //or when the connection is idle after a disconnection.
  //or, if in state 6 and receiving data, until all data is received.

  return theState;
}
