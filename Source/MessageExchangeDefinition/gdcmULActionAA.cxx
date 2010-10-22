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
This file contains the implementation for the classes for the AA Actions,
Association Abort Related Actions (Table 9-9 of ps 3.8-2009).

Since each class is essentially a placeholder for a function pointer, I'm breaking with having
each class have its own file for the sake of brevity of the number of files.

*/

#include "gdcmULActionAA.h"
#include "gdcmARTIMTimer.h"
#include "gdcmAAbortPDU.h"

using namespace gdcm::network;

//Send A-ABORT PDU (service-user source) and start (or restart if already started) ARTIM timer
EStateID ULActionAA1::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AAbortPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();

  return eSta13AwaitingClose;
}

//Stop ARTIM timer if running.  Close transport connection.
EStateID ULActionAA2::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){


  inConnection.GetTimer().Stop();
  inConnection.SetProtocol(NULL);

  return eSta1Idle;
}

//If (service-user initiated abort)
//- issue A-ABORT indication and close transport connection
//otherwise (service-provider initiated abort):
//- issue A-P-ABORT indication and close transport connection
EStateID ULActionAA3::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  return eSta1Idle;
}

//Issue A-P-ABORT indication primitive
EStateID ULActionAA4::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  return eSta1Idle;
}

//Stop ARTIM timer
EStateID ULActionAA5::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  inConnection.GetTimer().Stop();

  return eSta1Idle;
}

//Ignore PDU
EStateID ULActionAA6::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){
  //do nothing, I guess.
  return eSta13AwaitingClose;
}

//Send A-ABORT PDU
EStateID ULActionAA7::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){

  AAbortPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());

  return eSta13AwaitingClose;
}

//Send A-ABORT PDU (service-provider source), issue an A-P-ABORT indication, and start ARTIM timer
EStateID ULActionAA8::PerformAction(ULEvent& inEvent, ULConnection& inConnection, 
        bool& outWaitingForEvent, EEventID& outRaisedEvent){


  AAbortPDU thePDU;//for now, use Matheiu's default values
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetTimer().Start();

  return eSta13AwaitingClose;
}