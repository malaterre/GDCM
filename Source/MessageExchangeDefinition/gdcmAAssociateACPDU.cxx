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
const uint16_t AAssociateACPDU::ProtocolVersion = 0x01;
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
  uint8_t itemtype = 0;
  is.read( (char*)&itemtype, sizeof(ItemType) );
  assert( itemtype == ItemType );
  uint8_t reserved2;
  is >> reserved2;
  uint32_t pdulength;
  is.read( (char*)&pdulength, sizeof(PDULength) );
  SwapperDoOp::SwapArray(&pdulength,1);
  PDULength = pdulength;
  uint16_t protocolversion;
  is.read( (char*)&protocolversion, sizeof(ProtocolVersion) );
  SwapperDoOp::SwapArray(&protocolversion,1);
  uint16_t reserved9_10;
  is.read( (char*)&reserved9_10, sizeof(Reserved9_10) );
  SwapperDoOp::SwapArray(&reserved9_10,1);
  uint8_t reserved11_26[16] = {  };
  is.read( (char*)&reserved11_26, sizeof(Reserved11_26) ); // called
  uint8_t reserved27_42[16] = {  };
  is.read( (char*)&reserved27_42, sizeof(Reserved27_42) ); // calling
  uint8_t reserved43_74[32] = {  };
  is.read( (char*)&reserved43_74, sizeof(Reserved43_74) ); // 0 (32 times)

  AppContext.Read( is );
  PresentationContextAC pcac;
  pcac.Read( is );
  //std::vector<PresentationContextAC>::iterator it = PresContextAC.begin();
  //for( ; it != PresContextAC.end(); ++it )
  //  {
  //  it->Read( is );
  //  }
  UserInfo.Read( is );

  return is;
}

const std::ostream &AAssociateACPDU::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&PDULength, sizeof(PDULength) );
  uint16_t copy = PDULength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(PDULength) );
  os.write( (char*)&ProtocolVersion, sizeof(ProtocolVersion) );
  os.write( (char*)&Reserved9_10, sizeof(Reserved9_10) );
  os.write( (char*)&Reserved11_26, sizeof(Reserved11_26) );
  os.write( (char*)&Reserved27_42, sizeof(Reserved27_42) );
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

} // end namespace network
} // end namespace gdcm
