/*
This header defines the payload and class for Action AA-5, the fifth action in the 
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

It will:
Stop ARTIM timer

Next State: 
eSta1Idle
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAA5Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAA5 {
    public:
      void PerformAction();

    }
  }
}