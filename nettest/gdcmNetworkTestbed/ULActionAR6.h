/*
This header defines the payload and class for Action AR-6, the sixth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue P-Data indication

Next State: 
eSta7WaitRelease
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR6Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR6 {
    public:
      void PerformAction();

    }
  }
}