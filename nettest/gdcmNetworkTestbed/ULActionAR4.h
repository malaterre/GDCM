/*
This header defines the payload and class for Action AR-4, the fourth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue A-RELEASE-RP PDU and start ARTIM timer

Next State: 
eSta13AwaitingClose
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR4Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR4 {
    public:
      void PerformAction();

    }
  }
}