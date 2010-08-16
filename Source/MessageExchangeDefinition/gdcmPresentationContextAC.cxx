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
}

std::istream &PresentationContextAC::Read(std::istream &is)
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
  TransferSyntax_ ts;
  ts.Read( is );
}

const std::ostream &PresentationContextAC::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( (char*)&ID, sizeof(ID) );
  os.write( (char*)&Reserved6, sizeof(Reserved6) );
  os.write( (char*)&Result, sizeof(Result) );
  os.write( (char*)&Reserved8, sizeof(Reserved8) );
  SubItems.Write(os);

  return os;
}

} // end namespace network
} // end namespace gdcm
