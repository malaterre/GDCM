/*
This header defines the payload and class for Action AE-2, the second action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Send A-ASSOCIATE-RQ-PDU

The next state is:
eSta5WaitRemoteAssoc

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE2Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE2 {
    public:
      void PerformAction();

    }
  }
}