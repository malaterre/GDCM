/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPhotometricInterpretation.h"
#include "gdcmTrace.h"
#include <assert.h>
#include <stdlib.h>

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

  // Ouch ! We did not find anything, that's pretty bad, let's hope that 
  // the toolkit who wrote the image is buggy and tolerate \0 padded ASCII
  // string
  i = 0;
  while(PIStrings[i] != 0)
    {
    if( strncmp(pi, PIStrings[i], strlen(pi) ) == 0 )
      {
      gdcmDebugMacro( "PhotometricInterpretation was found: [" << pi 
        << "], but is invalid. It should be padded with a space" );
      return PIType(i);
      }
    ++i;
    }
  // too many whitespaces ??
  // http://deckard.mc.duke.edu/~samei/tg18_files/TG18-CH-dcm.zip
  // TG18-CH-2k-01.dcm
  i = 0;
  while(PIStrings[i] != 0)
    {
    if( strncmp(pi, PIStrings[i], strlen(PIStrings[i]) ) == 0 )
      {
      gdcmDebugMacro( "PhotometricInterpretation was found: [" << pi 
        << "], but is invalid. It should be padded with at most a single space" );
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
