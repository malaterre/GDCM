/*
This header defines the payload and class for Action AA-4, the fourth action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Issue A-P-ABORT indication primitive

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA4Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA4 {
    public:
      void PerformAction();

    }
  }
}