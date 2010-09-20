/*
This header defines the payload and class for Action AR-5, the fifth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Stop ARTIM timer

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR5Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR5 {
    public:
      void PerformAction();

    }
  }
}