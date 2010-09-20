/*
This header defines the payload and class for Action AR-3, the third action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue A-RELEASE confirmation primitive, and close transport connection

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR3Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR3 {
    public:
      void PerformAction();

    }
  }
}