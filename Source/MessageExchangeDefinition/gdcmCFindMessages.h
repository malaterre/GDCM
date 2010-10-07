/*
this file defines the messages for the cfind action
5 oct 2010 mmr
*/

#include "gdcmBaseCompositeMessage.h"

namespace gdcm{
  namespace network{
    class CFindRQ : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };

    class CFindRSP : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };

    class CFindCancelRq : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };
  }
}
