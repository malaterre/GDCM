/*
basically, given an initial byte, construct the appropriate PDU.
this way, the event loop doesn't have to know about all the different PDU types.
name and date: 25 Sept 2010 mmr
*/
#ifndef PDUFACTORY_H
#define PDUFACTORY_H
#include "gdcmTypes.h"
#include "gdcmBasePDU.h"
#include "gdcmNetworkEvents.h"
#include "gdcmDataSet.h"

namespace gdcm{
  namespace network{
    class PDUFactory {
      public:
      static BasePDU* ConstructPDU(uint8_t itemtype);//eventually needs to be smartpointer'd
      static EEventID DetermineEventByPDU(BasePDU* inPDU);
      static BasePDU* ConstructDataPDU(DataSet* inDataSet); //returns a data pdu to be filled by user information
      //NULL for the data set returns a C-Echo PDU
      static BasePDU* ConstructReleasePDU();
      static BasePDU* ConstructAbortPDU();
    };
  }
}
#endif //PDUFACTORY_H