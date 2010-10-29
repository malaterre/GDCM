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
#include "gdcmBaseRootQuery.h"

namespace gdcm {
namespace network {
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCEchoRQ(){
    CEchoRQ theEchoRQ;
    return theEchoRQ.ConstructPDV(NULL);
  }

  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCStoreRQ(DataSet *inDataSet) {
    CStoreRQ theStoreRQ;
    return theStoreRQ.ConstructPDV(inDataSet);
  }
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCStoreRSP(DataSet *inDataSet, BasePDU* inPDU) {
    CStoreRSP theStoreRSP;
    return theStoreRSP.ConstructPDV(inDataSet, inPDU);
  }
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCFindRQ(const ULConnection& inConnection, BaseRootQuery* inRootQuery) {
    CFindRQ theFindRQ;
    return theFindRQ.ConstructPDV(inRootQuery);
  }
  std::vector<PresentationDataValue> CompositeMessageFactory::ConstructCMoveRQ(const ULConnection& inConnection, BaseRootQuery* inRootQuery) {
    CMoveRQ theMoveRQ;
    return theMoveRQ.ConstructPDV(inConnection, inRootQuery);
  }
}
}
