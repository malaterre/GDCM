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

#include "gdcmAsynchronousOperationsWindowSub.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AsynchronousOperationsWindowSub::ItemType = 0x53;
const uint8_t AsynchronousOperationsWindowSub::Reserved2 = 0x00;

AsynchronousOperationsWindowSub::AsynchronousOperationsWindowSub()
{
  ItemLength = 0;
  MaximumNumberOperationsInvoked = 0;
  MaximumNumberOperationsPerformed = 0;

  ItemLength = Size() - 4;
  assert( ItemLength + 4 == Size() );
}

std::istream &AsynchronousOperationsWindowSub::Read(std::istream &is)
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

  uint16_t maximumnumberoperationsinvoked;
  is.read( (char*)&maximumnumberoperationsinvoked, sizeof(MaximumNumberOperationsInvoked) );
  SwapperDoOp::SwapArray(&maximumnumberoperationsinvoked,1);
  MaximumNumberOperationsInvoked = maximumnumberoperationsinvoked;

  uint16_t maximumnumberoperationsperformed;
  is.read( (char*)&maximumnumberoperationsperformed, sizeof(MaximumNumberOperationsPerformed) );
  SwapperDoOp::SwapArray(&MaximumNumberOperationsPerformed,1);
  MaximumNumberOperationsPerformed = maximumnumberoperationsperformed;

  return is;
}

const std::ostream &AsynchronousOperationsWindowSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  assert(0); // TODO

  return os;
}

size_t AsynchronousOperationsWindowSub::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(MaximumNumberOperationsInvoked);
  ret += sizeof(MaximumNumberOperationsPerformed);

  return ret;
}

} // end namespace network
} // end namespace gdcm
