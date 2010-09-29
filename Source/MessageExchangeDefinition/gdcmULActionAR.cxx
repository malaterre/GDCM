/*
This file contains the implementation for the classes for the AR Actions,
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.
*/

#include "gdcmULActionAR.h"
#include "gdcmARTIMTimer.h"
#include "gdcmAReleaseRQPDU.h"
#include "gdcmAReleaseRPPDU.h"
#include "gdcmPDataTFPDU.h"

using namespace gdcm::network;

//Send A-RELEASE-RQ-PDU
EStateID ULActionAR1::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AReleaseRQPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush(); // important


  outWaitingForEvent = true;

  return eSta7WaitRelease;
}

//Issue A-RELEASE indication primitive
EStateID ULActionAR2::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  outWaitingForEvent = false;
  outRaisedEvent = eARELEASERequest;//here's the primitive being sent
  return eSta8WaitLocalRelease;
}

//Issue A-RELEASE confirmation primitive, and close transport connection
EStateID ULActionAR3::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  outWaitingForEvent = false;
  outRaisedEvent = eARELEASERequest;
  //inConnection.GetProtocol()->dis
  //I can't see a way to close this connection directly; I guess it just gets reopened elsewhere?
  return eSta1Idle;
}

//Issue A-RELEASE-RP PDU and start ARTIM timer
EStateID ULActionAR4::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AReleaseRPPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();
  inConnection.GetTimer().Start();
  outWaitingForEvent = false;
  outRaisedEvent = eARELEASERequest;

  return eSta13AwaitingClose;
}

//Stop ARTIM timer
EStateID ULActionAR5::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  inConnection.GetTimer().Stop();
  return eSta1Idle;
}

//Issue P-DATA indication
EStateID ULActionAR6::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  outWaitingForEvent = true;
  outRaisedEvent = eEventDoesNotExist;
  return eSta7WaitRelease;
}

//Issue P-DATA-TF PDU
EStateID ULActionAR7::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  PDataTFPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();
  return eSta8WaitLocalRelease;
}

//Issue A-RELEASE indication (release collision):
//- If association-requestor, next state is eSta9ReleaseCollisionRqLocal
//- if not, next state is eSta10ReleaseCollisionAc
EStateID ULActionAR8::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  return eSta10ReleaseCollisionAc;
}

//Send A-RELEASE-RP PDU
EStateID ULActionAR9::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AReleaseRPPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();

  outWaitingForEvent = true;
  return eSta11ReleaseCollisionRq;
}

//Issue A-RELEASE confirmation primitive
EStateID ULActionAR10::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  outWaitingForEvent = false;
  outRaisedEvent = eARELEASEResponse;

  return eSta12ReleaseCollisionAcLocal;
}
    
