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
 * \brief Pack/Unpack 12 bits pixel into 16bits 
 * - You can only pack an even number of 16bits, which means a multiple of 4 (expressed in bytes)
 * - You can only unpack a multiple of 3 bytes
 */
class GDCM_EXPORT Unpacker12Bits
{
public:
  /// Pack an array of 16bits where all values are 12bits into a pack form
  /// n is the length in bytes of array in, out will be a fake 8bits array of size n / 2 * 3
  static bool Pack(char *out, const char *in, size_t n);

  /// Unpack an array of 'packed' 12bits data into a more conventional 16bits array
  /// n is the length in bytes of array in, out will be a 16bits array of size n / 3 * 2
  static bool Unpack(char *out, const char *in, size_t n);
};

} // end namespace gdcm

#endif //__gdcmUnpacker12Bits_h
