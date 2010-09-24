/* 

The ULConnectionManager performs actions on the ULConnection given inputs from
the user and from the state of what's going on around the connection (ie,
timeouts of the ARTIM timer, responses from the peer across the connection, etc).

Its inputs are ULEvents, and it performs ULActions.

*/

#include "gdcmULConnection.h"
#include "gdcmARTIMTimer.h"
#include <vector>
#include "gdcmDataSet.h"


namespace gdcm {
  namespace primitives {
    class ULConnectionManager {
    private:
      ULConnection* mConnection;
      ARTIMTimer* mTimer;
      
      //no copying
      ULConnectionManager(const gdcm::primitives::ULConnectionManager& inCM){};

    public:
      ULConnectionManager();
      ~ULConnectionManager();

      //returns true if a connection of the given AETitle (ie, 'this' program)
      //is able to connect to the given AETitle and Port in a certain amount of time
      bool EstablishConnection(const std::string& inAETitle,
        const std::string& inConnectAETitle, 
        const std::vector<char>& inIPAddress,
        const short& inConnectPort,
        const double& inTimeout);

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
      bool SendData(DataSet& inDataSet);



    };
  }
}
