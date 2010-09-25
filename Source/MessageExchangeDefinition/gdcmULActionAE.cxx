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

using namespace gdcm::network; //gonna have to collapse these namespaces at some point

//Issue TRANSPORT CONNECT request primitive to local transport service.
EStateID ULActionAE1::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  //opening a local socket
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
  return eSta4LocalAssocDone;
}

//Send A-ASSOCIATE-RQ-PDU
EStateID ULActionAE2::PerformAction(ULEvent& inEvent, ULConnection& inConnection){
  AAssociateRQPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  return eSta5WaitRemoteAssoc;
}

//Issue A-ASSOCIATE confirmation (accept) primitive
EStateID ULActionAE3::PerformAction(ULEvent& inEvent, ULConnection& inConnection){
  AAssociateACPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());

  return eSta6TransferReady;
}

//Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection
EStateID ULActionAE4::PerformAction(ULEvent& inEvent, ULConnection& inConnection){
  AAssociateRJPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.SetProtocol(NULL);
  return eSta1Idle;
}

//Issue Transport connection response primitive, start ARTIM timer
EStateID ULActionAE5::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  //issue response primitive; have to set that up
  inConnection.GetTimer().Start();

  return eSta2Open;
}

//Stop ARTIM timer and if A-ASSOCIATE-RQ acceptable by service-provider:
//- issue A-ASSOCIATE indication primitive
//Next state: eSta3WaitLocalAssoc
//otherwise:
//- issue A-ASSOCIATE-RJ-PDU and start ARTIM timer
//Next state: eSta13AwaitingClose
EStateID ULActionAE6::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  inConnection.GetTimer().Stop();

  //have to determine 'acceptability'
  //this is more server side than client, so it's a bit empty now
  bool acceptable = true;
  if (acceptable){

    return eSta3WaitLocalAssoc;
  } else {

    AAssociateRJPDU thePDU;//for now, use Matheiu's default values
    thePDU.Write(*inConnection.GetProtocol());
    inConnection.GetTimer().Stop();
    return eSta13AwaitingClose;
  }

}

//Send A-ASSOCIATE-AC PDU
EStateID ULActionAE7::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  AAssociateACPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  return eSta6TransferReady;
}

//Send A-ASSOCIATE-RJ PDU and start ARTIM timer
EStateID ULActionAE8::PerformAction(ULEvent& inEvent, ULConnection& inConnection){

  AAssociateACPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();

  return eSta13AwaitingClose;
}

    