/*
This header defines the payload and class for Action AE-7, the seventh action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Send A-ASSOCIATE-AC PDU

next state:
eSta6TransferReady

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE7Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE7 {
    public:
      void PerformAction();

    }
  }
}