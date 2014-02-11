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

#include "gdcmNEventReportMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmPresentationContextRQ.h"
#include "gdcmCommandDataSet.h"
#include "gdcmULConnection.h"

namespace gdcm{
  namespace network{

    std::vector<PresentationDataValue> NEventReportRQ::ConstructPDV(
      const ULConnection &inConnection, const BaseQuery* inQuery)
    {
      std::vector<PresentationDataValue> thePDV;
      assert( 0 && "TODO" );
      return thePDV;
      //std::vector<PresentationDataValue> thePDVs;
      // PresentationDataValue thePDV;

      // PresentationContextRQ pc( inQuery->GetAbstractSyntaxUID() );
      // uint8_t presidx = inConnection.GetPresentationContextIDFromPresentationContext(pc);
      // if( !presidx )
      //   {
      //   // try harder:
      //   PresentationContextRQ pc2( inQuery->GetAbstractSyntaxUID(), UIDs::ExplicitVRLittleEndian);
      //   presidx = inConnection.GetPresentationContextIDFromPresentationContext(pc2);
      //   if( !presidx )
      //     {
      //     gdcmErrorMacro( "Could not find Pres Cont ID" );
      //     return thePDVs;
      //     }
      //   }
      // thePDV.SetPresentationContextID( presidx );

      // thePDV.SetCommand(true);
      // thePDV.SetLastFragment(true);
      // //ignore incoming data set, make your own

      // CommandDataSet ds;
      // ds.Insert( pc.GetAbstractSyntax().GetAsDataElement() );
      // {
      // Attribute<0x0,0x100> at = { 0x0100 };
      // ds.Insert( at.GetAsDataElement() );
      // }
      // {
      // Attribute<0x0,0x110> at = { 1 };
      // ds.Insert( at.GetAsDataElement() );
      // }
      // {
      // Attribute<0x0,0x800> at = { 1 };
      // ds.Insert( at.GetAsDataElement() );
      // }
      // {
      // Attribute<0x0,0x1002> at = { 1 };
      // ds.Insert( at.GetAsDataElement() );
      // }
      // {
      // Attribute<0x0,0x1002> at = { 1 };
      // ds.Insert( at.GetAsDataElement() );
      // }
      // {
      // Attribute<0x0,0x0> at = { 0 };
      // unsigned int glen = ds.GetLength<ImplicitDataElement>();
      // assert( (glen % 2) == 0 );
      // at.SetValue( glen );
      // ds.Insert( at.GetAsDataElement() );
      // }

      // thePDV.SetDataSet(ds);
      // thePDVs.push_back(thePDV);
      // thePDV.SetDataSet(inQuery->GetQueryDataSet());
      // thePDV.SetMessageHeader( 2 );
      // thePDVs.push_back(thePDV);
      // return thePDVs;

    }

    std::vector<PresentationDataValue>  
      NEventReportRSP::ConstructPDVByDataSet(const DataSet* inDataSet){
        std::vector<PresentationDataValue> thePDV;
        (void)inDataSet;
        assert( 0 && "TODO" );
        return thePDV;
    }

  }//namespace network
}//namespace gdcm
