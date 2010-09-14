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
#include "gdcmAAssociateACPDU.h"
#include "gdcmSwapper.h"

namespace gdcm
{
namespace network
{
const uint8_t AAssociateACPDU::ItemType = 0x02; // PDUType ?
const uint8_t AAssociateACPDU::Reserved2 = 0x00;
const uint16_t AAssociateACPDU::ProtocolVersion = 0x01; // big endian
const uint16_t AAssociateACPDU::Reserved9_10 = 0x0000;
const uint8_t AAssociateACPDU::Reserved11_26[16] = {  };
const uint8_t AAssociateACPDU::Reserved27_42[16] = {  };
const uint8_t AAssociateACPDU::Reserved43_74[32] = {  };

AAssociateACPDU::AAssociateACPDU()
{
  PDULength = 0; // len of 
}

std::istream &AAssociateACPDU::Read(std::istream &is)
{
  //uint8_t itemtype = 0;
  //is.read( (char*)&itemtype, sizeof(ItemType) );
  //assert( itemtype == ItemType );
  uint8_t reserved2;
  is >> reserved2;
  uint32_t pdulength;
  is.read( (char*)&pdulength, sizeof(PDULength) );
  SwapperDoOp::SwapArray(&pdulength,1);
  PDULength = pdulength;
  uint16_t protocolversion;
  is.read( (char*)&protocolversion, sizeof(ProtocolVersion) );
  SwapperDoOp::SwapArray(&protocolversion,1);
  if( protocolversion != ProtocolVersion )
    {
    assert(0 && "TODO" );
    }
  uint16_t reserved9_10;
  is.read( (char*)&reserved9_10, sizeof(Reserved9_10) );
  SwapperDoOp::SwapArray(&reserved9_10,1);
  uint8_t reserved11_26[16] = {  };
  is.read( (char*)&reserved11_26, sizeof(Reserved11_26) ); // called
  uint8_t reserved27_42[16] = {  };
  is.read( (char*)&reserved27_42, sizeof(Reserved27_42) ); // calling
  uint8_t reserved43_74[32] = {  };
  is.read( (char*)&reserved43_74, sizeof(Reserved43_74) ); // 0 (32 times)

  uint8_t itemtype2 = 0x0;
  size_t curlen = 0;
  while( curlen + 68 < PDULength )
    {
    is.read( (char*)&itemtype2, sizeof(ItemType) );
    switch ( itemtype2 )
      {
    case 0x10: // ApplicationContext ItemType
      AppContext.Read( is );
      curlen += AppContext.Size();
      break;
    case 0x21: // PresentationContextAC ItemType
        {
        PresentationContextAC pcac;
        pcac.Read( is );
        PresContextAC.push_back( pcac );
        curlen += pcac.Size();
        }
      break;
    case 0x50: // UserInformation ItemType
      UserInfo.Read( is );
      curlen += UserInfo.Size();
      break;
    default:
      gdcmErrorMacro( "Unknown ItemType: " << std::hex << (int) itemtype2 );
      curlen = PDULength; // make sure to exit
      break;
      }
    // WARNING: I cannot simply call Size() since UserInfo is initialized with GDCM
    // own parameter, this will bias the computation. Instead compute relative
    // length of remaining bytes to read.
    //curlen = Size();
    }
  assert( curlen + 68 == PDULength );

  assert( PDULength + 4 + 1 + 1 == Size() );

  return is;
}

const std::ostream &AAssociateACPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&PDULength, sizeof(PDULength) );
  uint32_t copy = PDULength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(PDULength) );
  uint16_t protocolversion = ProtocolVersion;
  SwapperDoOp::SwapArray(&protocolversion,1);
  os.write( (char*)&protocolversion, sizeof(ProtocolVersion) );
  os.write( (char*)&Reserved9_10, sizeof(Reserved9_10) );
  //os.write( (char*)&Reserved11_26, sizeof(Reserved11_26) );
  const char calling[] = "ANY-SCP         ";
  os.write( calling, 16 );

  //os.write( (char*)&Reserved27_42, sizeof(Reserved27_42) );
  //const char called[] = "STORESCU        ";
  const char called[] = "ECHOSCU        ";
  os.write( called, 16 );
  os.write( (char*)&Reserved43_74, sizeof(Reserved43_74) );
  AppContext.Write( os );
  std::vector<PresentationContextAC>::const_iterator it = PresContextAC.begin();
  for( ; it != PresContextAC.end(); ++it )
    {
    it->Write( os );
    }
  UserInfo.Write( os );

  return os;
}

size_t AAssociateACPDU::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(PDULength);
  ret += sizeof(ProtocolVersion);
  ret += sizeof(Reserved9_10);
  ret += sizeof(Reserved11_26);
  ret += sizeof(Reserved27_42);
  ret += sizeof(Reserved43_74);
  ret += AppContext.Size();
  std::vector<PresentationContextAC>::const_iterator it = PresContextAC.begin();
  for( ; it != PresContextAC.end(); ++it )
    {
    ret += it->Size();
    }
  ret += UserInfo.Size();
  return ret;
}

void AAssociateACPDU::AddPresentationContextAC( PresentationContextAC const &pcac )
{
  PresContextAC.push_back( pcac );
  PDULength = Size() - 6;
  assert( PDULength + 4 + 1 + 1 == Size() );
}

void AAssociateACPDU::Print(std::ostream &os) const
{
  std::vector<PresentationContextAC>::const_iterator it = PresContextAC.begin();
  for( ; it != PresContextAC.end(); ++it )
    {
    it->Print(os);
    }
}

} // end namespace network
} // end namespace gdcm
