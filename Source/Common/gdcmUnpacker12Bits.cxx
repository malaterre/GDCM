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
#include "gdcmUnpacker12Bits.h"

namespace gdcm
{

bool Unpacker12Bits::Unpack(char *out, const char *in, size_t n)
{
  uint16_t *out16 = (uint16_t*)out;
  const uint8_t *p = (const uint8_t*)in;
  const uint8_t * end = p + n;
  for(; p != end; )
  {
    uint8_t b0, b1, b2;
    b0 = p[0];
    b1 = p[1];
    b2 = p[2];
    *out16++ =  ((b0 >> 4) << 8) + ((b0 & 0x0f) << 4) + (b1 & 0x0f);
    *out16++ =  ((b2 & 0x0f) << 8) + ((b1 >> 4) << 4) + (b2 >> 4);
    p += 3;
  }
  return true;
}

} // end namespace gdcm

