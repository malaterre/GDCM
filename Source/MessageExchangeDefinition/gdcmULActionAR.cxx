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

using namespace gdcm::primitives;
using namespace gdcm::network;

//Send A-RELEASE-RQ-PDU
EStateID ULActionAR1::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  AReleaseRQPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());

  return eSta7WaitRelease;
}

//Issue A-RELEASE indication primitive
EStateID ULActionAR2::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta8WaitLocalRelease;
}

//Issue A-RELEASE confirmation primitive, and close transport connection
EStateID ULActionAR3::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta1Idle;
}

//Issue A-RELEASE-RP PDU and start ARTIM timer
EStateID ULActionAR4::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  AReleaseRPPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();

  return eSta13AwaitingClose;
}

//Stop ARTIM timer
EStateID ULActionAR5::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  inConnection.GetTimer().Stop();
  return eSta1Idle;
}

//Issue P-Data indication
EStateID ULActionAR6::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta7WaitRelease;
}

//Issue P-DATA-TF PDU
EStateID ULActionAR7::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  PDataTFPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  return eSta8WaitLocalRelease;
}

//Issue A-RELEASE indication (release collision):
//- If association-requestor, next state is eSta9ReleaseCollisionRqLocal
//- if not, next state is eSta10ReleaseCollisionAc
EStateID ULActionAR8::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta10ReleaseCollisionAc;
}

//Send A-RELEASE-RP PDU
EStateID ULActionAR9::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  AReleaseRPPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  return eSta11ReleaseCollisionRq;
}

//Issue A-RELEASE confirmation primitive
EStateID ULActionAR10::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta12ReleaseCollisionAcLocal;
}
    