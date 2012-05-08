/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRoleSelectionSub.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t RoleSelectionSub::ItemType = 0x54;
const uint8_t RoleSelectionSub::Reserved2 = 0x00;

RoleSelectionSub::RoleSelectionSub()
{
  ItemLength = 0;
  UIDLength = 0;
  SCURole = 0;
  SCPRole = 0;

  ItemLength = Size() - 4;
  assert( (size_t)ItemLength + 4 == Size() );
}

std::istream &RoleSelectionSub::Read(std::istream &is)
{
  //uint8_t itemtype = 0x0;
  //is.read( (char*)&itemtype, sizeof(ItemType) );
  //assert( itemtype == ItemType );
  uint8_t reserved2;
  is.read( (char*)&reserved2, sizeof(Reserved2) );
  uint16_t itemlength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;

  uint16_t uidlength;
  is.read( (char*)&uidlength, sizeof(UIDLength) );
  SwapperDoOp::SwapArray(&uidlength,1);
  UIDLength = uidlength;

  char name[256];
  assert( uidlength < 256 );
  is.read( name, uidlength );
  Name = std::string(name,uidlength);

  uint8_t scurole;
  is.read( (char*)&scurole, sizeof(SCURole) );
  SCURole = scurole;

  uint8_t scprole;
  is.read( (char*)&scprole, sizeof(SCPRole) );
  SCPRole = scprole;

  return is;
}

const std::ostream &RoleSelectionSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  uint16_t uidlength = UIDLength;
  SwapperDoOp::SwapArray(&uidlength,1);
  os.write( (char*)&uidlength, sizeof(UIDLength) );

  os.write( Name.c_str(), Name.size() );

  uint8_t scurole = SCURole;
  os.write( (char*)&scurole, sizeof(SCURole) );

  uint8_t scprole = SCPRole;
  os.write( (char*)&scprole, sizeof(SCPRole) );

  return os;
}

size_t RoleSelectionSub::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(UIDLength);
  ret += UIDLength;
  ret += sizeof(SCURole);
  ret += sizeof(SCPRole);

  return ret;
}

} // end namespace network
} // end namespace gdcm
