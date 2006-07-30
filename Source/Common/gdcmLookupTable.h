/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmLookupTable_h
#define __gdcmLookupTable_h

#include "gdcmTypes.h"

#include <vector>

namespace gdcm
{
  
class LookupTableInternal;
class ByteValue;
class LookupTable
{
public:
  typedef enum {
    UNKNOWN = 0,
    GRAY,
    RED,
    GREEN,
    BLUE,
  } LookupTableType;

  LookupTable();
  ~LookupTable();

  void SetRedLUT(ByteValue const &bv);
  void SetGreenLUT(ByteValue const &bv);
  void SetBlueLUT(ByteValue const &bv);

private:
  LookupTableInternal *Internal;
};

} // end namespace gdcm

#endif //__gdcmLookupTable_h
