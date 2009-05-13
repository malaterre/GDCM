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
#ifndef __gdcmMD5_h
#define __gdcmMD5_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for MD5 
 *
 * \warning this class is able to pick from two implementations:
 *
 * 1. a lightweight md5 implementation (when GDCM_BUILD_TESTING is turned ON)
 * 2. the one from OpenSSL (when GDCM_USE_SYSTEM_OPENSSL is turned ON)
 *
 * In all other cases it will return an error
 */
//-----------------------------------------------------------------------------
class MD5Internals;
class GDCM_EXPORT MD5
{
public :
  MD5();
  ~MD5();

  static bool Compute(const char *buffer, unsigned long buf_len, char digest_str[33]);

  static bool ComputeFile(const char *filename, char digest_str[33]);

private:
  MD5Internals *Internals;
private:
  MD5(const MD5&);  // Not implemented.
  void operator=(const MD5&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmMD5_h
