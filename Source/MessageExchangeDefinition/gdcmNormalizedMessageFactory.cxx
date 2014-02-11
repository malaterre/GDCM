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
Normalized DICOM services (C-Echo, C-Find, C-Get, C-Move, and C-Store).  It will also handle
parsing the incoming data to determine which of the NormalizedPDUs the incoming data is, and
so therefore allowing the scu to determine what to do with incoming data (if acting as
a storescp server, for instance).

name and date: 4 oct 2010 mmr
*/

#include "gdcmNormalizedMessageFactory.h"
#include "gdcmBaseQuery.h"

#include "gdcmNActionMessages.h"
#include "gdcmNCreateMessages.h"
#include "gdcmNDeleteMessages.h"
#include "gdcmNEventReportMessages.h"
#include "gdcmNGetMessages.h"
#include "gdcmNSetMessages.h"

namespace gdcm {
  namespace network {
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNEventReport	(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NEventReportRQ theNEventReportRQ;
      return theNEventReportRQ.ConstructPDV(inConnection, inQuery);
    }
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNGet			(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NGetRQ theNGetRQ;
      return theNGetRQ.ConstructPDV(inConnection, inQuery);
    }
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNSet			(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NSetRQ theNSetRQ;
      return theNSetRQ.ConstructPDV(inConnection, inQuery);
    }
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNAction		(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NActionRQ theNActionRQ;
      return theNActionRQ.ConstructPDV(inConnection, inQuery);
    }
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNCreate		(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NCreateRQ theNCreate;
      return theNCreate.ConstructPDV(inConnection, inQuery);
    }
    std::vector<PresentationDataValue> NormalizedMessageFactory::ConstructNDelete		(const ULConnection& inConnection, const BaseQuery* inQuery)
    {
      NDeleteRQ theNDeleteRQ;
      return theNDeleteRQ.ConstructPDV(inConnection, inQuery);
    }
  }
}
