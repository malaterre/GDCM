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
#ifndef GDCMCNDELETEMESSAGES_H
#define GDCMCNDELETEMESSAGES_H

#include "gdcmBaseNormalizedMessage.h"

namespace gdcm{
  namespace network{

class ULConnection;

/**
 * \brief NDeleteRQ
 * this file defines the messages for the ndelete action
 */
class NDeleteRQ : public BaseNormalizedMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDV(const ULConnection &inConnection,
        const BaseQuery* inQuery);
    };

/**
 * \brief NDeleteRSP
 * this file defines the messages for the ndelete action
 */
    class NDeleteRSP : public BaseNormalizedMessage {
    public:
      std::vector<PresentationDataValue> ConstructPDVByDataSet(const DataSet* inDataSet);
    };
  }
}
#endif // GDCMCNDELETEMESSAGES_H
