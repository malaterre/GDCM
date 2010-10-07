/*
This class constructs PDataPDUs, but that have been specifically constructed for the
composite DICOM services (C-Echo, C-Find, C-Get, C-Move, and C-Store).  It will also handle
parsing the incoming data to determine which of the CompositePDUs the incoming data is, and
so therefore allowing the scu to determine what to do with incoming data (if acting as
a storescp server, for instance).

name and date: 4 oct 2010 mmr
*/

#include "gdcmDataSet.h"
#include "gdcmPresentationDataValue.h"
#include "gdcmULConnection.h"

namespace gdcm {
  namespace network {
    class CompositeMessageFactory {
    public:
      //the echo request only needs a properly constructed PDV.
      //find, move, etc, may need something more robust, but since those are 
      //easily placed into the appropriate pdatapdu in the pdufactory,
      //this approach without a base class (but done internally) is useful.
      static std::vector<PresentationDataValue> ConstructCEchoRQ(const ULConnection& inConnection);

      static std::vector<PresentationDataValue> ConstructCStoreRQ(const ULConnection& inConnection, DataSet *inDataSet);

  static  std::vector<PresentationDataValue> ConstructCFindRQ(const ULConnection& inConnection, DataSet *inDataSet);


    };
  }
}
