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
  ID = 0;
  Result = 0;
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
  //SubItems.Write(os);

  return os;
}

} // end namespace network
} // end namespace gdcm
