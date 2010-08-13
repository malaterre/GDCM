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
#include "gdcmApplicationContext.h"

namespace gdcm
{
namespace network
{
const uint8_t ApplicationContext::ItemType = 0x10;
const uint8_t ApplicationContext::Reserved2 = 0x00;

ApplicationContext::ApplicationContext()
{
  ItemLength = 0;
  Name = "1.2.840.10008.3.1.1.1";
}

const std::ostream &ApplicationContext::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( Name.c_str(), Name.size() );
  return os;
}

} // end namespace network
} // end namespace gdcm
