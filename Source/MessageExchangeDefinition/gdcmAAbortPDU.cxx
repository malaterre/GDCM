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
#include "gdcmAAbortPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AAbortPDU::ItemType = 0x7; // PDUType ?
const uint8_t AAbortPDU::Reserved2 = 0x0;
const uint8_t AAbortPDU::Reserved7 = 0x0;
const uint8_t AAbortPDU::Reserved8 = 0x0;

AAbortPDU::AAbortPDU()
{
  ItemLength = 0;
  Source = 0;
  Reason = 0;

  ItemLength = Size() - 6;
  assert( (ItemLength + 4 + 1 + 1) == Size() );
}

std::istream &AAbortPDU::Read(std::istream &is)
{
  uint8_t itemtype = 0;
  is.read( (char*)&itemtype, sizeof(ItemType) );
  assert( itemtype == ItemType );
  uint8_t reserved2 = 0;
  is.read( (char*)&reserved2, sizeof(Reserved2) );
  uint32_t itemlength = ItemLength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  uint8_t reserved7 = 0;
  is.read( (char*)&reserved7, sizeof(Reserved7) );
  uint8_t reserved8 = 0;
  is.read( (char*)&reserved8, sizeof(Reserved8) );
  uint8_t source = 0;
  is.read( (char*)&source, sizeof(Source) );
  Source = source;
  uint8_t reason = 0;
  is.read( (char*)&reason, sizeof(Reason) );
  Reason = reason;

  assert( (ItemLength + 4 + 1 + 1) == Size() );
  return is;
}

const std::ostream &AAbortPDU::Write(std::ostream &os) const
{
  return os;
}

size_t AAbortPDU::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(Reserved7);
  ret += sizeof(Reserved8);
  ret += sizeof(Source);
  ret += sizeof(Reason);

  return ret;
}

} // end namespace network
} // end namespace gdcm
