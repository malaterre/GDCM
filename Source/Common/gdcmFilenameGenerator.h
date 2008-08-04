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
#ifndef __gdcmFilenameGenerator_h
#define __gdcmFilenameGenerator_h

// doc

#include "gdcmTypes.h"
#include <string>
#include <vector>


namespace gdcm
{
/** \class FilenameGenerator
 * \brief class to generate filenames based on a pattern (C-style)
 */

class GDCM_EXPORT FilenameGenerator
{
public:
  FilenameGenerator():Pattern(),Filenames() {}
  ~FilenameGenerator() {}
  // FIXME: already defines in gdcm::Directory
  typedef std::string FilenameType;
  typedef std::vector<FilenameType> FilenamesType;

  /// Set/Get pattern
  void SetPattern(const char *pattern) { Pattern = pattern; }
  const char *GetPattern() const { return Pattern.c_str(); }

  /// Generate (return success)
  bool Generate();

  /// Set/Get the number of filenames to generate
  void SetNumberOfFilenames(unsigned int nfiles);
  unsigned int GetNumberOfFilenames() const;

  /// Get a particular filename (call after Generate)
  const char * GetFilename(unsigned int n) const;

  /// Return all filenames 
  FilenamesType const & GetFilenames() const { assert( !Pattern.empty() ); return Filenames; }

private:
  FilenameType Pattern;
  FilenamesType Filenames;
};

} // end namespace gdcm

#endif //__gdcmFilenameGenerator_h
