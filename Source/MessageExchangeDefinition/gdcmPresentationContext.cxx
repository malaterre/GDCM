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
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t PresentationContext::ItemType = 0x20;
const uint8_t PresentationContext::Reserved2 = 0x00;
const uint8_t PresentationContext::Reserved6 = 0x00;
const uint8_t PresentationContext::Reserved7 = 0x00;
//const uint8_t PresentationContext::Reserved7 = 0xff; // DCMTK ??
const uint8_t PresentationContext::Reserved8 = 0x00;

PresentationContext::PresentationContext()
{
  ID = 0x01;

  TransferSyntax_ t;
  t.SetFromUID( gdcm::UIDs::GetUIDString( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM ) );
  TransferSyntaxes.push_back( t );

  ItemLength = Size() - 4;
  assert( ItemLength + 4 == Size() );
}

std::istream &PresentationContext::Read(std::istream &is)
{
  return is;
}

const std::ostream &PresentationContext::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

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

size_t PresentationContext::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(ID);
  ret += sizeof(Reserved6);
  ret += sizeof(Reserved7);
  ret += sizeof(Reserved8);
  ret += SubItems.Size();
  std::vector<TransferSyntax_>::const_iterator it = TransferSyntaxes.begin();
  for( ; it != TransferSyntaxes.end(); ++it )
    {
    ret += it->Size();
    }

  return ret;
}

} // end namespace network
} // end namespace gdcm
