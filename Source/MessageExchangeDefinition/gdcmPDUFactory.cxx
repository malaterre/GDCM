/*
basically, given an initial byte, construct the appropriate PDU.
this way, the event loop doesn't have to know about all the different PDU types.

name and date: 25 Sept 2010 mmr
*/
#include "gdcmPDUFactory.h"
#include "gdcmAAbortPDU.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmAAssociateRJPDU.h"
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAReleaseRPPDU.h"
#include "gdcmAReleaseRQPDU.h"
#include "gdcmPDataTFPDU.h"

using namespace gdcm::network;

//eventually needs to be smartpointer'd
BasePDU* PDUFactory::ConstructPDU(uint8_t itemtype){
  BasePDU* thePDU = NULL;
  switch (itemtype){
    case 0x01:
      thePDU = new AAssociateRQPDU();
      break;
    case 0x02:
      thePDU = new AAssociateACPDU();
      break;
    case 0x03:
      thePDU = new AAssociateRJPDU();
      break;
    case 0x04:
      thePDU = new PDataTFPDU();
      break;
    case 0x05:
      thePDU = new AReleaseRQPDU();
      break;
    case 0x06:
      thePDU = new AReleaseRPPDU();
      break;
    case 0x07:
      thePDU = new AAbortPDU();
      break;
      //default is that the PDU remains null
  }
  return thePDU;

}

//determine which event was received by the PDU type
EEventID PDUFactory::DetermineEventByPDU(BasePDU* inPDU){
  if(inPDU) {
  AAssociateRQPDU* theAAssociateRQPDU = dynamic_cast<AAssociateRQPDU*>(inPDU);
  if (theAAssociateRQPDU != NULL){
    return eAASSOCIATE_RQPDUreceived;
  }
  AAssociateACPDU* theAAssociateACPDU = dynamic_cast<AAssociateACPDU*>(inPDU);
  if (theAAssociateACPDU != NULL){
    return eASSOCIATE_ACPDUreceived;
  }
  AAssociateRJPDU* theAAssociateRJPDU = dynamic_cast<AAssociateRJPDU*>(inPDU);
  if (theAAssociateRJPDU != NULL){
    return eASSOCIATE_RJPDUreceived;
  }
  PDataTFPDU* thePDataTFPDU = dynamic_cast<PDataTFPDU*>(inPDU);
  if (thePDataTFPDU != NULL){
    return ePDATATFPDU;
  }
  AReleaseRQPDU* theAReleaseRQPDU = dynamic_cast<AReleaseRQPDU*>(inPDU);
  if (theAReleaseRQPDU != NULL){
    return eARELEASE_RQPDUReceived;
  }
  AReleaseRPPDU* theAReleaseRPPDU = dynamic_cast<AReleaseRPPDU*>(inPDU);
  if (theAReleaseRPPDU != NULL){
    return eARELEASEResponse;
  }
  AAbortPDU* theAAbortPDU = dynamic_cast<AAbortPDU*>(inPDU);
  if (theAAbortPDU != NULL){
    return eAABORTPDUReceivedOpen;
  }
}
  return eEventDoesNotExist;
}
