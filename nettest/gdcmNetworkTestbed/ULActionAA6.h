/*
This header defines the payload and class for Action AA-6, the sixth action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Ignore PDU

Next State: 
eSta13AwaitingClose
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA6Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA6 {
    public:
      void PerformAction();

    }
  }
}