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
file name: gdcmQueryFactory.h
contains: a class to produce a query based off of user-entered information
name and date: 18 oct 2010 mmr

Essentially, this class is used to construct a query based off of user input (typically
from the command line; if in code directly, the query itself could just be instantiated)

In theory, could also be used as the interface to validate incoming datasets as belonging
to a particular query style
*/

#include "gdcmBaseRootQuery.h"

namespace gdcm{
  namespace network{
    class GDCM_EXPORT QueryFactory {
    public:
      static BaseRootQuery* ProduceQuery(const ERootType &inRootType);
    };
  }
}
