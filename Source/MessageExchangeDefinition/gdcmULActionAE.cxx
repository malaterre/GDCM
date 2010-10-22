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
/*

This file contains the implementation for the classes for the AE Actions,
Association Establishment Related Actions (Table 9-6 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.

*/

#include "gdcmULActionAE.h"
#include "gdcmARTIMTimer.h"
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmAAssociateRJPDU.h"

#include <socket++/echo.h>//for setting up the local socket

namespace gdcm
{
namespace network{  //gonna have to collapse these namespaces at some point

//Issue TRANSPORT CONNECT request primitive to local transport service.
EStateID ULActionAE1::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  //opening a local socket
  try{
    echo* p = new echo(protocol::tcp);
    if (inConnection.GetConnectionInfo().GetCalledIPPort() == 0){
      if (!inConnection.GetConnectionInfo().GetCalledComputerName().empty())
        (*p)->connect(inConnection.GetConnectionInfo().GetCalledComputerName().c_str());
      else 
        (*p)->connect(inConnection.GetConnectionInfo().GetCalledIPAddress());
    }
    else {
      if (!inConnection.GetConnectionInfo().GetCalledComputerName().empty())
        (*p)->connect(inConnection.GetConnectionInfo().GetCalledComputerName().c_str(), 
          inConnection.GetConnectionInfo().GetCalledIPPort());
    }
    //make sure to convert timeouts to platform appropriate values.
    (*p)->recvtimeout((int)inConnection.GetTimer().GetTimeout());
    (*p)->sendtimeout((int)inConnection.GetTimer().GetTimeout());
    inConnection.SetProtocol(p);
  } catch (...){//unable to establish connection, so break off.
     outWaitingForEvent = false;
     outRaisedEvent = eEventDoesNotExist;
     return eSta1Idle;
  }

  outWaitingForEvent = false;
  outRaisedEvent = eTransportConnConfirmLocal;

  return eSta4LocalAssocDone;
}

//Send A-ASSOCIATE-RQ-PDU
EStateID ULActionAE2::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){
  AAssociateRQPDU thePDU;//for now, use Matheiu's default values

  thePDU.SetCallingAETitle( inConnection.GetConnectionInfo().GetCallingAETitle() );
  thePDU.SetCalledAETitle( inConnection.GetConnectionInfo().GetCalledAETitle() );

  //the presentation context is now defined when the connection is first
  //desired to be established.  The connection proposes these different presentation contexts.
  //ideally, we could refine it further to a particular presentation context, but
  //if the server supports many and we support many, then an arbitrary decision can be made.
  std::vector<PresentationContext> thePCS = inConnection.GetPresentationContexts();

  std::vector<PresentationContext>::const_iterator itor;
  for (itor = thePCS.begin(); itor < thePCS.end(); itor++){
    thePDU.AddPresentationContext(*itor);
  }

  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();

  outWaitingForEvent = true;
  outRaisedEvent = eEventDoesNotExist;

  return eSta5WaitRemoteAssoc;
}

//Issue A-ASSOCIATE confirmation (accept) primitive
// NOTE: A-ASSOCIATE is NOT A-ASSOCIATE-AC
// PS 3.7 / Annex D for A-ASSOCIATE definition
EStateID ULActionAE3::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){
  outWaitingForEvent = false;
  outRaisedEvent = eEventDoesNotExist;//no event is raised,
  //wait for the user to try to send some data.
  return eSta6TransferReady;
}

//Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection
EStateID ULActionAE4::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){
          
  outWaitingForEvent = false;
  outRaisedEvent = eASSOCIATE_RJPDUreceived;
  return eSta1Idle;
}

//Issue Transport connection response primitive, start ARTIM timer
EStateID ULActionAE5::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  //issue response primitive; have to set that up
  inConnection.GetTimer().Start();

  outWaitingForEvent = false;
  outRaisedEvent = eTransportConnConfirmLocal;
  return eSta2Open;
}

//Stop ARTIM timer and if A-ASSOCIATE-RQ acceptable by service-provider:
//- issue A-ASSOCIATE indication primitive
//Next state: eSta3WaitLocalAssoc
//otherwise:
//- issue A-ASSOCIATE-RJ-PDU and start ARTIM timer
//Next state: eSta13AwaitingClose
EStateID ULActionAE6::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  inConnection.GetTimer().Stop();

  //have to determine 'acceptability'
  //this is more server side than client, so it's a bit empty now
  bool acceptable = true;
  if (acceptable){
    
    outWaitingForEvent = false;
    outRaisedEvent = eAASSOCIATEresponseAccept;

    return eSta3WaitLocalAssoc;
  } else {

    outWaitingForEvent = false;
    outRaisedEvent = eAASSOCIATEresponseReject;
    AAssociateRJPDU thePDU;//for now, use Matheiu's default values
    thePDU.Write(*inConnection.GetProtocol());
    inConnection.GetTimer().Stop();
    return eSta13AwaitingClose;
  }

}

//Send A-ASSOCIATE-AC PDU
EStateID ULActionAE7::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AAssociateACPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  
  outWaitingForEvent = true;
  outRaisedEvent = eEventDoesNotExist;
  return eSta6TransferReady;
}

//Send A-ASSOCIATE-RJ PDU and start ARTIM timer
EStateID ULActionAE8::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AAssociateACPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();
  outWaitingForEvent = false;
  outRaisedEvent = eAASSOCIATEresponseReject;

  return eSta13AwaitingClose;
}

   }
} 
