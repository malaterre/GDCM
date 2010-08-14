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
#include "gdcmImplementationClassUIDSub.h"

namespace gdcm
{
namespace network
{
const uint8_t ImplementationClassUIDSub::ItemType = 0x52;
const uint8_t ImplementationClassUIDSub::Reserved2 = 0x00;

ImplementationClassUIDSub::ImplementationClassUIDSub()
{
  ImplementationClassUID = "1.2.276.0.7230010.3.0.3.5.5";
  ItemLength = ImplementationClassUID.size();
}

const std::ostream &ImplementationClassUIDSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( ImplementationClassUID.c_str(), ImplementationClassUID.size() );

  return os;
}

} // end namespace network
} // end namespace gdcm
