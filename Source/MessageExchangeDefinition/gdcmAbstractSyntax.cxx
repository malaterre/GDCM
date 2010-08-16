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
#include "gdcmAbstractSyntax.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AbstractSyntax::ItemType = 0x30;
const uint8_t AbstractSyntax::Reserved2 = 0x00;

AbstractSyntax::AbstractSyntax()
{
  UpdateName ( "1.2.840.10008.1.1" ); // Verification SOP Class
}

std::istream &AbstractSyntax::Read(std::istream &is)
{
  assert( 0 );
  return is;
}

const std::ostream &AbstractSyntax::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  os.write( Name.c_str(), Name.size() );
  return os;
}

size_t AbstractSyntax::Size() const
{
  size_t ret = 0;
  assert( Name.size() == ItemLength );
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += ItemLength;
  return ret;
}

void AbstractSyntax::UpdateName( const char *name )
{
  if( name )
    {
    gdcm::UIDs uids;
    bool b = uids.SetFromUID( name );
    if( b )
      {
      Name = name;
      ItemLength = Name.size();
      assert( ItemLength + 4 == Size() );
      return;
      }
    }

  gdcmErrorMacro( "Invalid Name: " << name );
  throw "Invalid Name";
}

void AbstractSyntax::SetNameFromUID( gdcm::UIDs::TSName tsname )
{
  const char *name = gdcm::UIDs::GetUIDString( tsname );
  UpdateName( name );
}


} // end namespace network
} // end namespace gdcm
