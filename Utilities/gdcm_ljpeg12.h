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
#ifndef __gdcm_ljpeg12_h
#define __gdcm_ljpeg12_h

/* Use the ljpeg library configured for gdcm.  */
#include "gdcmTypes.h"

#ifdef GDCM_USE_SYSTEM_LJPEG
# include <ljpeg-62/12/jinclude.h>
# include <ljpeg-62/12/jpeglib.h>
# include <ljpeg-62/12/jerror.h>
#else
extern "C" {
#include "gdcmjpeg/12/jinclude.h"
#include "gdcmjpeg/12/jpeglib.h"
#include "gdcmjpeg/12/jerror.h"
}
#endif

#endif
