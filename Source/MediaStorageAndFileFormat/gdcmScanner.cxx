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

namespace gdcm
{


Scanner::~Scanner()
{
}

void Scanner::AddTag( Tag const & t )
{
  Tags.insert( t );
}

bool Scanner::Scan( Directory::FilenamesType const & filenames )
{
  Directory::FilenamesType::const_iterator it = filenames.begin();
  for(; it != filenames.end(); ++it)
    {
    Reader reader;
    const char *filename = it->c_str();
    reader.SetFileName( filename );
    bool read = false;
    try
      {
      read = reader.Read();
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
      const DataSet & ds = reader.GetFile().GetDataSet();
      TagsType::const_iterator tag = Tags.begin();
      for( ; tag != Tags.end(); ++tag )
        {
        DataElement const & de = ds.GetDataElement( *tag );
        const ByteValue *bv = de.GetByteValue();
        //assert( VR::IsASCII( vr ) );
        assert( bv );
        std::string s( bv->GetPointer(), bv->GetLength() );
        s.resize( std::min( s.size(), strlen( s.c_str() ) ) );
        // Store the potentially new value:
        Values.insert( s );
        const char *value = Values.find( s )->c_str();
        // Keep the mapping:
        FilenameToValue &mapping = Mappings[*tag];
        mapping.insert(
          FilenameToValue::value_type(filename, value));
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
  TagsType::const_iterator tag = Tags.begin();
  for( ; tag != Tags.end(); ++tag )
    {
    os << "Tag: " << *tag << "\n";
    //const FilenameToValue &mapping = Mappings[*tag];
    const FilenameToValue &mapping = Mappings.find(*tag)->second;
    FilenameToValue::const_iterator it = mapping.begin();
    for( ; it != mapping.end(); ++it)
      {
      const char *filename = it->first;
      const char *value = it->second;
      os << filename << " -> " << value << "\n";
      }
    }
}

} // end namespace gdcm
