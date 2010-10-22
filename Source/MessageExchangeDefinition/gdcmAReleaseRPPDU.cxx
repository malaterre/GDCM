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

#include "gdcmAReleaseRPPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AReleaseRPPDU::ItemType = 0x6; // PDUType ?
const uint8_t AReleaseRPPDU::Reserved2 = 0x0;
const uint32_t AReleaseRPPDU::Reserved7_10 = 0x0;

AReleaseRPPDU::AReleaseRPPDU()
{
  ItemLength = Size() - 6; // PDU Length
  assert( ItemLength + 6 == Size() );
}

std::istream &AReleaseRPPDU::Read(std::istream &is)
{
  //uint8_t itemtype = 0;
  //is.read( (char*)&itemtype, sizeof(ItemType) );
  //assert( itemtype == ItemType );
  uint8_t reserved2 = 0;
  is.read( (char*)&reserved2, sizeof(Reserved2) );
  uint32_t itemlength = ItemLength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  uint32_t reserved7_10;
  is.read( (char*)&reserved7_10, sizeof(Reserved7_10) );

  assert( ItemLength + 6 == Size() );
  return is;
}

const std::ostream &AReleaseRPPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&Reserved7_10, sizeof(Reserved7_10) );

  assert( ItemLength + 6 == Size() );

  return os;
}

size_t AReleaseRPPDU::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength); // len of
  ret += sizeof(Reserved7_10);

  return ret;
}



void AReleaseRPPDU::Print(std::ostream &os) const
{
  os << "Not implemented yet" << std::endl;
}

} // end namespace network
} // end namespace gdcm
