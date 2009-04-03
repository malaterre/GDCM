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
#ifndef __gdcmSHA1_h
#define __gdcmSHA1_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for SHA1 
 *
 */
//-----------------------------------------------------------------------------
class SHA1Internals;
class GDCM_EXPORT SHA1
{
public :
  SHA1();
  ~SHA1();

  static bool Compute(const char *buffer, unsigned long buf_len, char digest_str[20*2+1]);

private:
  SHA1Internals *Internals;
private:
  SHA1(const SHA1&);  // Not implemented.
  void operator=(const SHA1&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmSHA1_h
