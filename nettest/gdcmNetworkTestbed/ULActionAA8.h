/*
This header defines the payload and class for Action AA-8, the eigth action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Send A-ABORT PDU (service-provider source), issue an A-P-ABORT indication, and start ARTIM timer

Next State: 
eSta13AwaitingClose
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA8Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA8 {
    public:
      void PerformAction();

    }
  }
}