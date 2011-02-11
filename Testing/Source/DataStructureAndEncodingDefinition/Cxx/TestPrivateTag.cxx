/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPrivateTag.h"

int TestPrivateTag(int , char * [])
{
  gdcm::PrivateTag pt(0x29,0x1018,"SIEMENS CSA HEADER");
  if( pt != gdcm::Tag(0x0029,0x18) )
    {
    std::cerr << pt << std::endl;
    return 1;
    }
//  if( pt.GetOwner() != std::string("SIEMENS CSA HEADER") )
//    {
//    std::cerr << "[" << pt.GetOwner() << "]" << std::endl;
//    return 1;
//    }

  const char str[] = "0029,1019,SIEMENS CSA HEADER";

  if( !pt.ReadFromCommaSeparatedString( str ) ) return 1;

  if( pt != gdcm::Tag(0x0029,0x19) )
    {
    std::cerr << pt << std::endl;
    return 1;
    }
  if( pt.GetOwner() != std::string("SIEMENS CSA HEADER") )
    {
    std::cerr << "[" << pt.GetOwner() << "]" << std::endl;
    return 1;
    }

  return 0;
}
