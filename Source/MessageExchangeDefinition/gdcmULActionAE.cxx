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
namespace network
{

//Issue TRANSPORT CONNECT request primitive to local transport service.
EStateID ULActionAE1::PerformAction(ULEvent& inEvent, ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  //opening a local socket
  outWaitingForEvent = false;
  if (!inConnection.InitializeConnection())
    {
    outRaisedEvent = eEventDoesNotExist;
    return eSta1Idle;
    }
  else
    {
    outRaisedEvent = eTransportConnConfirmLocal;
    }
  return eSta4LocalAssocDone;
}

//Send A-ASSOCIATE-RQ-PDU
EStateID ULActionAE2::PerformAction(ULEvent& inEvent, ULConnection& inConnection,
  bool& outWaitingForEvent, EEventID& outRaisedEvent)
{
  AAssociateRQPDU thePDU;

  thePDU.SetCallingAETitle( inConnection.GetConnectionInfo().GetCallingAETitle() );
  thePDU.SetCalledAETitle( inConnection.GetConnectionInfo().GetCalledAETitle() );

  //the presentation context is now defined when the connection is first
  //desired to be established. The connection proposes these different
  //presentation contexts. ideally, we could refine it further to a particular
  //presentation context, but if the server supports many and we support many,
  //then an arbitrary decision can be made.
  std::vector<PresentationContext> const & thePCS =
    inConnection.GetPresentationContexts();

  std::vector<PresentationContext>::const_iterator itor;
  for (itor = thePCS.begin(); itor < thePCS.end(); itor++)
    {
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
  //we have one server type, a store scp started on a cmove
  //so, it's defined as acceptable.
  bool acceptable = true;//for now, always accept
  if (inEvent.GetPDUs().empty()){
    acceptable = false; //can't accept an empty set of pdus.
    //also, requrie little endian, not sure how to set that, but it should be here.
  }
  AAssociateRQPDU* rqpdu;
  if (acceptable){
    rqpdu = dynamic_cast<AAssociateRQPDU*>(inEvent.GetPDUs()[0]);
    if (rqpdu == NULL){
      acceptable = false;
    }
  }
  if (acceptable){
    outWaitingForEvent = false;//not waiting, now want to get the
    //sending of data underway.  Have to get info now
    outRaisedEvent = eAASSOCIATEresponseAccept;

    TransferSyntaxSub ts1;
    ts1.SetNameFromUID( UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );

    AAssociateACPDU acpdu;

    for( unsigned int index = 0; index < rqpdu->GetNumberOfPresentationContext(); index++ ){
      // FIXME / HARDCODED We only ever accept Little Endian
      // FIXME we should check :
      // rqpdu.GetAbstractSyntax() contains LittleENdian
      PresentationContextAC pcac1;
      PresentationContext const &pc = rqpdu->GetPresentationContext(index);
      //add the presentation context back into the connection,
      //so later functions will know what's allowed on this connection
      inConnection.AddAcceptedPresentationContext(pc);

      uint8_t id = pc.GetPresentationContextID();

      std::vector<TransferSyntaxSub> tsSet = pc.GetTransferSyntaxes();
      std::vector<TransferSyntaxSub>::iterator tsitor;
      bool hasLittleEndian = false;
      for (tsitor = tsSet.begin(); tsitor < tsSet.end(); tsitor++){
        if (strcmp(tsitor->GetName(), ts1.GetName())==0){
          hasLittleEndian = true;
        }
      }
      if (!hasLittleEndian) continue; //don't add this presentation context, because
      //the client doesn't know how to handle it.

      pcac1.SetPresentationContextID( id );
      pcac1.SetTransferSyntax( ts1 );
      acpdu.AddPresentationContextAC( pcac1 );
    }

    // Init AE-Titles:
    rqpdu->InitFromRQ( acpdu );

    acpdu.Write( *inConnection.GetProtocol() );
    inConnection.GetProtocol()->flush();

    return eSta3WaitLocalAssoc;
  } else {

    outWaitingForEvent = false;
    outRaisedEvent = eAASSOCIATEresponseReject;
    AAssociateRJPDU thePDU;//for now, use Matheiu's default values
    thePDU.Write(*inConnection.GetProtocol());
    inConnection.GetProtocol()->flush();
    inConnection.GetTimer().Stop();
    return eSta13AwaitingClose;
  }

}

//Send A-ASSOCIATE-AC PDU
EStateID ULActionAE7::PerformAction(ULEvent& inEvent, ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& outRaisedEvent){


// FIXME  MM
//  AAssociateACPDU thePDU;//for now, use Matheiu's default values
//  thePDU.Write(*inConnection.GetProtocol());
// FIXME

  outWaitingForEvent = true;
  outRaisedEvent = eEventDoesNotExist;
  return eSta6TransferReady;
}

//Send A-ASSOCIATE-RJ PDU and start ARTIM timer
EStateID ULActionAE8::PerformAction(ULEvent& inEvent, ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AAssociateRJPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();
  outWaitingForEvent = false;
  outRaisedEvent = eAASSOCIATEresponseReject;

  return eSta13AwaitingClose;
}

} // end namespace network
} // end namespace gdcm
