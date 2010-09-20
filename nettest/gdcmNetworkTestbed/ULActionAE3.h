/*
This header defines the payload and class for Action AE-3, the third action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Issue A-ASSOCIATE confirmation (accept) primitive

Next state:
eSta6TransferReady
*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE3Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE3 {
    public:
      void PerformAction();

    }
  }
}