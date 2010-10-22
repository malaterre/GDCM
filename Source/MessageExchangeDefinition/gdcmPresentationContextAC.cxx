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

#include "gdcmPresentationContextAC.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t PresentationContextAC::ItemType = 0x21;
const uint8_t PresentationContextAC::Reserved2 = 0x00;
const uint8_t PresentationContextAC::Reserved6 = 0x00;
const uint8_t PresentationContextAC::Reserved8 = 0x00;

PresentationContextAC::PresentationContextAC()
{
  ItemLength = 0; // len of last transfer syntax
  ID = 1; // odd [1-255]
  Result = 0;
  //assert( ItemLength + 4 == Size() );
}

std::istream &PresentationContextAC::Read(std::istream &is)
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
  uint8_t id;
  is.read( (char*)&id, sizeof(ID) );
  ID = id;
  uint8_t reserved6;
  is.read( (char*)&reserved6, sizeof(Reserved6) );
  uint8_t result;
  is.read( (char*)&result, sizeof(Result) );
  Result = result; // 0-4
  uint8_t reserved8;
  is.read( (char*)&reserved8, sizeof(Reserved6) );
  SubItems.Read( is );

  assert( ItemLength + 4 == Size() );
  return is;
}

const std::ostream &PresentationContextAC::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&ID, sizeof(ID) );
  os.write( (char*)&Reserved6, sizeof(Reserved6) );
  os.write( (char*)&Result, sizeof(Result) );
  os.write( (char*)&Reserved8, sizeof(Reserved8) );
  SubItems.Write(os);

  assert( ItemLength + 4 == Size() );
  return os;
}

size_t PresentationContextAC::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(ID);
  ret += sizeof(Reserved6);
  ret += sizeof(Result);
  ret += sizeof(Reserved8);
  ret += SubItems.Size();
  return ret;
}

void PresentationContextAC::SetTransferSyntax( TransferSyntax_ const &ts )
{
  SubItems = ts;
  ItemLength = Size() - 4;
  assert( ItemLength + 4 == Size() );
}

void PresentationContextAC::Print(std::ostream &os) const
{
  os << "ID: " << (int)ID << std::endl;
  os << "Result: " << (int)Result << std::endl;
  os << "TransferSyntax: ";
  SubItems.Print( os );
}

void PresentationContextAC::SetPresentationContextID( uint8_t id )
{
  ID = id;
}

} // end namespace network
} // end namespace gdcm
