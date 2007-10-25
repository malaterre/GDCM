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
#include "gdcmJPEG8Codec.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"

extern "C" {
#include "jpeg/8/jinclude.h"
#include "jpeg/8/jpeglib.h"
#include "jpeg/8/jerror.h"
}

#include <setjmp.h>

#define JPEGBITSCodec JPEG8Codec
#include "gdcmJPEGBITSCodec.cxx"
