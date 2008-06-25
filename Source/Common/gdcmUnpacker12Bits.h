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
#ifndef __gdcmUnpacker12Bits_h
#define __gdcmUnpacker12Bits_h

#include "gdcmSwapCode.h"

namespace gdcm
{
/** \class Unpacker12Bits
 * \brief Unpacked 12 bits pixel into 16bits 
 */

class GDCM_EXPORT Unpacker12Bits
{
public:
  Unpacker12Bits() {}
  ~Unpacker12Bits() {}
  bool Unpack(char *out, const char *in, size_t n);
};

} // end namespace gdcm

#endif //__gdcmUnpacker12Bits_h
