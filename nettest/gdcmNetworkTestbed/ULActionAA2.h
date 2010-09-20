/*
This header defines the payload and class for Action AA-2, the second action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Stop ARTIM timer if running.  Close transport connection.

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA2Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA2 {
    public:
      void PerformAction();

    }
  }
}