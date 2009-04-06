/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcm_polarssl_h
#define __gdcm_polarssl_h

/* Use the uuid library configured for gdcm.  */
#include "gdcmTypes.h"
#ifdef GDCM_USE_SYSTEM_POLARSSL
# include <uuid/uuid.h>
#else
# include <gdcmpolarssl/include/polarssl/config.h>
# include <gdcmpolarssl/include/polarssl/rsa.h>
# include <gdcmpolarssl/include/polarssl/x509.h>
# include <gdcmpolarssl/include/polarssl/aes.h>
# include <gdcmpolarssl/include/polarssl/md5.h>
# include <gdcmpolarssl/include/polarssl/sha1.h>
# include <gdcmpolarssl/include/polarssl/havege.h>
#endif

#endif
