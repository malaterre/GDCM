/*
base class for network events.

An event consists of the event ID and the data associated with that event.

Note that once a PDU is created, it is now the responsibility of the associated event to destroy it!
name and date: 25 sept 2010 mmr

*/
#include "gdcmNetworkStateID.h"
#include "gdcmNetworkEvents.h"
#include "gdcmBasePDU.h"

#ifndef ULEVENT_H
#define ULEVENT_H

namespace gdcm {
  namespace network {

    class ULEvent {
      EEventID mEvent;
      BasePDU* mBasePDU;
    public:
      ULEvent(const EEventID& inEventID, BasePDU* inBasePDU){
        mEvent = inEventID;
        mBasePDU = inBasePDU;
      }
      ~ULEvent(){
        if (mBasePDU != NULL){
          delete mBasePDU;
          mBasePDU = NULL;
        }
      }

      EEventID GetEvent() const { return mEvent; }
      BasePDU* GetPDU() const { return mBasePDU; }

      void SetEvent(const EEventID& inEvent) { mEvent = inEvent; }
      void SetPDU(BasePDU* inPDU) { 
        if (mBasePDU != NULL){
          delete mBasePDU;
        } 
        mBasePDU = inPDU;
      }
    };
  }
}

#endif //ULEVENT_H