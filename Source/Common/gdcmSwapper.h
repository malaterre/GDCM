/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmSwapper_h
#define __gdcmSwapper_h

#include "gdcmTypes.h"
#include "gdcmSwapCode.h"

namespace gdcm
{


class SwapperNoOp
{
public:
  template <typename T> static T Swap(T val) {}
  template <typename T> static void SwapArray(T *array, unsigned int n) {}
};

class SwapperDoOp
{
public:
  template <typename T> static T Swap(T val);
  template <typename T>
  static void SwapArray(T *array, unsigned int n)
  {
    // TODO: need to unroll loop:
    for(unsigned int i = 0; i < n; ++i)
    {
      array[i] = Swap<T>(array[i]);
    }
  }
};


} // end namespace gdcm

#endif //__gdcmSwapper_h
