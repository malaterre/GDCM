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
#ifndef __gdcmX509_h
#define __gdcmX509_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for x509 
 *
 */
//-----------------------------------------------------------------------------
class X509Internals;
class GDCM_EXPORT X509
{
public :
  X509();
  ~X509();

  typedef enum {
/*#define POLARSSL_*/ ERR_X509_KEY_PASSWORD_REQUIRED           = -0x02C0,
/*#define POLARSSL_*/ ERR_X509_KEY_PASSWORD_MISMATCH           = -0x02E0
  } X509ErrorType;

private:
  X509Internals *Internals;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmX509_h
