/*
This header defines the payload and class for Action AR-7, the seventh action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue P-DATA-TF PDU

Next State: 
eSta8WaitLocalRelease
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR7Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR7 {
    public:
      void PerformAction();

    }
  }
}