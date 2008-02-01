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

  void Print( std::ostream & os ) const;

  typedef std::set< std::string > ValuesType;
  ValuesType const & GetValues() const { return Values; }

  typedef std::map<Tag,FilenameToValue> MappingType;
  MappingType const & GetMappings() const { return Mappings; }

  FilenameToValue const & GetMapping(Tag const &t) const;

  const char* GetValue(Tag const &t, const char *filename) const;

private:
  // Will store all the value found:
  typedef std::set< Tag > TagsType;
  std::set< Tag > Tags;
  ValuesType Values;
  Directory::FilenamesType Filenames;
  std::map<Tag,FilenameToValue> Mappings;
};

#if 0
class FilenameToValueExtractor
{
public:
  FilenameToValueExtractor(Scanner::FilenameToValue &ftv):FTV(ftv) {}
  const char *GetValue(const char *filename) {
    Scanner::FilenameToValue &mapping = FTV;
    std::ostream &os = std::cout;
    Scanner::FilenameToValue::const_iterator it = mapping.begin();
    for( ; it != mapping.end(); ++it)
      {
      const char *filename = it->first;
      const char *value = it->second;
      os << filename << " -> " << value << "\n";
      }

    /*Scanner::FilenameToValue::const_iterator*/ it = FTV.find(filename);
    //assert( it != FTV.end() );
    //assert( strcmp(it->first, filename) == 0 );
    return it->second;
  }
private:
  Scanner::FilenameToValue & FTV;
};
#endif

} // end namespace gdcm

#endif //__gdcmScanner_h
