/*
This header defines the payload and class for Action AE-8, the eigth action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Send A-ASSOCIATE-RJ PDU and start ARTIM timer

next state:
eSta13AwaitingClose

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE8Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE8 {
    public:
      void PerformAction();

    }
  }
}