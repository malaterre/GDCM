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
#include "gdcmAbstractSyntax.h"

namespace gdcm
{
namespace network
{
const uint8_t AbstractSyntax::ItemType = 0x30;
const uint8_t AbstractSyntax::Reserved2 = 0x00;

AbstractSyntax::AbstractSyntax()
{
  Name = "1.2.840.10008.1.1";
  ItemLength = Name.size();
}

const std::ostream &AbstractSyntax::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( Name.c_str(), Name.size() );
  return os;
}

} // end namespace network
} // end namespace gdcm
