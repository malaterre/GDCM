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

#include "gdcmUserInformation.h"
#include "gdcmSwapper.h"
#include "gdcmAsynchronousOperationsWindowSub.h"

namespace gdcm
{
namespace network
{

const uint8_t UserInformation::ItemType = 0x50;
const uint8_t UserInformation::Reserved2 = 0x00;

UserInformation::UserInformation()
{
  AOWS = NULL;
  size_t t0 = MLS.Size();
  size_t t1 = ICUID.Size();
  size_t t2 = 0; //AOWS.Size();
  size_t t3 = IVNS.Size();
  ItemLength = t0 + t1 + t2 + t3;
  assert( (size_t)ItemLength + 4 == Size() );
}

std::istream &UserInformation::Read(std::istream &is)
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

//  MLS.Read(is);
//  ICUID.Read(is);
//  IVNS.Read(is);
  uint8_t itemtype2 = 0x0;
  size_t curlen = 0;
  while( curlen < ItemLength )
    {
    is.read( (char*)&itemtype2, sizeof(ItemType) );
    switch ( itemtype2 )
      {
    case 0x51: // MaximumLengthSub
      MLS.Read( is );
      curlen += MLS.Size();
      break;
    case 0x52: // ImplementationClassUIDSub
      ICUID.Read(is);
      curlen += ICUID.Size();
      break;
    case 0x53: // AsynchronousOperationsWindowSub
      assert( !AOWS );
      AOWS = new AsynchronousOperationsWindowSub;
      AOWS->Read( is );
      curlen += AOWS->Size();
      break;
    case 0x55: // ImplementationVersionNameSub
      IVNS.Read( is );
      curlen += IVNS.Size();
      break;
    default:
      gdcmErrorMacro( "Unknown ItemType: " << std::hex << (int) itemtype2 );
      curlen = ItemLength; // make sure to exit
      assert(0);
      break;
      }
    }
  assert( curlen == ItemLength );

  assert( (size_t)ItemLength + 4 == Size() );
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
  ICUID.Write(os);
  if( AOWS )
    {
    AOWS->Write(os);
    }
  IVNS.Write(os);

  assert( (size_t)ItemLength + 4 == Size() );

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
  if( AOWS )
    ret += AOWS->Size();
  ret += IVNS.Size();

  return ret;
}

void UserInformation::Print(std::ostream &os) const
{
}

} // end namespace network
} // end namespace gdcm
