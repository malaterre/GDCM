/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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
  cecho.SetCalledAETitle( "MI2B2" );

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
    }

  gdcm::network::PDataTFPDU pdata;
  gdcm::network::PresentationDataValue pdv;
  pdata.AddPresentationDataValue( pdv );
  pdata.Write( ios );
  ios.flush();

  // listen back
  gdcm::network::PDataTFPDU pdata2;
  pdata2.Read( ios );

  // Print output DataSet:
  pdata2.GetPresentationDataValue(0).GetDataSet().Print( std::cout );

  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( ios );

  return ios;
}

} // end namespace network
} // end namespace gdcm
