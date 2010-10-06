/*
this file defines the messages for the cecho action
5 oct 2010 mmr
*/

#include "gdcmBaseCompositeMessage.h"

namespace gdcm{
  namespace network{
    class CEchoRQ : public BaseCompositeMessage {
    public:
      PresentationDataValue ConstructPDV(DataSet* inDataSet);
    };

    class CEchoRSP : public BaseCompositeMessage {
    public:
      PresentationDataValue ConstructPDV(DataSet* inDataSet);
    };
  }
}
