/*
This header defines the classes for the AA Actions,
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.

*/
#ifndef ULACTIONAA_H
#define ULACTIONAA_H

#include "gdcmULAction.h"

namespace gdcm {
  namespace network {

    //Send A-ABORT PDU (service-user source) and start (or restart if already started) ARTIM timer
    //Next State: eSta13AwaitingClose
    class ULActionAA1 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Stop ARTIM timer if running.  Close transport connection.
    //Next State: eSta1Idle
    class ULActionAA2 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //If (service-user initiated abort)
    //- issue A-ABORT indication and close transport connection
    //otherwise (service-provider initiated abort):
    //- issue A-P-ABORT indication and close transport connection
    //Next State: eSta1Idle
    class ULActionAA3 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Issue A-P-ABORT indication primitive
    //Next State: eSta1Idle
    class ULActionAA4 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Stop ARTIM timer
    //Next State: eSta1Idle
    class ULActionAA5 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Ignore PDU
    //Next State: eSta13AwaitingClose
    class ULActionAA6 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Send A-ABORT PDU
    //Next State: eSta13AwaitingClose
    class ULActionAA7 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Send A-ABORT PDU (service-provider source), issue an A-P-ABORT indication, and start ARTIM timer
    //Next State: eSta13AwaitingClose
    class ULActionAA8 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };
  }
}

#endif
