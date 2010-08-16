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
#include "gdcmImplementationClassUIDSub.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t ImplementationClassUIDSub::ItemType = 0x52;
const uint8_t ImplementationClassUIDSub::Reserved2 = 0x00;

ImplementationClassUIDSub::ImplementationClassUIDSub()
{
  ImplementationClassUID = "1.2.276.0.7230010.3.0.3.5.5";
  ItemLength = ImplementationClassUID.size();
}

std::istream &ImplementationClassUIDSub::Read(std::istream &is)
{
  uint8_t itemtype = 0x0;
  is.read( (char*)&itemtype, sizeof(ItemType) );
  assert( itemtype == ItemType );
  uint8_t reserved2;
  is.read( (char*)&reserved2, sizeof(Reserved2) );
  uint16_t itemlength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;

  char name[256];
  assert( itemlength < 256 );
  is.read( name, itemlength );
  ImplementationClassUID = name;

  return is;
}

const std::ostream &ImplementationClassUIDSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  os.write( ImplementationClassUID.c_str(), ImplementationClassUID.size() );

  return os;
}

} // end namespace network
} // end namespace gdcm
