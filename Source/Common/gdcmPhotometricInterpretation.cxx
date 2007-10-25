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
#include "gdcmPhotometricInterpretation.h"
#include <assert.h>

namespace gdcm
{

static const char *PIStrings[] = {
  "UNKNOW",
  "MONOCHROME1 ",
  "MONOCHROME2 ",
  "PALETTE COLOR ",
  "RGB ",
  "HSV",
  "ARGB",
  "CMYK",
  "YBR_FULL",
  "YBR_FULL_422",
  "YBR_PARTIAL_422",
  "YBR_PARTIAL_420",
  "YBR_ICT",
  "YBR_RCT",
  0
};

const char *PhotometricInterpretation::GetPIString(PIType pi)
{
  assert( pi < PhotometricInterpretation::PI_END );
  return PIStrings[pi];
}

PhotometricInterpretation::PIType PhotometricInterpretation::GetPIType(const char *pi)
{
  int i = 0;
  while(PIStrings[i] != 0)
    {
    if( strcmp(pi, PIStrings[i]) == 0 )
      {
      return PIType(i);
      }
    ++i;
    }

  abort();
  return PI_END;
}

bool PhotometricInterpretation::IsRetired(PIType pi)
{
  return pi == HSV || pi == ARGB || pi == CMYK;
}

int PhotometricInterpretation::GetSamplesPerPixel()
{
  if( PIField == MONOCHROME1
   || PIField == MONOCHROME2 )
    {
    return 1;
    }
  else
    {
    assert( PIField != UNKNOW );
    assert( PIField != PI_END );
    assert( PIField == PALETTE_COLOR
         || PIField == RGB
         || PIField == HSV
         || PIField == ARGB
         || PIField == CMYK
         || PIField == YBR_FULL
         || PIField == YBR_FULL_422
         || PIField == YBR_PARTIAL_422
         || PIField == YBR_PARTIAL_420
         || PIField == YBR_ICT
         || PIField == YBR_RCT
      );
    return 3;
    }
}

} // end namespace gdcm
