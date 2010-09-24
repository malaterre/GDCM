/*
This header defines the classes for the DT Actions,
Data Transfer Related Actions (Table 9-8 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.
*/

#include "gdcmULAction.h"

namespace gdcm {
  namespace network {

    //Send P-DATA-TF PDU
    //Next state: eSta6TransferReady
    class ULActionDT1 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };
    
    //Send P-DATA indication primitive
    //Next state: eSta6TransferReady
    class ULActionDT2 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };
  }
}