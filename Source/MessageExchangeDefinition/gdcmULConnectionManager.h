/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef ULCONNECTIONMANAGER_H
#define ULCONNECTIONMANAGER_H

#include "gdcmULTransitionTable.h"
#include "gdcmULConnection.h"
#include "gdcmULConnectionInfo.h"
#include "gdcmPresentationDataValue.h"

namespace gdcm {
  class DataSet;


  namespace network {
  class BaseRootQuery;
    enum GDCM_EXPORT EConnectionType {
      eEcho,
      eFind,
      //eGet,      //our spec does not require C-GET support
      eMove,       //established by EstablishConnectionMove--DO NOT USE THIS DIRECTLY
      eStore
    };

/**
 * \brief ULConnectionManager
 * The ULConnectionManager performs actions on the ULConnection given inputs
 * from the user and from the state of what's going on around the connection
 * (ie, timeouts of the ARTIM timer, responses from the peer across the
 * connection, etc).
 *
 * Its inputs are ULEvents, and it performs ULActions.
 */
class GDCM_EXPORT ULConnectionManager
{
    private:
      ULConnection* mConnection;
      ULConnection* mSecondaryConnection;
      ULTransitionTable mTransitions;

      //no copying
      ULConnectionManager(const gdcm::network::ULConnectionManager& inCM){};

      //event handler loop.
      //will just keep running until the current event is nonexistent.
      //at which point, it will return the current state of the connection
      //if inWaitFirst == true, the loop awaits incoming data first, before sending data
      //back.  Can be used to implement scp functionality, in theory-- in this instance,
      //it's being used to instantiate a loop to get the results from a cmove.
      //requires that a secondary connection be started.
      EStateID RunEventLoop(ULEvent& inEvent, std::vector<DataSet>& outDataSet,
        const bool& inWaitFirst, ULConnection* inWhichConnection);

    public:
      ULConnectionManager();
      ~ULConnectionManager();

      /// returns true if a connection of the given AETitle (ie, 'this' program)
      /// is able to connect to the given AETitle and Port in a certain amount of
      /// time providing the connection type will establish the proper exchange
      /// syntax with a server; if a different functionality is required, a
      /// different connection should be established.
      /// returns false if the connection type is 'move'-- have to give a return
      /// port for move to work as specified.
      bool EstablishConnection(const std::string& inAETitle, const std::string& inConnectAETitle,
        const std::string& inComputerName, const long& inIPAddress,
        const unsigned short& inConnectPort, const double& inTimeout,
        const EConnectionType& inConnectionType, const gdcm::DataSet& inDS);

      /// returns true for above reasons, but contains the special 'move' port
      bool EstablishConnectionMove(const std::string& inAETitle, const std::string& inConnectAETitle,
        const std::string& inComputerName, const long& inIPAddress,
        const unsigned short& inConnectPort, const double& inTimeout,
        const unsigned short& inReturnPort, const gdcm::DataSet& inDS);


      //bool ReestablishConnection(const EConnectionType& inConnectionType,
      //  const gdcm::DataSet& inDS);

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
      //bool SendData();

      //send the Data PDU associated with Echo (ie, a default DataPDU)
      //this lets the user confirm that the connection is alive.
      //the user should look to cout to see the response of the echo command
      //returns the PresentationDataValue that was returned by the remote
      //host.  Note that the PDV can be uninitialized, which would indicate failure.
      std::vector<PresentationDataValue> SendEcho();

      // API will change...
      std::vector<DataSet> SendStore(DataSet *inDataSet);
      std::vector<DataSet> SendFind(BaseRootQuery* inRootQuery);
      std::vector<DataSet> SendMove(BaseRootQuery* inRootQuery);

    };
  }
}

#endif //ULCONNECTIONMANAGER_H
