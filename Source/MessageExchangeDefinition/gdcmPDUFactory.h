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

namespace gdcm{
  namespace network{
    class PDUFactory {
      public:
      static BasePDU* ConstructPDU(uint8_t itemtype);//eventually needs to be smartpointer'd
      static EEventID DetermineEventByPDU(BasePDU* inPDU);
    };
  }
}
#endif //PDUFACTORY_H