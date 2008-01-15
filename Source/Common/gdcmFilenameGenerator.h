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

// It's a source
class GDCM_EXPORT FilenameGenerator
{
public:
  FilenameGenerator() {}
  ~FilenameGenerator() {}
  // FIXME: already defines in gdcm::Directory
  typedef std::string FilenameType;
  typedef std::vector<FilenameType> FilenamesType;

  void SetPattern(const char *pattern) { Pattern = pattern; }
  const char *GetPattern() const { return Pattern.c_str(); }

  bool Generate();

  void SetNumberOfFilenames(unsigned int nfiles);
  unsigned int GetNumberOfFilenames() const;
  const char * GetFilename(unsigned int n) const;

  FilenamesType const & GetFilenames() const { assert( !Pattern.empty() ); return Filenames; }

private:
  FilenameType Pattern;
  FilenamesType Filenames;
};

} // end namespace gdcm

#endif //__gdcmFilenameGenerator_h
