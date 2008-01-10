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
#include "gdcmTrace.h"

namespace gdcm
{
static const char *ScalarTypeStrings[] = {
  "INT8",
  "UINT8",
  "INT12",
  "UINT12",
  "INT16",
  "UINT16",
  "INT32",
  "UINT32",  
  NULL,
};

unsigned short PixelFormat::GetSamplesPerPixel() const
{
  if ( BitsAllocated == 24 )
    {
    gdcmWarningMacro( "This is illegal in DICOM, assuming a RGB image" );
    return 3;
    }
  return SamplesPerPixel;
}

PixelFormat::ScalarType PixelFormat::GetScalarType() const
{
  ScalarType type = PixelFormat::UNKNOWN;
  switch( BitsAllocated )
    {
  case 8:
    type = PixelFormat::UINT8;
    break;
  case 12:
    type = PixelFormat::UINT12;
    break;
  case 16:
    type = PixelFormat::UINT16;
    break;
  case 32:
    type = PixelFormat::UINT32;
    break;    
  case 24:
    gdcmWarningMacro( "This is illegal in DICOM, assuming a RGB image" );
    type = PixelFormat::UINT8;
    break;
    
  default:
    gdcmErrorMacro( "I have never seen this before BitsAllocated "
      << BitsAllocated );
    abort();
    }
  if( PixelRepresentation )
    {
    assert( type <= INT32 );
    // That's why you need to order properly type in ScalarType
    type = ScalarType(int(type)+1);
    }
  return type;
}

const char *PixelFormat::GetScalarTypeAsString() const
{
  return ScalarTypeStrings[GetScalarType()];
}

uint8_t PixelFormat::GetPixelSize() const
{
  assert( !(BitsAllocated % 8 ) );
  uint8_t pixelsize = BitsAllocated / 8;
  pixelsize *= SamplesPerPixel;

  return pixelsize;
}

void PixelFormat::Print(std::ostream &os) const
{
  os << "SamplesPerPixel    :" << SamplesPerPixel     << "\n"; 
  os << "BitsAllocated      :" << BitsAllocated       << "\n";
  os << "BitsStored         :" << BitsStored          << "\n";
  os << "HighBit            :" << HighBit             << "\n";
  os << "PixelRepresentation:" << PixelRepresentation << "\n";
}

} // end namespace gdcm
