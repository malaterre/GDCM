/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
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
/*
 * HSV/ARGB/CMYK can still be found in PS 3.3 - 2000:
 * 
 * HSV = Pixel data represent a color image described by hue, saturation, and value image planes.
 * The minimum sample value for each HSV plane represents a minimum value of each vector. This
 * value may be used only when Samples per Pixel (0028,0002) has a value of 3.
 *
 * ARGB = Pixel data represent a color image described by red, green, blue, and alpha image planes.
 * The minimum sample value for each RGB plane represents minimum intensity of the color. The
 * alpha plane is passed through Palette Color Lookup Tables. If the alpha pixel value is greater than
 * 0, the red, green, and blue lookup table values override the red, green, and blue, pixel plane colors.
 * This value may be used only when Samples per Pixel (0028,0002) has a value of 4.
 *
 * CMYK = Pixel data represent a color image described by cyan, magenta, yellow, and black image
 * planes. The minimum sample value for each CMYK plane represents a minimum intensity of the
 * color. This value may be used only when Samples per Pixel (0028,0002) has a value of 4.
 *
 */

static const char *PIStrings[] = {
  "UNKNOW",
  "MONOCHROME1 ",
  "MONOCHROME2 ",
  "PALETTE COLOR ",
  "RGB ",
  "HSV ",
  "ARGB",
  "CMYK",
  "YBR_FULL",
  "YBR_FULL_422",
  "YBR_PARTIAL_422 ",
  "YBR_PARTIAL_420 ",
  "YBR_ICT ",
  "YBR_RCT ",
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
  // the toolkit which wrote the image is buggy and tolerate \0 padded ASCII
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

  //abort();
  return PI_END;
}

bool PhotometricInterpretation::IsRetired(PIType pi)
{
  return pi == HSV || pi == ARGB || pi == CMYK;
}

unsigned short PhotometricInterpretation::GetSamplesPerPixel() const
{
  if ( PIField == UNKNOW ) return 0;
  else if( PIField == MONOCHROME1
   || PIField == MONOCHROME2 
   || PIField == PALETTE_COLOR )
    {
    return 1;
    }
  else if( PIField == ARGB || PIField == CMYK )
    {
    return 4;
    }
  else
    {
    assert( PIField != PI_END );
    assert( //PIField == PALETTE_COLOR
            PIField == RGB
         || PIField == HSV
         //|| PIField == ARGB
         //|| PIField == CMYK
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

bool PhotometricInterpretation::IsLossy() const
{
  return !IsLossless();
}

bool PhotometricInterpretation::IsLossless() const
{
  switch ( PIField )
    {
  case MONOCHROME1:
  case MONOCHROME2:
  case PALETTE_COLOR:
  case RGB:
  case HSV:
  case ARGB:
  case CMYK:
  case YBR_FULL:
  case YBR_RCT:
    return true;
    break;
  case YBR_FULL_422:
  case YBR_PARTIAL_422:
  case YBR_PARTIAL_420:
  case YBR_ICT:
    return false;
    break;
    }

  assert( 0 ); // technically one should not reach here, unless UNKNOW ...
  return false;
}

const char *PhotometricInterpretation::GetString() const
{
  return PhotometricInterpretation::GetPIString( PIField );
}

bool PhotometricInterpretation::IsSameColorSpace( PhotometricInterpretation const &pi ) const
{
  if( PIField == pi ) return true;

  // else
  if( PIField == RGB
   || PIField == YBR_RCT
   || PIField == YBR_ICT )
    {
    if( pi == RGB || pi == YBR_RCT || pi == YBR_ICT ) return true;
    }

  return false;
}

} // end namespace gdcm
