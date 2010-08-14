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
#include "gdcmPresentationContext.h"
#include "gdcmUIDs.h"

namespace gdcm
{
namespace network
{
const uint8_t PresentationContext::ItemType = 0x20;
const uint8_t PresentationContext::Reserved2 = 0x00;
const uint8_t PresentationContext::Reserved6 = 0x00;
const uint8_t PresentationContext::Reserved7 = 0x00;
const uint8_t PresentationContext::Reserved8 = 0x00;

PresentationContext::PresentationContext()
{
  ItemLength = 0;
  ID = 0;
  TransferSyntax_ t1;
  t1.SetFromUID( gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass ) );
  //TransferSyntaxes.push_back( t1 );

  TransferSyntax_ t2;
  t2.SetFromUID( gdcm::UIDs::GetUIDString( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM ) );
  TransferSyntaxes.push_back( t2 );

  TransferSyntax_ t3;
  t3.SetFromUID( "1.2.2.276.0.7230010.3.0.3.5.5" );
  //TransferSyntaxes.push_back( t3 );
}

const std::ostream &PresentationContext::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( (char*)&ID, sizeof(ID) );
  os.write( (char*)&Reserved6, sizeof(Reserved6) );
  os.write( (char*)&Reserved7, sizeof(Reserved7) );
  os.write( (char*)&Reserved8, sizeof(Reserved8) );
  SubItems.Write(os);
  std::vector<TransferSyntax_>::const_iterator it = TransferSyntaxes.begin();
  for( ; it != TransferSyntaxes.end(); ++it )
    {
    it->Write( os );
    }

  return os;
}

} // end namespace network
} // end namespace gdcm
