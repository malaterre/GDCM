/*
This header defines the payload and class for Action AR-8, the eigth action in the 
Association Release Related Actions (Table 9-8 of ps 3.8-2009).

It will:
Issue A-RELEASE indication (release collision):
- If association-requestor, next state is eSta9ReleaseCollisionRqLocal
- if not, next state is eSta10ReleaseCollisionAc

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAR8Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAR8 {
    public:
      void PerformAction();

    }
  }
}