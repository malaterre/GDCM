/*
This file is the implementation of the ULTransitionTable class, including the actual event handling as well as the construction of the table itself.

*/

#include "gdcmULTransitionTable.h"
#include "gdcmULActionAA.h"
#include "gdcmULActionAE.h"
#include "gdcmULActionAR.h"
#include "gdcmULActionDT.h"

using namespace gdcm::primitives;

//construct the table
ULTransitionTable::ULTransitionTable(){
  //row 1
  TableRow theRow(eAASSOCIATERequestLocalUser);
  theRow.transitions[eSta1Idle] = Transition::MakeNew(eSta4LocalAssocDone, new ULActionAE1());
  mTable.push_back(theRow);
  //row 2
  TableRow theRow2(eAASSOCIATERequestLocalUser);
  theRow2.transitions[eSta4LocalAssocDone] = 
    Transition::MakeNew(eSta5WaitRemoteAssoc, new ULActionAE2());
  mTable.push_back(theRow2);
//row 3
  TableRow theRow3(eASSOCIATE_ACPDUreceived);
  theRow3.transitions[eSta2Open] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow3.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta6TransferReady, new ULActionAE3());
  theRow3.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow3.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  mTable.push_back(theRow3);

//row 4
  TableRow theRow4(eASSOCIATE_RJPDUreceived);
  theRow4.transitions[eSta2Open] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow4.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAE4());
  theRow4.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow4.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  mTable.push_back(theRow4);
//row 5
  TableRow theRow5(eTransportConnIndicLocal);
  theRow5.transitions[eSta1Idle] = Transition::MakeNew(eSta2Open, new ULActionAE5());
  mTable.push_back(theRow5);
//row 6
  TableRow theRow6(eAASSOCIATE_RQPDUreceived);
  theRow6.transitions[eSta2Open] = 
    Transition::MakeNew(eSta3WaitLocalAssoc | eSta13AwaitingClose, new ULActionAE6());
  theRow6.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAE4());
  theRow6.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow6.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA7());
  mTable.push_back(theRow6);
//row 7
  TableRow theRow7(eAASSOCIATEresponseAccept);
  theRow7.transitions[eSta3WaitLocalAssoc] = Transition::MakeNew(eSta7WaitRelease, new ULActionAE7());
  mTable.push_back(theRow7);
//row 8
  TableRow theRow8(eAASSOCIATEresponseReject);
  theRow8.transitions[eSta3WaitLocalAssoc] = Transition::MakeNew(eSta7WaitRelease, new ULActionAE7());
  mTable.push_back(theRow8);
  //Row 9
  TableRow theRow9(ePDATArequest);
  theRow9.transitions[eSta6TransferReady] = Transition::MakeNew(eSta6TransferReady, new ULActionDT1());
  theRow9.transitions[eSta8WaitLocalRelease] = Transition::MakeNew(eSta8WaitLocalRelease, new ULActionAR7());
  mTable.push_back(theRow9);
//row 10
  TableRow theRow10(ePDATATFPDU);
  theRow10.transitions[eSta2Open] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow10.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta6TransferReady, new ULActionDT2());
  theRow10.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta7WaitRelease, new ULActionAR6());
  theRow10.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow10.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  mTable.push_back(theRow10);
//row 11
  TableRow theRow11(eARELEASERequest);
  theRow11.transitions[eSta6TransferReady] = Transition::MakeNew(eSta7WaitRelease, new ULActionAR1());
  mTable.push_back(theRow11);
//row 12
  TableRow theRow12(eARELEASE_RQPDUReceivedOpen);
  theRow12.transitions[eSta2Open] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow12.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta8WaitLocalRelease, new ULActionAR2());
  theRow12.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta9ReleaseCollisionRqLocal | eSta10ReleaseCollisionAc, new ULActionAR8());
  theRow12.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow12.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  mTable.push_back(theRow12);
//row 13
  TableRow theRow13(eARELEASE_RQPDUReceived);
  theRow13.transitions[eSta2Open] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow13.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta1Idle, new ULActionAR3());
  theRow13.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow13.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA6());
  mTable.push_back(theRow13);
  //Row 14
  TableRow theRow14(eARELEASEResponse);
  theRow14.transitions[eSta8WaitLocalRelease] = Transition::MakeNew(eSta13AwaitingClose, new ULActionAR4());
  theRow14.transitions[eSta9ReleaseCollisionRqLocal] = Transition::MakeNew(eSta11ReleaseCollisionRq, new ULActionAR9);
  theRow14.transitions[eSta12ReleaseCollisionAcLocal] = Transition::MakeNew(eSta13AwaitingClose, new ULActionAR4());
  mTable.push_back(theRow14);
  //row 15
  TableRow theRow15(eAABORTRequest);
  theRow15.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta4LocalAssocDone] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  theRow15.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow15.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  mTable.push_back(theRow15);
  //row 16
  TableRow theRow16(eAABORTPDUReceivedOpen);
  theRow16.transitions[eSta2Open] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  theRow16.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA3());
  theRow16.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA2());
  mTable.push_back(theRow16);
  //row 17
  TableRow theRow17(eTransportConnectionClosed);
  theRow17.transitions[eSta2Open] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA5());
  theRow17.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta4LocalAssocDone] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA4());
  theRow17.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA5());
  mTable.push_back(theRow17);
  //row 18
  TableRow theRow18(eARTIMTimerExpired);
  theRow18.transitions[eSta2Open] = Transition::MakeNew(eSta1Idle, new ULActionAA2());
  theRow18.transitions[eSta13AwaitingClose] = Transition::MakeNew(eSta1Idle, new ULActionAA2());
  mTable.push_back(theRow18);
  //row 19
  TableRow theRow19(eARTIMTimerExpired);
  theRow19.transitions[eSta3WaitLocalAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA1());
  theRow19.transitions[eSta13AwaitingClose] = 
    Transition::MakeNew(eSta1Idle, new ULActionAA8());
  theRow19.transitions[eSta5WaitRemoteAssoc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta6TransferReady] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta7WaitRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta8WaitLocalRelease] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta9ReleaseCollisionRqLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta10ReleaseCollisionAc] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta11ReleaseCollisionRq] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA8());
  theRow19.transitions[eSta12ReleaseCollisionAcLocal] = 
    Transition::MakeNew(eSta13AwaitingClose, new ULActionAA7());
  mTable.push_back(theRow19);

}

//given the event and the state of the connection, call the appropriate action
EStateID ULTransitionTable::HandleEvent(ULEvent& inEvent, ULConnection& inConnection) const{
  //first, find the Event
  EEventID eventID = inEvent.GetEvent();
  if (eventID >= 0 && eventID < mTable.size()){//make sure that the event exists
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