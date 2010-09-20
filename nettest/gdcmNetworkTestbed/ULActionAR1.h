/*
This header defines the payload and class for Action AR-1, the first action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Send A-RELEASE-RQ-PDU

Next State: 
eSta7WaitRelease
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR1Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR1 {

    public:
      void PerformAction();
    }
  }
}