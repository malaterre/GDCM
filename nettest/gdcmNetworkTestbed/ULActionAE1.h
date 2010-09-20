/*
This header defines the payload and class for Action AE-1, the first action in the 
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

It will:
Issue TRANSPORT CONNECT request primitive to local transport service.

This can only be done on ULConnections in ULStateIdle, and results in a ULConnection in 
ULStateWaitLocalAssoc (if all goes well).

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionAE1Payload {
    public:
      //whatever goes into this action

    }


    class ULActionAE1 {
    public:
      void PerformAction();

    }
  }
}