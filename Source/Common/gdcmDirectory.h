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
#ifndef __gdcmDirectory_h
#define __gdcmDirectory_h

#include "gdcmTypes.h"

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

namespace gdcm
{
/**
 * \brief Class for manipulation directories
 *
 * \note This implementation provide a cross platform implementation
 * for manipulating directores: basically traversing directories
 * and harvesting files
 *
 * \note 
 * will not take into account unix type hidden file
 * recursive option will not look into UNIX type hidden directory (those starting with a .)
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Directory
{
public :
  Directory() {}
  ~Directory() {}
  typedef std::string FilenameType;
  typedef std::vector<FilenameType> FilenamesType;

  void Print(std::ostream &_os = std::cout);

  /// Get the name of the toplevel directory
  FilenameType const &GetToplevel() const { return Toplevel; }

  /// Set/Get the file names within the directory
  FilenamesType const &GetFilenames() const {
    assert( !(Toplevel.empty()) && "Need to call Explore first" );
    return Filenames; }

  /// Return the Directories traversed
  FilenamesType const &GetDirectories() const { return Directories; }

  /// construct a list of filenames and subdirectory beneath directory: name
  unsigned int Load(FilenameType const &name, bool recursive = false) {
    Filenames.clear(); // clear previous
    Directories.clear(); // clear previous
    Toplevel = name;
    return Explore( Toplevel, recursive );
  }
  // \todo later: GLOB
  // The glob() function searches for all the pathnames matching pattern according to 
  // the rules used by the shell (see glob(7)).  No tilde expansion or parameter 
  // substitution is done; if you want these, use wordexp(3).
  // int Glob(...);

protected:
  /// Return number of file found when 'recursive'ly exploring directory `name`
  unsigned int Explore(FilenameType const &name, bool recursive);

private :
  /// List of file names
  FilenamesType Filenames;
  FilenamesType Directories;

  /// name of the toplevel directory to explore
  FilenameType Toplevel;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmDirectory_h
