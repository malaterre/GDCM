/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTag.h"
#include "gdcmTrace.h"

namespace gdcm
{
  void Tag::ReadFromCommaSeparatedString(const char *str)
    {
    unsigned int group = 0, element = 0;
    if( sscanf(str, "%04x,%04x", &group , &element) != 2 )
      {
      gdcmErrorMacro( "Problem reading the Tag: " << str );
      }
    SetGroup( group );
    SetElement( element );
    }
} // end namespace gdcm
