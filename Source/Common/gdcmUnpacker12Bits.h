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
#ifndef __gdcmUnpacker12Bits_h
#define __gdcmUnpacker12Bits_h

#include "gdcmSwapCode.h"

namespace gdcm
{
/**
 * \brief Unpack 12 bits pixel into 16bits 
 */
class GDCM_EXPORT Unpacker12Bits
{
public:
  /// Unpack an array of 'packed' 12bits data into a more conventional 16bits array
  static bool Unpack(char *out, const char *in, size_t n);

  /// Pack (not implemented)
  static bool Pack(char *out, const char *in, size_t n);
};

} // end namespace gdcm

#endif //__gdcmUnpacker12Bits_h
