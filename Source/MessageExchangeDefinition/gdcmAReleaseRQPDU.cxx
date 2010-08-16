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
#include "gdcmAReleaseRQPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AReleaseRQPDU::ItemType = 0x5; // PDUType ?
const uint8_t AReleaseRQPDU::Reserved2 = 0x0;
const uint32_t AReleaseRQPDU::Reserved7_10 = 0x0;

AReleaseRQPDU::AReleaseRQPDU()
{
  ItemLength = 0; // PDU Length
}

std::istream &AReleaseRQPDU::Read(std::istream &is)
{
  return is;
}

const std::ostream &AReleaseRQPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&Reserved7_10, sizeof(Reserved7_10) );

  return os;
}

} // end namespace network
} // end namespace gdcm
