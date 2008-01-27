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
#include "gdcmPixelFormat.h"

int TestPixelFormat(int , char *[])
{
  gdcm::PixelFormat pf;
  pf.SetScalarType( gdcm::PixelFormat::UNKNOWN );
  if( pf.GetScalarType() != gdcm::PixelFormat::UNKNOWN )
    {
    return 1;
    }
  
  return 0;
}
