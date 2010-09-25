/*
This file is the implementation of the ULTransitionTable class, including the actual event handling as well as the construction of the table itself.

*/

#include "gdcmULTransitionTable.h"
#include "gdcmULActionAA.h"
#include "gdcmULActionAE.h"
#include "gdcmULActionAR.h"
#include "gdcmULActionDT.h"

using namespace gdcm::network;

//construct the table
ULTransitionTable::ULTransitionTable(){
  //row 1

  mTable[eAASSOCIATERequestLocalUser].transitions[GetStateIndex(eSta1Idle)] = 
    Transition::MakeNew(eSta4LocalAssocDone, new ULActionAE1());
  //row 2
  mTable[eAASSOCIATERequestLocalUser].transitions[GetStateIndex(eSta4LocalAssocDone)] = 
    Transition::MakeNew(eSta5WaitRemoteAssoc, new ULActionAE2());
//row 3
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta6TransferReady, new ULActionAE3());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_ACPDUreceived].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());

//row 4
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAE4());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eASSOCIATE_RJPDUreceived].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
//row 5
  mTable[eTransportConnIndicLocal].transitions[GetStateIndex(eSta1Idle)] = 
    Transition::MakeNew(eSta2Open, new ULActionAE5());
//row 6
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta3WaitLocalAssoc | eSta13AwaitingClose, new ULActionAE6());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAE4());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eAASSOCIATE_RQPDUreceived].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA7());
//row 7
  mTable[eAASSOCIATEresponseAccept].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta7WaitRelease, new ULActionAE7());
//row 8
  mTable[eAASSOCIATEresponseReject].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta7WaitRelease, new ULActionAE7());
  //Row 9
  mTable[ePDATArequest].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta6TransferReady, new ULActionDT1());
  mTable[ePDATArequest].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta8WaitLocalRelease, new ULActionAR7());
//row 10
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta6TransferReady, new ULActionDT2());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta7WaitRelease, new ULActionAR6());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[ePDATATFPDU].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
//row 11
  mTable[eARELEASERequest].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta7WaitRelease, new ULActionAR1());
//row 12
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta8WaitLocalRelease, new ULActionAR2());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta9ReleaseCollisionRqLocal | eSta10ReleaseCollisionAc, new ULActionAR8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceivedOpen].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
//row 13
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAR3());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARELEASE_RQPDUReceived].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  //Row 14
  mTable[eARELEASEResponse].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAR4());
  mTable[eARELEASEResponse].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta11ReleaseCollisionRq, new ULActionAR9);
  mTable[eARELEASEResponse].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAR4());
  //row 15
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta4LocalAssocDone)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eAABORTRequest].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  //row 16
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  mTable[eAABORTPDUReceivedOpen].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  //row 17
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA5());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta4LocalAssocDone)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  mTable[eTransportConnectionClosed].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA5());
  //row 18
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta2Open)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  //row 19
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta3WaitLocalAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta13AwaitingClose)] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta5WaitRemoteAssoc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta6TransferReady)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta7WaitRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta8WaitLocalRelease)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta9ReleaseCollisionRqLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta10ReleaseCollisionAc)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta11ReleaseCollisionRq)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  mTable[eARTIMTimerExpired].transitions[GetStateIndex(eSta12ReleaseCollisionAcLocal)] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA7());

}

//given the event and the state of the connection, call the appropriate action
EStateID ULTransitionTable::HandleEvent(ULEvent& inEvent, ULConnection& inConnection) const{
  //first, find the Event
  EEventID eventID = inEvent.GetEvent();
  if (eventID >= 0 && eventID < eEventDoesNotExist){//make sure that the event exists
    //have to convert the state ID into an index
    int stateIndex = GetStateIndex(inConnection.GetState());
    if (stateIndex >= 0 && stateIndex < cMaxStateID){
      if (mTable[eventID].transitions[stateIndex].mAction != NULL){
        return mTable[eventID].transitions[stateIndex].mAction->PerformAction(inEvent, inConnection);
      }
    }
  }
  return eStaDoesNotExist;
}