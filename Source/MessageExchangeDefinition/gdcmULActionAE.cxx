/*

This file contains the implementation for the classes for the AE Actions,
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.

*/

#include "gdcmULActionAE.h"
#include "gdcmARTIMTimer.h"

#include <socket++/echo.h>//for setting up the local socket

using namespace gdcm::primitives;

//Issue TRANSPORT CONNECT request primitive to local transport service.
EStateID ULActionAE1::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  //opening a local socket
  echo e(protocol::tcp);
  inConnection.mSocket = e;
  return eSta4LocalAssocDone;
}

//Send A-ASSOCIATE-RQ-PDU
EStateID ULActionAE2::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta5WaitRemoteAssoc;
}

//Issue A-ASSOCIATE confirmation (accept) primitive
EStateID ULActionAE3::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta6TransferReady;
}

//Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection
EStateID ULActionAE4::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta1Idle;
}

//Issue Transport connection response primitive, start ARTIM timer
EStateID ULActionAE5::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta2Open;
}

//Stop ARTIM timer and if A-ASSOCIATE-RQ acceptable by service-provider:
//- issue A-ASSOCIATE indication primitive
//Next state: eSta3WaitLocalAssoc
//otherwise:
//- issue A-ASSOCIATE-RJ-PDU and start ARTIM timer
//Next state: eSta13AwaitingClose
EStateID ULActionAE6::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta13AwaitingClose;
}

//Send A-ASSOCIATE-AC PDU
EStateID ULActionAE7::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta6TransferReady;
}

//Send A-ASSOCIATE-RJ PDU and start ARTIM timer
EStateID ULActionAE8::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  return eSta13AwaitingClose;
}

    