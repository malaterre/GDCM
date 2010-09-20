/*
This header defines the payload and class for Action AE-4, the fourth action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection

Next state is:
eSta1Idle

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE4Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE4 {
    public:
      void PerformAction();

    }
  }
}