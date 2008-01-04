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
#include "gdcmJPEG12Codec.h"

extern "C" {
#include "jpeg/12/jinclude.h"
#include "jpeg/12/jpeglib.h"
#include "jpeg/12/jerror.h"
}

#include <setjmp.h>

#define JPEGBITSCodec JPEG12Codec
#include "gdcmJPEGBITSCodec.cxx"

