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
#ifndef __gdcmPKCS7_h
#define __gdcmPKCS7_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for PKCS7 encryption
 *
 * http://www.openssl.org/docs/crypto/PKCS7_encrypt.html
 */
//-----------------------------------------------------------------------------
class PKCS7Internals;
class GDCM_EXPORT PKCS7
{
public :
  PKCS7();
  ~PKCS7();

  bool Encrypt(char *output, const char *array, size_t len) const;

protected:

private:
  PKCS7Internals *Internals;

private:
  PKCS7(const PKCS7&);  // Not implemented.
  void operator=(const PKCS7&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmPKCS7_h
