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
this file defines the messages for the cecho action
5 oct 2010 mmr
*/

#include "gdcmNDeleteMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmPresentationContextRQ.h"
#include "gdcmCommandDataSet.h"
#include "gdcmULConnection.h"

namespace gdcm{
  namespace network{

    std::vector<PresentationDataValue> NDeleteRQ::ConstructPDV(
      const ULConnection &inConnection, const BaseQuery* inQuery)
    {
      std::vector<PresentationDataValue> thePDV;
      assert( 0 && "TODO" );
      return thePDV;
    }

    std::vector<PresentationDataValue>  
      NDeleteRSP::ConstructPDVByDataSet(const DataSet* inDataSet){
        std::vector<PresentationDataValue> thePDV;
        (void)inDataSet;
        assert( 0 && "TODO" );
        return thePDV;
    }

  }//namespace network
}//namespace gdcm
