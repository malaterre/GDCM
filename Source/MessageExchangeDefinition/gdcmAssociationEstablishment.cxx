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
#include "gdcmAssociationEstablishment.h"
#include "gdcmSwapper.h"
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmAAssociateRJPDU.h"
#include "gdcmPDataTFPDU.h"
#include "gdcmAReleaseRQPDU.h"

namespace gdcm
{
namespace network
{

/*
Table 9-2
ASSOCIATION ESTABLISHMENT
State Definition
Sta 2 Transport connection open (Awaiting A-ASSOCIATE-RQ PDU)
Sta 3 Awaiting local A-ASSOCIATE response primitive (from local user)
Sta 4 Awaiting transport connection opening to complete (from local transport service)
Sta 5 Awaiting A-ASSOCIATE-AC or A-ASSOCIATE-RJ PDU
*/

AssociationEstablishment::AssociationEstablishment()
{
}

std::iostream &AssociationEstablishment::Run(std::iostream &ios)
{
  std::istream &is = ios;
  std::ostream &os = ios;

  gdcm::network::AAssociateRQPDU cecho;
  //cecho.SetCallingAETitle( "ECHOSCU" );
  cecho.SetCallingAETitle( "ACME1" );
  //cecho.SetCallingAETitle( "MI2B2" );
  //cecho.SetCalledAETitle( "ACME_STORE" );
  //cecho.SetCalledAETitle( "MI2B2" );
  cecho.SetCalledAETitle( "A" );

  gdcm::network::PresentationContext pc;
  gdcm::network::AbstractSyntax as;
  as.SetNameFromUID( gdcm::UIDs::VerificationSOPClass );
  pc.SetAbstractSyntax( as );

  gdcm::network::TransferSyntax_ ts;
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  pc.AddTransferSyntax( ts );

  cecho.AddPresentationContext( pc );
  cecho.Write(ios);
  ios.flush();

  uint8_t itemtype = 0x0;
  is.read( (char*)&itemtype, 1 );
  switch ( itemtype )
    {
  case 0x2:
      {
      gdcm::network::AAssociateACPDU acpdu;
      acpdu.Read( ios );
      acpdu.Print( std::cout );
      }
    break;
  case 0x3:
      {
      gdcm::network::AAssociateRJPDU rjpdu;
      rjpdu.Read( ios );
      rjpdu.Print( std::cout );
      return ios; // idle 
      }
    break;
  default:
    assert( 0 );
    throw "Unimplemented";
    }

  //gdcm::network::PDataTFPDU pdata;
  //gdcm::network::PresentationDataValue pdv;
  //pdata.AddPresentationDataValue( pdv );
  //pdata.Write( ios );
  //ios.flush();

  //// listen back
  //gdcm::network::PDataTFPDU pdata2;
  //pdata2.Read( ios );

  //// Print output DataSet:
  //pdata2.GetPresentationDataValue(0).GetDataSet().Print( std::cout );

  //// send release:
  //gdcm::network::AReleaseRQPDU rel;
  //rel.Write( ios );

  return ios;
}

} // end namespace network
} // end namespace gdcm
