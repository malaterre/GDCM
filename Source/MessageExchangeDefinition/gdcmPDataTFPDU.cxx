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
#include "gdcmPDataTFPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t PDataTPPDU::ItemType = 0x04; // PDUType ?
const uint8_t PDataTPPDU::Reserved2 = 0x00;

PDataTPPDU::PDataTPPDU()
{
  PresentationDataValue pdv;
  V.push_back( pdv );

  ItemLength = Size() - 6;
  assert( (ItemLength + 4 + 1 + 1) == Size() );
}

std::istream &PDataTPPDU::Read(std::istream &is)
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

  PresentationDataValue pdv;
  pdv.Read( is );
  V.push_back( pdv );
//  std::vector<PresentationDataValue>::const_iterator it = V.begin();
//  for( ; it != V.end(); ++it )
//    {
//    it->Write( os );
//    }

  return is;
}

const std::ostream &PDataTPPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  std::vector<PresentationDataValue>::const_iterator it = V.begin();
  for( ; it != V.end(); ++it )
    {
    it->Write( os );
    }

  return os;
}

size_t PDataTPPDU::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  std::vector<PresentationDataValue>::const_iterator it = V.begin();
  for( ; it != V.end(); ++it )
    {
    ret += it->Size( );
    }

  return ret;
}

} // end namespace network
} // end namespace gdcm
