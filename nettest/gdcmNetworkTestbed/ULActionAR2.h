/*
This header defines the payload and class for Action AR-2, the second action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue A-RELEASE indication primitive

Next State: 
eSta8WaitLocalRelease
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR2Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR2 {

    public:
      void PerformAction();
    }
  }
}