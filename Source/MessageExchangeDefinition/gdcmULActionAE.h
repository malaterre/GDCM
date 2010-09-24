/*

This header defines the classes for the AE Actions,
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.

*/

#include "gdcmULAction.h"

namespace gdcm {
  namespace network {

    //Issue TRANSPORT CONNECT request primitive to local transport service.
    class ULActionAE1 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Send A-ASSOCIATE-RQ-PDU
    //Next State: eSta5WaitRemoteAssoc
    class ULActionAE2 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Issue A-ASSOCIATE confirmation (accept) primitive
    //Next State: eSta6TransferReady
    class ULActionAE3 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection
    //Next State: eSta1Idle
    class ULActionAE4 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Issue Transport connection response primitive, start ARTIM timer
    //Next State: eSta2Open
    class ULActionAE5 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Stop ARTIM timer and if A-ASSOCIATE-RQ acceptable by service-provider:
    //- issue A-ASSOCIATE indication primitive
    //Next state: eSta3WaitLocalAssoc
    //otherwise:
    //- issue A-ASSOCIATE-RJ-PDU and start ARTIM timer
    //Next state: eSta13AwaitingClose
    class ULActionAE6 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Send A-ASSOCIATE-AC PDU
    //Next State: eSta6TransferReady
    class ULActionAE7 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };

    //Send A-ASSOCIATE-RJ PDU and start ARTIM timer
    //Next State: eSta13AwaitingClose
    class ULActionAE8 : public ULAction {
    public:
      EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection);
    };
  }
}