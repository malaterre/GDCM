/*
This header defines the payload and class for Action AA-7, the seventh action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Send A-ABORT PDU

Next State: 
eSta13AwaitingClose
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA7Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA7 {
    public:
      void PerformAction();

    }
  }
}