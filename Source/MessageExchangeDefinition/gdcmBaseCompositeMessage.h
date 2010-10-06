/*
The Composite events described in section 3.7-2009 of the DICOM standard all use their own messages.
These messages are constructed using Presentation Data Values, from section 3.8-2009 of the standard,
and then fill in appropriate values in their datasets.  

So, for the five composites:
cecho
cfind
cmove
cget
cstore
there are a series of messages.  However, all of these messages are obtained as part of a PDataPDU,
and all have to be placed there.  Therefore, since they all have shared functionality and construction
tropes, that will be put into a base class.  Further, the base class will be then returned by the
factory class, gdcmCompositePDUFactory.

This is an abstract class.  It cannot be instantiated on its own.
*/
#ifndef BASECOMPOSITEMESSSAGE_H
#define BASECOMPOSITEMESSSAGE_H
#include "gdcmDataSet.h"
#include "gdcmPresentationDataValue.h"
#include <vector>

namespace gdcm{
  namespace network{
    class BaseCompositeMessage{
    public:
      //construct the appropriate pdv and dataset for this message
      //for instance, setting tag 0x0,0x100 to the appropriate value
      //the pdv, as described in Annex E of 3.8-2009, is the first byte
      //of the message (the MessageHeader), and then the subsequent dataset
      //that describes the operation.
      virtual std::vector<PresentationDataValue> ConstructPDV(DataSet* inDataSet) = 0;

    };
  }
}
#endif //BASECOMPOSITEMESSSAGE_H