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
#ifndef __gdcmTesting_h
#define __gdcmTesting_h

#include "gdcmTypes.h"

#include <iostream>

namespace gdcm
{
/**
 * \brief class for testing
 * \details this class is used for the nightly regression system for GDCM
 * It makes heavily use of md5 computation
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Testing
{
public :
  Testing() {};
  ~Testing() {};

  /// MD5 stuff
  /// digest_str needs to be at least : strlen = [2*16+1];
  /// string will be \0 padded. (md5 are 32 bytes long)
  static bool ComputeMD5(const char *buffer, const unsigned long buf_len,
    char *digest_str);
  static bool ComputeFileMD5(const char *filename, char *digest_str);

  /// Print
  void Print(std::ostream &os = std::cout);

  /// return the table of fullpath to gdcmData DICOM files:
  static const char * const * GetFileNames();
  static unsigned int GetNumberOfFileNames();
  static const char * GetFileName(unsigned int file);

  /// return the table that map the md5 (as in md5sum) of the Pixel Data associated
  /// to a filename
  typedef const char* const (*MD5DataImagesType)[2];
  static MD5DataImagesType GetMD5DataImages();
  static unsigned int GetNumberOfMD5DataImages();
  static const char * const * GetMD5DataImage(unsigned int file);
  static const char * GetMD5FromFile(const char *filepath);

  /// Return the GDCM DATA ROOT
  static const char * GetDataRoot();

  /// Return the GDCM DATA EXTRA ROOT
  static const char * GetDataExtraRoot();

  /// Return the GDCM PIXEL SPACING DATA ROOT (See David Clunie website for dataset)
  static const char * GetPixelSpacingDataRoot();

  /// NOT THREAD SAFE
  /// Returns the temp directory as used in testing needing to output data:
  static const char * GetTempDirectory(const char * subdir = 0);

  /// NOT THREAD SAFE
  static const char * GetTempFilename(const char *filename, const char * subdir = 0);
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmTesting_h
