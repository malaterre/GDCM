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

#include "gdcmImplementationVersionNameSub.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t ImplementationVersionNameSub::ItemType = 0x55;
const uint8_t ImplementationVersionNameSub::Reserved2 = 0x00;

ImplementationVersionNameSub::ImplementationVersionNameSub()
{
  ImplementationVersionName = FileMetaInformation::GetImplementationVersionName();
  ItemLength = ImplementationVersionName.size();
  assert( ItemLength + 4 == Size() );
}

std::istream &ImplementationVersionNameSub::Read(std::istream &is)
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

  char name[256];
  assert( itemlength < 256 );
  is.read( name, itemlength );
  ImplementationVersionName = std::string(name,itemlength);

  return is;
}

const std::ostream &ImplementationVersionNameSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  os.write( ImplementationVersionName.c_str(), ImplementationVersionName.size() );

  return os;
}

size_t ImplementationVersionNameSub::Size() const
{
  size_t ret = 0;
  assert( ImplementationVersionName.size() == ItemLength );
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += ItemLength;

  return ret;
}

} // end namespace network
} // end namespace gdcm
