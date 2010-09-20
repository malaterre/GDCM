/*
This header defines the payload and class for Action DT-1, the first action in the 
Data Transfer Related Actions (Table 9-7 of ps 3.8-2009).

It will:
Send P-DATA-TF PDU

next state:
eSta6TransferReady

*/

#include "ULAction.h"

namespace gdcm {
  namespace primitives {
    class ULActionDT1Payload {
    public:
      //whatever goes into this action

    }


    class ULActionDT1 {
    public:
      void PerformAction();

    }
  }
}