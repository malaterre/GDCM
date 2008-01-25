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
#ifndef __gdcmScanner_h
#define __gdcmScanner_h

#include "gdcmDirectory.h"
#include "gdcmTag.h"

#include <map>
#include <set>
#include <string>

namespace gdcm
{
/**
 * \brief Scanner
 */
class GDCM_EXPORT Scanner
{
public:
  Scanner():Values(),Filenames(),Mappings() {}
  ~Scanner();
  typedef std::map<const char*, const char*> StringToStringMap;
  typedef StringToStringMap FilenameToValue;
  //typedef StringToStringMap ValueToFilename;

  void AddTag( Tag const & t );

  bool Scan( Directory::FilenamesType const & filenames );

  void Print( std::ostream & os );

  typedef std::set< std::string > ValuesType;
  ValuesType const & GetValues() { return Values; }

  typedef std::map<Tag,FilenameToValue> MappingType;
  MappingType const & GetMappings() { return Mappings; }

private:
  // Will store all the value found:
  typedef std::set< Tag > TagsType;
  std::set< Tag > Tags;
  ValuesType Values;
  Directory::FilenamesType Filenames;
  std::map<Tag,FilenameToValue> Mappings;
};

} // end namespace gdcm

#endif //__gdcmScanner_h
