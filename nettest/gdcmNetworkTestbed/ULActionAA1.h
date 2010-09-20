/*
This header defines the payload and class for Action AA-1, the first action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Send A-ABORT PDU (service-user source) and start (or restart if already started) ARTIM timer

Next State: 
eSta13AwaitingClose
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA1Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA1 {
    public:
      void PerformAction();
    }
  }
}