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
#ifndef __gdcmTesting_h
#define __gdcmTesting_h

#include "gdcmTypes.h"

#include <iostream>

namespace gdcm
{
/*
 * \brief Class for Testing
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Testing
{
public :
  Testing() {};
  ~Testing() {};

  void Print(std::ostream &_os = std::cout);

  static const char * const *GetFileNames();
  static unsigned int GetNumberOfFileNames();
  static const char * GetFileName(unsigned int file);

  typedef const char* const (*MD5DataImagesType)[2];
  static MD5DataImagesType GetMD5DataImages();
  static unsigned int GetNumberOfMD5DataImages();
  static const char * GetMD5FromFile(const char *filepath);

  static const char *GetDataRoot();
  static const char *GetTempDirectory();
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmTesting_h
