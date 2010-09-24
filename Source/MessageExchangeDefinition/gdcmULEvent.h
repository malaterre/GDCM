/*
base class for network events.

An event consists of the event ID and the data associated with that event.

*/
#include "gdcmNetworkStateID.h"
#include "gdcmNetworkEvents.h"
#include "gdcmDataSet.h"

#ifndef ULEVENT_H
#define ULEVENT_H

namespace gdcm {
  namespace network {

    class ULEvent {
      EEventID mEvent;
      DataSet mDataSet;
    public:
      ULEvent(const EEventID& inEventID, const DataSet& inDataSet){
        mEvent = inEventID;
        mDataSet = inDataSet;
      }

      EEventID GetEvent() const { return mEvent; }
      DataSet GetDataSet() const { return mDataSet; }

      void SetEvent(const EEventID& inEvent) { mEvent = inEvent; }
      void SetDataSet(const DataSet& inDataSet) { mDataSet = inDataSet; }
    };
  }
}

#endif //ULEVENT_H