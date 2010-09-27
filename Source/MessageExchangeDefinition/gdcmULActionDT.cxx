/*
This file contains the implementation for the classes for the DT Actions,
Data Transfer Related Actions (Table 9-8 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.
*/

#include "gdcmULActionDT.h"
#include "gdcmARTIMTimer.h"
#include "gdcmPDataTFPDU.h"

using namespace gdcm::network;

//Send P-DATA-TF PDU
EStateID ULActionDT1::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent)
{

  PDataTFPDU* dataPDU = dynamic_cast<PDataTFPDU*>(inEvent.GetPDU());
  if (dataPDU == NULL){
    throw new gdcm::Exception("Data sending event PDU malformed.");
    return eStaDoesNotExist;
  }
  dataPDU->Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();

  outWaitingForEvent = true;//wait for a response that the data got there.
  outRaisedEvent = ePDATArequest;

  return eSta6TransferReady;
}

//Send P-DATA indication primitive
//for now, does nothing, stops the event loop
EStateID ULActionDT2::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  outWaitingForEvent = false;
  outRaisedEvent = ePDATArequest;
  return eSta6TransferReady;
}
