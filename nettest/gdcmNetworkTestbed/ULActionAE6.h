/*
This header defines the payload and class for Action AE-6, the sixth action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Stop ARTIM timer and if A-ASSOCIATE-RQ acceptable by service-provider:
  - issue A-ASSOCIATE indication primitive
  Next state: eSta3WaitLocalAssoc

otherwise:
  - issue A-ASSOCIATE-RJ-PDU and start ARTIM timer
  Next state: eSta13AwaitingClose


*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE6Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE6 {
    public:
      void PerformAction();

    }
  }
}