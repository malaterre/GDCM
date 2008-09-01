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
#include "gdcmUnpacker12Bits.h"

namespace gdcm
{

bool Unpacker12Bits::Unpack(char *out, const char *in, size_t n)
{
  if( n % 3 ) return false;
  // http://groups.google.com/group/comp.lang.c/msg/572bc9b085c717f3
  short *q = (short*)out;
  unsigned char *p = (unsigned char*)in;
  const unsigned char *end = p+n;
  unsigned char b0,b1,b2;

  while (p!=end)
    {
    b0 = *p++;
    b1 = *p++;
    b2 = *p++;
    *q++ =  ((b1 & 0xf) << 8) + b0;
    *q++ =  (b1>>4) + (b2<<4);
    } 
  return true;
}

bool Unpacker12Bits::Pack(char *out, const char *in, size_t n)
{
  return false;
}

} // end namespace gdcm

