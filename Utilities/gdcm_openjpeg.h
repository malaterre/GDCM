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
#ifndef __gdcm_openjpeg_h
#define __gdcm_openjpeg_h

/* Use the openjpeg library configured for gdcm.  */
#include "gdcmTypes.h"
#ifdef GDCM_USE_SYSTEM_OPENJPEG
//# include <openjpeg-1.0/openjpeg.h>
# include <openjpeg.h>
#else
extern "C" {
#include <gdcmopenjpeg/libopenjpeg/openjpeg.h>
}
#endif

#endif

