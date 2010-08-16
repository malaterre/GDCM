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
#include "gdcmUserInformation.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{

const uint8_t UserInformation::ItemType = 0x50;
const uint8_t UserInformation::Reserved2 = 0x00;

UserInformation::UserInformation()
{
  size_t t0 = MLS.Size();
  size_t t1 = ICUID.Size();
  size_t t2 = IVNS.Size();
  ItemLength = t0 + t1 + t2;
  assert( ItemLength + 4 == Size() );
}

std::istream &UserInformation::Read(std::istream &is)
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

  MLS.Read(is);
  ICUID.Read(is);
  IVNS.Read(is);

  return is;
}

const std::ostream &UserInformation::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  MLS.Write(os);
  //os.write( Data.c_str(), Data.size() );
  ICUID.Write(os);
  IVNS.Write(os);

  return os;
}

size_t UserInformation::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength); // len of
  ret += MLS.Size();
  ret += ICUID.Size();
  ret += IVNS.Size();

  return ret;
}

} // end namespace network
} // end namespace gdcm
