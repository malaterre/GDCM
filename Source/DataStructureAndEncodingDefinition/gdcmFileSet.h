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
#ifndef __gdcmFileSet_h
#define __gdcmFileSet_h

#include "gdcmFile.h"
#include <vector>

namespace gdcm
{
/**
 * \brief
 * File-set: A File-set is a collection of DICOM Files (and possibly non-DICOM Files)
 * that share a common naming space within which File IDs are unique.
 */
class GDCM_EXPORT FileSet
{
public:
  FileSet():Files() {}
  typedef std::string FileType;
  typedef std::vector<FileType> FilesType;

  /// \deprecated. Does nothing
  void AddFile(File const & ) {}

  /// Add a file 'filename' to the list of files. Return true on success, false in case filename could not
  /// be found on system.
  bool AddFile(const char *filename);

  void SetFiles(FilesType const &files);
  FilesType const &GetFiles() const {
    return Files; 
  }

private:
  FilesType Files;
};

} // end namespace gdcm

#endif //__gdcmFileSet_h
