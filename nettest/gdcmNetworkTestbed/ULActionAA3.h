/*
This header defines the payload and class for Action AA-3, the third action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
If (service-user initiated abort)
- issue A-ABORT indication and close transport connection
otherwise (service-provider initiated abort):
- issue A-P-ABORT indication and close transport connection

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA3Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA3 {

    public:
      void PerformAction();
    }
  }
}