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
#include "gdcmScanner.h"
#include "gdcmReader.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"

namespace gdcm
{


Scanner::~Scanner()
{
}

void Scanner::ClearTags()
{
  Tags.clear();
}

void Scanner::AddTag( Tag const & t )
{
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  const DictEntry &entry = dicts.GetDictEntry( t );
  // Is this tag an ASCII on ?
  if( entry.GetVR() & VR::VRASCII )
    {
    Tags.insert( t );
    }
  else if( entry.GetVR() == VR::INVALID )
    {
    gdcmWarningMacro( "Only tag with known VR are allowed. Tag " << t << " will be discarded" );
    }
  else
    {
    assert( entry.GetVR() & VR::VRBINARY );
    gdcmWarningMacro( "Only ASCII VR are supported for now. Tag " << t << " will be discarded" );
    }
}

bool Scanner::IsKey( const char * filename ) const
{
  Directory::FilenamesType::const_iterator it = std::find(Filenames.begin(), Filenames.end(), filename);
  if( it == Filenames.end() )
    {
    gdcmErrorMacro( "The file: " << filename << " was not scanned" );
    return false;
    }
  // Look for the file in Mappings table:
  MappingType::const_iterator it2 = Mappings.find(filename);
  return it2 != Mappings.end();
}

bool Scanner::Scan( Directory::FilenamesType const & filenames )
{
  // Is there at least one tag ?
  if( Tags.empty() ) return true;
  //if( filenames.empty() ) return true;

  // Prepare hash table:
  Mappings.clear();
  Mappings[""]; // Create a fake table for dummy file

  // Make our own copy:
  Filenames = filenames;

  // Find the tag with the highest value (get the one from the end of the std::set)
  TagsType::const_reverse_iterator it1 = Tags.rbegin();
  const Tag & last = *it1;

  Directory::FilenamesType::const_iterator it = Filenames.begin();
  for(; it != Filenames.end(); ++it)
    {
    Reader reader;
    const char *filename = it->c_str();
    assert( filename );
    reader.SetFileName( filename );
    bool read = false;
    try
      {
      // Start reading all tags, including the 'last' one:
      read = reader.ReadUpToTag(last);
      }
    catch(std::exception & ex)
      {
      gdcmWarningMacro( "Failed to read:" << filename << " with ex:" << ex.what() );
      }
    catch(...)
      {
      gdcmWarningMacro( "Failed to read:" << filename  << " with unknown error" );
      }
    if( read )
      {
      // Keep the mapping:
      TagToValue &mapping = Mappings[filename];

      const DataSet & ds = reader.GetFile().GetDataSet();
      TagsType::const_iterator tag = Tags.begin();
      for( ; tag != Tags.end(); ++tag )
        {
        if( ds.FindDataElement( *tag ) )
          {
          std::string s;
          DataElement const & de = ds.GetDataElement( *tag );
          const ByteValue *bv = de.GetByteValue();
          //assert( VR::IsASCII( vr ) );
          if( bv ) // Hum, should I store an empty string or what ?
            {
            s = std::string( bv->GetPointer(), bv->GetLength() );
            s.resize( std::min( s.size(), strlen( s.c_str() ) ) );
            }
          // Store the potentially new value:
          Values.insert( s );
          assert( Values.find( s ) != Values.end() );
          const char *value = Values.find( s )->c_str();
          assert( value );
          mapping.insert(
            TagToValue::value_type(*tag, value));
          }
        }
      }
    }
  return true;
}

void Scanner::Print( std::ostream & os ) const
{
  os << "Values:\n";
  ValuesType::const_iterator it = Values.begin();
  for( ; it != Values.end(); ++it)
    {
    os << *it << "\n";
    }
  os << "Mapping:\n";
  Directory::FilenamesType::const_iterator file = Filenames.begin();
  for(; file != Filenames.end(); ++file)
    {
    const char *filename = file->c_str();
    bool b = IsKey(filename);
    const char *comment = !b ? "could not be read" : "could be read";
    os << "Filename: " << filename << " (" << comment << ")\n";
    //const FilenameToValue &mapping = Mappings[*tag];
    if( Mappings.find(filename) != Mappings.end() )
      {
      const TagToValue &mapping = GetMapping(filename);
      TagToValue::const_iterator it = mapping.begin();
      for( ; it != mapping.end(); ++it)
        {
        const Tag & tag = it->first;
        const char *value = it->second;
        os << tag << " -> [" << value << "]\n";
        }
      }
    }
}

Scanner::TagToValue const & Scanner::GetMapping(const char *filename) const
{
//  assert( Mappings.find(filename) != Mappings.end() );
  if( Mappings.find(filename) != Mappings.end() )
    return Mappings.find(filename)->second;
  return Mappings.find("")->second; // dummy file could not be found
}

/*
std::vector<const char *> Scanner::GetKeys() const
{
  std::vector<const char *> keys;

  Directory::FilenamesType::const_iterator file = Filenames.begin();
  for(; file != Filenames.end(); ++file)
    {
    const char *filename = file->c_str();
    MappingType::const_iterator it = Mappings.find(filename);
    if ( it != Mappings.end() )
      {
      keys.push_back( filename );
      }
    }
  assert( keys.size() <= Filenames.size() );
  return keys;
}
*/

const char* Scanner::GetValue(const char *filename, Tag const &t) const
{
  TagToValue const &ftv = GetMapping(filename);
  if( ftv.find(t) != ftv.end() )
    {
    return ftv.find(t)->second;
    }
  return NULL;
}

} // end namespace gdcm
