/*
The NetworkEvents enumeration defines the inputs into the state of the network connection.

These inputs can come either from user input or input from other things on the socket, 
ie, responses from the peer or ARTIM timeouts.

*/


namespace gdcm {
  namespace primitives{
    enum ENetworkEvents {
      eAASSOCIATERequestLocalUser,
      eTransportConnConfirmLocal,
      eASSOCIATE-ACPDUreceived,
      eASSOCIATE-RJPDUreceived,
      eTransportConnIndicLocal,
      eAASSOCIATE-RQPDUreceived,
      eAASSOCIATEresponseAccept,
      eAASSOCIATEresponseReject,
      ePDATArequest,
      ePDATATFPDU,

    }
  }
}