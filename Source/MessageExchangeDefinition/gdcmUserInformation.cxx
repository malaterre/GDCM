/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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
  (void)os;
}

} // end namespace network
} // end namespace gdcm
