#ifndef CMOVEMESSAGES_H
#define CMOVEMESSAGES_H
/*
this file defines the messages for the cfind action
5 oct 2010 mmr
*/

#include "gdcmBaseCompositeMessage.h"

namespace gdcm{
  namespace network{
    class CMoveRQ : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };

    class CMoveRSP : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };

    class CMoveCancelRq : public BaseCompositeMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet);
    };
  }
}
#endif
