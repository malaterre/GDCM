/*
base class for network events.

An event consists of the event ID and the data associated with that event.

Note that once a PDU is created, it is now the responsibility of the associated event to destroy it!
name and date: 25 sept 2010 mmr

*/
#include "gdcmNetworkStateID.h"
#include "gdcmNetworkEvents.h"
#include "gdcmBasePDU.h"
#include <vector>

#ifndef ULEVENT_H
#define ULEVENT_H

namespace gdcm {
  namespace network {

    class ULEvent {
      EEventID mEvent;
      std::vector<BasePDU*> mBasePDU;

      void DeletePDUVector(){
        std::vector<BasePDU*>::iterator baseItor;
        for (baseItor = mBasePDU.begin(); baseItor < mBasePDU.end(); baseItor++){
          if (*baseItor != NULL){
            delete *baseItor;
            *baseItor = NULL;
          }
        }
      }

    public:
      ULEvent(const EEventID& inEventID, std::vector<BasePDU*> inBasePDU){
        mEvent = inEventID;
        mBasePDU = inBasePDU;
      }
      ULEvent(const EEventID& inEventID, BasePDU* inBasePDU){
        mEvent = inEventID;
        mBasePDU.push_back(inBasePDU);
      }
      ~ULEvent(){
        DeletePDUVector();
      }

      EEventID GetEvent() const { return mEvent; }
      std::vector<BasePDU*> GetPDUs() const { return mBasePDU; }

      void SetEvent(const EEventID& inEvent) { mEvent = inEvent; }
      void SetPDU(std::vector<BasePDU*> inPDU) { 
        DeletePDUVector();
        mBasePDU = inPDU;
      }
    };
  }
}

#endif //ULEVENT_H