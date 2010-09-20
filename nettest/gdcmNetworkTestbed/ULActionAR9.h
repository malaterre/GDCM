/*
This header defines the payload and class for Action AR-9, the ninth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Send A-RELEASE-RP PDU

Next State: 
eSta11ReleaseCollisionRq
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR9Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR9 {
    public:
      void PerformAction();

    }
  }
}