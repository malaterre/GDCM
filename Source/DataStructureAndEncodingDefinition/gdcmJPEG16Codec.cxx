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
#include "gdcmJPEG16Codec.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"

extern "C" {
#include "jpeg/16/jinclude.h"
#include "jpeg/16/jpeglib.h"
#include "jpeg/16/jerror.h"
}

#include <setjmp.h>

#define JPEGBITSCodec JPEG16Codec
#include "gdcmJPEGBITSCodec.cxx"

