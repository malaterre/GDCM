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
    return val;
#endif
    }
  template <> inline uint32_t SwapperDoOp::Swap<uint32_t>(uint32_t val)
    {
#ifdef HAVE_BYTESWAP_H
    return bswap_32(val);
#else
    return val;
#endif
    }
  template <> inline uint64_t SwapperDoOp::Swap<uint64_t>(uint64_t val)
    {
#ifdef HAVE_BYTESWAP_H
    return bswap_64(val);
#else
    return val;
#endif
    }

} // end namespace gdcm
 
#endif // __gdcmSwapper_txx
