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
#ifndef __gdcmSwapper_txx
#define __gdcmSwapper_txx

#ifdef HAVE_BYTESWAP_H
// TODO: not cross plateform...
#include <byteswap.h>
#endif


namespace gdcm
{

  template <> inline uint16_t SwapperDoOp::Swap<uint16_t>(uint16_t val)
    {
#ifdef HAVE_BYTESWAP_H
    return bswap_16(val);
#else
    return (val>>8) | (val<<8);
#endif
    }
  template <> inline uint32_t SwapperDoOp::Swap<uint32_t>(uint32_t val)
    {
#ifdef HAVE_BYTESWAP_H
    return bswap_32(val);
#else
    val= ((val<<8)&0xFF00FF00) | ((val>>8)&0x00FF00FF);
    val= (val>>16) | (val<<16);
    return val;
#endif
    }
  template <> inline uint64_t SwapperDoOp::Swap<uint64_t>(uint64_t val)
    {
#ifdef HAVE_BYTESWAP_H
    return bswap_64(val);
#else
    val= ((val<< 8)&0xFF00FF00FF00FF00ULL) | ((val>> 8)&0x00FF00FF00FF00FFULL);
    val= ((val<<16)&0xFFFF0000FFFF0000ULL) | ((val>>16)&0x0000FFFF0000FFFFULL);
    return (val>>32) | (val<<32);
#endif
    }

  template <> inline void SwapperDoOp::SwapArray(uint8_t *array, unsigned int n) {}

} // end namespace gdcm
 
#endif // __gdcmSwapper_txx
