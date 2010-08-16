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
#include "gdcmAAssociateRQPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
/*
9.3.2 A-ASSOCIATE-RQ PDU STRUCTURE
An A-ASSOCIATE-RQ PDU shall be made of a sequence of mandatory fields followed by a variable
length field. Table 9-11 shows the sequence of the mandatory fields.
The variable field shall consist of one Application Context Item, one or more Presentation Context Items,
and one User Information Item. Sub-Items shall exist for the Presentation Context and User Information
Items.
*/
namespace network
{
const uint8_t AAssociateRQPDU::ItemType = 0x1; // PDUType ?
const uint8_t AAssociateRQPDU::Reserved2 = 0x0;
const uint16_t AAssociateRQPDU::ProtocolVersion = 0x100; // big - endian ?
const uint16_t AAssociateRQPDU::Reserved9_10 = 0x0;
const uint8_t AAssociateRQPDU::Reserved43_74[32] = {};

AAssociateRQPDU::AAssociateRQPDU()
{
  memset(CalledAETitle, ' ', sizeof(CalledAETitle));
  const char called[] = "ANY-SCP";
  strncpy(CalledAETitle, called, strlen(called) );
  memset(CallingAETitle, ' ', sizeof(CallingAETitle));
  const char calling[] = "ECHOSCU";
  strncpy(CallingAETitle, calling, strlen(calling) );

  PresContext.push_back( PresentationContext() );

  ItemLength = Size() - 6;
  assert( (ItemLength + 4 + 1 + 1) == Size() );
}

std::istream &AAssociateRQPDU::Read(std::istream &is)
{
  assert( 0 );
  return is;
}

const std::ostream &AAssociateRQPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&ProtocolVersion, sizeof(ProtocolVersion) );
  os.write( (char*)&Reserved9_10, sizeof(Reserved9_10) );
  os.write( CalledAETitle, 16 );
  os.write( CallingAETitle, 16 );
  os.write( (char*)&Reserved43_74, sizeof(Reserved43_74) );
  AppContext.Write(os);
  std::vector<PresentationContext>::const_iterator it = PresContext.begin();
  for( ; it != PresContext.end(); ++it)
    {
    it->Write(os);
    }
  UserInfo.Write(os);

  return os;
}

size_t AAssociateRQPDU::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(ProtocolVersion);
  ret += sizeof(Reserved9_10);
  ret += sizeof(CalledAETitle);
  ret += sizeof(CallingAETitle);
  ret += sizeof(Reserved43_74);
  ret += AppContext.Size();
  std::vector<PresentationContext>::const_iterator it = PresContext.begin();
  for( ; it != PresContext.end(); ++it)
    {
    ret += it->Size();
    }
  ret += UserInfo.Size();

  return ret;
}

} // end namespace network
} // end namespace gdcm
