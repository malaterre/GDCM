/*
This class constructs PDataPDUs, but that have been specifically constructed for the
composite DICOM services (C-Echo, C-Find, C-Get, C-Move, and C-Store).  It will also handle
parsing the incoming data to determine which of the CompositePDUs the incoming data is, and
so therefore allowing the scu to determine what to do with incoming data (if acting as
a storescp server, for instance).

name and date: 4 oct 2010 mmr
*/

#include "gdcmCompositeMessageFactory.h"
#include "gdcmCEchoMessages.h"
#include "gdcmCStoreMessages.h"
#include "gdcmCFindMessages.h"
#include "gdcmCMoveMessages.h"

namespace gdcm {
namespace network {
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCEchoRQ(const ULConnection& inConnection){
    CEchoRQ theEchoRQ;
    return theEchoRQ.ConstructPDV(NULL);
  }

  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCStoreRQ(const ULConnection& inConnection, DataSet *inDataSet) {
    CStoreRQ theStoreRQ;
    return theStoreRQ.ConstructPDV(inDataSet);
  }
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCFindRQ(const ULConnection& inConnection, DataSet *inDataSet) {
    CFindRQ theFindRQ;
    return theFindRQ.ConstructPDV(inDataSet);
  }
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCMoveRQ(const ULConnection& inConnection, DataSet *inDataSet) {
    CMoveRQ theMoveRQ;
    return theMoveRQ.ConstructPDV(inDataSet);
  }
}
}
