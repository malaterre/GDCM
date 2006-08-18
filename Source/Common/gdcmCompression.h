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
#ifndef __gdcmCompression_h
#define __gdcmCompression_h

#include "gdcmTypes.h"

namespace gdcm
{

class Compression
{
public:
  typedef enum {
    UNKNOWN = 0,
    RAW,
    JPEG,
    JPEG2000,
    RLE
  } Types;
};

}

#endif //__gdcmCompression_h
