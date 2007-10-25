/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmType.h"

namespace gdcm
{

static const char *TypeStrings[] = {
   "1",
   "1C",
   "2",
   "2C",
   "3",
   "UNKNOWN",
   0
};

const char *Type::GetTypeString(TypeType type)
{
  return TypeStrings[type];
}

Type::TypeType Type::GetTypeType(const char *type)
{
  int i = 0;
  while(TypeStrings[i] != 0)
    {
    if( strcmp(type, TypeStrings[i]) == 0 )
      return (TypeType)i;
    ++i;
    }
  return UNKNOWN;
}

} // end namespace gdcm
