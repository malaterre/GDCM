/*
basically, given an initial byte, construct the appropriate PDU.
this way, the event loop doesn't have to know about all the different PDU types.

name and date: 25 Sept 2010 mmr

Updte on 27 sept 2010 mmr: since this is where all PDUs are included, also use this
class to construct specific instances of PDUs, and return the BasePDU class.
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
  ///
    const PresentationDataValue &pdv = thePDataTFPDU->GetPresentationDataValue(0);
    int mh = pdv.GetMessageHeader();
    if( mh == 3 )
      {
      // E.2 MESSAGE CONTROL HEADER ENCODING
      // If bit 1 is set to 1, the following fragment shall contain the last
      // fragment of a Message Data Set or of a Message Command.
      std::cout << "This was the last fragment of the message data set" << std::endl;
      }
    return ePDATATFPDU;
  }
  AReleaseRQPDU* theAReleaseRQPDU = dynamic_cast<AReleaseRQPDU*>(inPDU);
  if (theAReleaseRQPDU != NULL){
    return eARELEASE_RQPDUReceivedOpen;
  }
  AReleaseRPPDU* theAReleaseRPPDU = dynamic_cast<AReleaseRPPDU*>(inPDU);
  if (theAReleaseRPPDU != NULL){
    return eARELEASE_RPPDUReceived;
  }
  AAbortPDU* theAAbortPDU = dynamic_cast<AAbortPDU*>(inPDU);
  if (theAAbortPDU != NULL){
    return eAABORTPDUReceivedOpen;
  }
}
  return eEventDoesNotExist;
}

BasePDU* PDUFactory::ConstructReleasePDU(){
  AReleaseRQPDU* theAReleaseRQPDU = new AReleaseRQPDU();

  return theAReleaseRQPDU;
}
BasePDU* PDUFactory::ConstructAbortPDU(){
  AAbortPDU* theAAbortPDU = new AAbortPDU();

  return theAAbortPDU;
}
BasePDU* PDUFactory::CreateCEchoPDU(){
  
  PDataTFPDU* thePDataTFPDU = new PDataTFPDU();
  gdcm::network::PresentationDataValue pdv;
  thePDataTFPDU->AddPresentationDataValue( pdv );
  return thePDataTFPDU;
}


BasePDU* PDUFactory::CreateCFindPDU(gdcm::DataSet* inDataSet){

  PDataTFPDU* thePDataTFPDU = new PDataTFPDU();
  gdcm::network::PresentationDataValue pdv;
  thePDataTFPDU->AddPresentationDataValue( pdv );

  return thePDataTFPDU;


}