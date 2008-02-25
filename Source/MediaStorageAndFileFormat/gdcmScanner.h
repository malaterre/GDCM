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
 * \todo
 * For now I am only dealing with VRASCII elements, this would seriously slow down to do
 * interpretation of other stuff (FIXME: need double check that)
 * 
 * \warning: IMPORTANT In case of file where tags are not ordered, the output will be garbage
 *
 * \note: implementation details. All values are stored in a std::set of std::string. Then the *address*
 * of the cstring underlying the std::string is used in the std::map
 */
class GDCM_EXPORT Scanner
{
public:
  Scanner():Values(),Filenames(),Mappings() {}
  ~Scanner();

  // struct to map a filename to a value
  // Implementation note:
  // all std::map in this class will be using const char * and not std::string
  // since we are pointing to existing std::string (hold in a std::vector)
  // this avoid an extra copy of the byte array.
  // Tag are used as Tag class since sizeof(tag) <= sizeof(pointer)
  typedef std::map<Tag, const char*> TagToStringMap;
  typedef TagToStringMap TagToValue;

  // Add a tag that will need to be read
  void AddTag( Tag const & t );
  void ClearTags();

  // Start the scan !
  bool Scan( Directory::FilenamesType const & filenames );

  // Print result
  void Print( std::ostream & os ) const;

  // Check if filename is a key in the Mapping table.
  // returns true only of file can be found, which means
  // the file was indeed a DICOM file that could be processed
  bool IsKey( const char * filename ) const;

  // Return the list of filename that are key in the internal map,
  // which means those filename were properly parsed
  //std::vector<const char *> GetKeys() const;

  // struct to store all the values found:
  typedef std::set< std::string > ValuesType;

  // Get all the values found (in lexicographic order)
  ValuesType const & GetValues() const { return Values; }

  /* ltstr is CRITICAL, otherwise pointers value are used to do the key comparison */
  struct ltstr
    {
    bool operator()(const char* s1, const char* s2) const
      {
      return strcmp(s1, s2) < 0;
      }
    };
  typedef std::map<const char *,TagToValue, ltstr> MappingType;
  // Mappings are the mapping from a particular tag to the map, mapping filename to value:
  MappingType const & GetMappings() const { return Mappings; }

  // Get the std::map mapping filenames to value for tag 't'
  TagToValue const & GetMapping(const char *filename) const;

  // Retrieve the value found for tag: t associated with file: filename
  const char* GetValue(const char *filename, Tag const &t) const;

private:
  // struct to store all uniq tags in ascending order:
  typedef std::set< Tag > TagsType;
  std::set< Tag > Tags;
  ValuesType Values;
  Directory::FilenamesType Filenames;

  // Main struct that will hold all mapping:
  MappingType Mappings;
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
