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
#ifndef __gdcmScanner_h
#define __gdcmScanner_h

#include "gdcmDirectory.h"
#include "gdcmTag.h"

#include <map>
#include <set>
#include <string>

#include <string.h> // strcmp

namespace gdcm
{
/**
 * \brief Scanner
 * \todo
 * This filter is dealing with both VRASCII and VRBINARY element, thanks to the help of gdcm::StringFilter
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

  /// struct to map a filename to a value
  /// Implementation note:
  /// all std::map in this class will be using const char * and not std::string
  /// since we are pointing to existing std::string (hold in a std::vector)
  /// this avoid an extra copy of the byte array.
  /// Tag are used as Tag class since sizeof(tag) <= sizeof(pointer)
  typedef std::map<Tag, const char*> TagToValue;
  //typedef std::map<Tag, ConstCharWrapper> TagToValue; //StringMap;
  //typedef TagToStringMap TagToValue;
  typedef TagToValue::value_type TagToValueValueType;

  /// Add a tag that will need to be read. Those are root level skip tags
  void AddTag( Tag const & t );
  void ClearTags();

  /// Add a tag that will need to be skipped. Those are root level skip tags
  void AddSkipTag( Tag const & t );
  void ClearSkipTags();

  /// Start the scan !
  bool Scan( Directory::FilenamesType const & filenames );

  /// Print result
  void Print( std::ostream & os ) const;

  /// Check if filename is a key in the Mapping table.
  /// returns true only of file can be found, which means
  /// the file was indeed a DICOM file that could be processed
  bool IsKey( const char * filename ) const;

  /// Return the list of filename that are key in the internal map,
  /// which means those filename were properly parsed
  Directory::FilenamesType GetKeys() const;

  // struct to store all the values found:
  typedef std::set< std::string > ValuesType;

  /// Get all the values found (in lexicographic order)
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
  typedef MappingType::const_iterator ConstIterator;
  ConstIterator Begin() const { return Mappings.begin(); }
  ConstIterator End() const { return Mappings.end(); }

  /// Mappings are the mapping from a particular tag to the map, mapping filename to value:
  MappingType const & GetMappings() const { return Mappings; }

  /// Get the std::map mapping filenames to value for file 'filename'
  TagToValue const & GetMapping(const char *filename) const;

  /// Retrieve the value found for tag: t associated with file: filename
  /// This is meant for a single short call. If multiple calls (multiple tags)
  /// should be done, prefer the GetMapping function, and then reuse the TagToValue
  /// hash table.
  const char* GetValue(const char *filename, Tag const &t) const;

private:
  // struct to store all uniq tags in ascending order:
  typedef std::set< Tag > TagsType;
  std::set< Tag > Tags;
  std::set< Tag > SkipTags;
  ValuesType Values;
  Directory::FilenamesType Filenames;

  // Main struct that will hold all mapping:
  MappingType Mappings;

  double Progress;
};

/*
 * HACK: I need this temp class to be able to manipulate a std::map from python,
 * swig does not support wrapping of simple class like std::map...
 */
class PythonTagToValue
{
public:
  PythonTagToValue(Scanner::TagToValue const &t2v):Internal(t2v),it(t2v.begin()) {}
  const Scanner::TagToValueValueType& GetCurrent() const { return *it; }
  const Tag& GetCurrentTag() const { return it->first; }
  const char *GetCurrentValue() const { return it->second; }
  void Start() { it = Internal.begin(); }
  bool IsAtEnd() const { return it == Internal.end(); }
  void Next() { ++it; }
private:
  const Scanner::TagToValue& Internal;
  Scanner::TagToValue::const_iterator it;
};


} // end namespace gdcm

#endif //__gdcmScanner_h
