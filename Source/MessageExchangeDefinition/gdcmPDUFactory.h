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
      static BasePDU* ConstructReleasePDU();
      static BasePDU* ConstructAbortPDU();

      //these are the composite PDU construction methods for the PDataPDUs.
      //basically, builds a pdatapdu, and then puts the appropriate information in
      //for the appropriate composite service (c-echo, c-find, c-store, c-get, c-move)
      static BasePDU* CreateCEchoPDU();
      static BasePDU* CreateCStorePDU(DataSet *inDataSet);
      static BasePDU* CreateCFindPDU(DataSet* inDataSet);
    };
  }
}
#endif //PDUFACTORY_H
