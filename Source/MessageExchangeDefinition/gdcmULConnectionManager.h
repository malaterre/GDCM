/* 

The ULConnectionManager performs actions on the ULConnection given inputs from
the user and from the state of what's going on around the connection (ie,
timeouts of the ARTIM timer, responses from the peer across the connection, etc).

Its inputs are ULEvents, and it performs ULActions.

*/
#include "gdcmULTransitionTable.h"
#include "gdcmULConnection.h"
#include "gdcmULConnectionInfo.h"

namespace gdcm {
  namespace network {
    class ULConnectionManager {
    private:
      ULConnection* mConnection;
      ULTransitionTable mTransitions;
      
      //no copying
      ULConnectionManager(const gdcm::network::ULConnectionManager& inCM){};

      //event handler loop.
      //will just keep running until the current event is nonexistent.
      //at which point, it will return the current state of the connection
      EStateID RunEventLoop(ULEvent& inEvent);

    public:
      ULConnectionManager();
      ~ULConnectionManager();

      //returns true if a connection of the given AETitle (ie, 'this' program)
      //is able to connect to the given AETitle and Port in a certain amount of time
      bool EstablishConnection(const std::string& inAETitle, const std::string& inConnectAETitle, 
        const std::string& inComputerName, const long& inIPAddress, 
        const unsigned short& inConnectPort, const double& inTimeout);

      //allows for a connection to be broken, but waits for an acknowledgement
      //of the breaking for a certain amount of time.  Returns true of the
      //other side acknowledges the break
      bool BreakConnection(const double& inTimeout);

      //severs the connection, if it's open, without waiting for any kind of response.
      //typically done if the program is going down. 
      void BreakConnectionNow();

      //This function will send a given piece of data 
      //across the network connection.  It will return true if the 
      //sending worked, false otherwise.
      //note that sending is asynchronous; as such, there's
      //also a 'receive' option, but that requires a callback function.
      bool SendData();



    };
  }
}