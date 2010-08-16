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
  //Data = ( "1.2.2.276.0.7230010.3.0.3.5.5" );
  //Data += "OFFIS_DCMTK_355";
  //ItemLength = Data.size();
  ItemLength = 0x3a;
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

} // end namespace network
} // end namespace gdcm
