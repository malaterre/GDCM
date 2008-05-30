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
#ifndef __gdcm_zlib_h
#define __gdcm_zlib_h

/* Use the zlib library configured for gdcm.  */
#include "gdcmTypes.h"
#ifdef GDCM_USE_SYSTEM_ZLIB
// $ dpkg -S /usr/include/zlib.h
// zlib1g-dev: /usr/include/zlib.h
# include <zlib.h>
#else
# include <gdcmzlib/zlib.h>
#endif

#endif
