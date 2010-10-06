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
  std::vector<BasePDU*> theDataPDUs = inEvent.GetPDUs();
  std::vector<BasePDU*>::const_iterator itor = theDataPDUs.begin();
  //they can all be sent at once because of the structure in 3.8 7.6-- pdata does not wait for a response.
  for (itor = theDataPDUs.begin(); itor < theDataPDUs.end(); itor++) {

    PDataTFPDU* dataPDU = dynamic_cast<PDataTFPDU*>(*itor);
    if (dataPDU == NULL){
      throw new gdcm::Exception("Data sending event PDU malformed.");
      return eStaDoesNotExist;
    }
    dataPDU->Write(*inConnection.GetProtocol());
    inConnection.GetProtocol()->flush();
  }
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
