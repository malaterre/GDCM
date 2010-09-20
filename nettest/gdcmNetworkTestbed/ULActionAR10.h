/*
This header defines the payload and class for Action AR-10, the tenth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue A-RELEASE confirmation primitive

Next State: 
eSta12ReleaseCollisionAcLocal
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR10Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR10 {
    public:
      void PerformAction();

    }
  }
}