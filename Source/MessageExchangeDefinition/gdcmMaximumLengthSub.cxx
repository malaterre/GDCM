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
#include "gdcmMaximumLengthSub.h"

namespace gdcm
{
namespace network
{
const uint8_t MaximumLengthSub::ItemType = 0x51;
const uint8_t MaximumLengthSub::Reserved2 = 0x00;

MaximumLengthSub::MaximumLengthSub()
{
  ItemLength = 0;
  MaximumLength = 0;
}

const std::ostream &MaximumLengthSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( (char*)&MaximumLength, sizeof(MaximumLength) );

  return os;
}

} // end namespace network
} // end namespace gdcm
