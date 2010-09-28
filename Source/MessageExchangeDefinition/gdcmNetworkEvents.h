/*
The NetworkEvents enumeration defines the inputs into the state of the network connection.

These inputs can come either from user input or input from other things on the socket, 
ie, responses from the peer or ARTIM timeouts.

Note that this enumeration is not 'power of two', like the states, because you can't have 
multiple simultaneous events.  Multiple state outputs in transition tables, however, is possible.

*/
#ifndef NETWORKEVENTS_H
#define NETWORKEVENTS_H

namespace gdcm {
  namespace network{
    typedef enum {
      eAASSOCIATERequestLocalUser = 0,
      eTransportConnConfirmLocal,
      eASSOCIATE_ACPDUreceived,
      eASSOCIATE_RJPDUreceived,
      eTransportConnIndicLocal,
      eAASSOCIATE_RQPDUreceived,
      eAASSOCIATEresponseAccept,
      eAASSOCIATEresponseReject,
      ePDATArequest,
      ePDATATFPDU,
      eARELEASERequest,
      eARELEASE_RQPDUReceivedOpen,
      eARELEASE_RQPDUReceived,
      eARELEASEResponse,
      eAABORTRequest,
      eAABORTPDUReceivedOpen,
      eTransportConnectionClosed,
      eARTIMTimerExpired,
      eUnrecognizedPDUReceived,
      eEventDoesNotExist
    } EEventID;

    const int cMaxEventID = eEventDoesNotExist;
  }
}

#endif //NETWORKEVENTS_H
