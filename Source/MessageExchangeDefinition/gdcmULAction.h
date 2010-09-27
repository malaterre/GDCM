/*
A ULConnection in a given ULState can perform certain ULActions.  This base class
provides the interface for running those ULActions on a given ULConnection.

Essentially, the ULConnectionManager will take this object, determined from the current
ULState of the ULConnection, and pass the ULConnection object to the ULAction.  The ULAction
will then invoke whatever necessary commands are required by a given action.

The result of a ULAction is a ULEvent (ie, what happened as a result of the action).

This ULEvent is passed to the ULState, so that the transition to the next state can occur.

Actions are associated with Payloads-- be thos filestreams, AETitles to establish connections, 
whatever.  The actual parameters that the user will pass via an action will come through 
a Payload object, which should, in itself, be some gdcm-based object (but not all objects can
be payloads; sending a single dataelement as a payload isn't meaningful).  As such, each action
has its own particular payload.

For the sake of keeping files together, both the particular payload class and the action class
will be defined in the same header file.  Payloads should JUST be data (or streams), NO METHODS.

name and date: 16 sept 2010 mmr

27 sept 2010 mmr: update on how to handle state transitions.

Some actions perform changes that should raise events on the local system, and some
actions perform changes that will require waiting for events from the remote system.

Therefore, this base action has been modified so that those events are set by each action.  
When the event loop runs an action, it will then test to see if a local event was raised by the
action, and if so, perform the appropriate subsequent action.  If the action requires waiting
for a response from the remote system, then the event loop will sit there (presumably with the
ARTIM timer running) and wait for a response from the remote system.  Once a response is
obtained, then the the rest of the state transitions can happen.

*/

#include "gdcmNetworkStateID.h"
#include "gdcmULEvent.h"
#include "gdcmULConnection.h"

#ifndef ULACTION_H
#define ULACTION_H

namespace gdcm {
  namespace network {

    class ULAction {
    private:
      //cannot copy a ULAction
      ULAction(const gdcm::network::ULAction& inAction) {};

    protected:


    public:
      ULAction() {};
      //make sure destructors are virtual to avoid memory leaks
      virtual ~ULAction() {};

      virtual EStateID PerformAction(ULEvent& inEvent, ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& outRaisedEvent) = 0;
    };
  }
}

#endif //ULACTION_H