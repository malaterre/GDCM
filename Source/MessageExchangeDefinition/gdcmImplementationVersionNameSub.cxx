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
#include "gdcmImplementationVersionNameSub.h"

namespace gdcm
{
namespace network
{
const uint8_t ImplementationVersionNameSub::ItemType = 0x55;
const uint8_t ImplementationVersionNameSub::Reserved2 = 0x00;

ImplementationVersionNameSub::ImplementationVersionNameSub()
{
  ImplementationVersionName = "OFFIS_DCMTK_355";
  ItemLength = ImplementationVersionName.size();
}

const std::ostream &ImplementationVersionNameSub::Write(std::ostream &os) const
{
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  os.write( (char*)&ItemLength, sizeof(ItemLength) );
  os.write( ImplementationVersionName.c_str(), ImplementationVersionName.size() );

  return os;
}

} // end namespace network
} // end namespace gdcm
