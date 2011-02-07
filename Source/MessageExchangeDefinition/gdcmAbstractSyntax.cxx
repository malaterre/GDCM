/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "gdcmAbstractSyntax.h"
#include "gdcmSwapper.h"
#include <limits>

namespace gdcm
{
namespace network
{
const uint8_t AbstractSyntax::ItemType = 0x30;
const uint8_t AbstractSyntax::Reserved2 = 0x00;

AbstractSyntax::AbstractSyntax()
{
  //UpdateName ( "1.2.840.10008.1.1" ); // Verification SOP Class
  ItemLength = 0;
}

std::istream &AbstractSyntax::Read(std::istream &is)
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
  Name = std::string(name,itemlength);

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
  assert(ret <= (size_t)std::numeric_limits<uint16_t>::max);
  assert(ret >= 4);
  return ret;
}

void AbstractSyntax::UpdateName( const char *name )
{
  if( name )
    {
    UIDs uids;
    bool b = uids.SetFromUID( name );
    if( b )
      {
      Name = name;
      size_t lenTemp = Name.size();
      assert(lenTemp < (size_t)std::numeric_limits<uint16_t>::max);
      ItemLength = (uint16_t)lenTemp;
      assert( (size_t)ItemLength + 4 == Size() );
      return;
      }
    }

  gdcmErrorMacro( "Invalid Name: " << name );
  throw "Invalid Name";
}

void AbstractSyntax::SetNameFromUID( UIDs::TSName tsname )
{
  const char *name = UIDs::GetUIDString( tsname );
  UpdateName( name );
}
void AbstractSyntax::SetNameFromUIDString( const std::string& inUIDName )
{
  const char *name = inUIDName.c_str();
  UpdateName( name );
}

void AbstractSyntax::Print(std::ostream &os) const
{
  os << Name << std::endl;
}


} // end namespace network
} // end namespace gdcm
