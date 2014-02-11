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
#ifndef GDCMNORMALIZEDMESSAGEFACTORY_H
#define GDCMNORMALIZEDMESSAGEFACTORY_H

#include "gdcmPresentationDataValue.h"
#include "gdcmULConnection.h"

namespace gdcm {
  class BaseQuery;
  class File;
  namespace network {
    class BasePDU;

class NormalizedMessageFactory
{
    public:
      static  std::vector<PresentationDataValue> ConstructNEventReport	(const ULConnection& inConnection, const BaseQuery* inQuery);
      static  std::vector<PresentationDataValue> ConstructNGet			(const ULConnection& inConnection, const BaseQuery* inQuery);
      static  std::vector<PresentationDataValue> ConstructNSet			(const ULConnection& inConnection, const BaseQuery* inQuery);
      static  std::vector<PresentationDataValue> ConstructNAction		(const ULConnection& inConnection, const BaseQuery* inQuery);
      static  std::vector<PresentationDataValue> ConstructNCreate		(const ULConnection& inConnection, const BaseQuery* inQuery);
      static  std::vector<PresentationDataValue> ConstructNDelete		(const ULConnection& inConnection, const BaseQuery* inQuery);


    };
  }
}

#endif // GDCMNORMALIZEDMESSAGEFACTORY_H
