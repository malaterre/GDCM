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
#include "gdcmDirectory.h"
#include "gdcmTesting.h"

// dcmdump /path/to/image/*.dcm 2>&/dev/null| grep 0020 | grep "000e\|000d" | sort | uniq
//
// $ find   /images/ -type f -exec dcmdump -s +P 0010,0010 {} \; 

int TestScanner(int argc, char *argv[])
{
  const char *directory = gdcm::Testing::GetDataRoot();
  if( argc == 2 )
    {
    directory = argv[1];
    }
  gdcm::Directory d;
  unsigned int nfiles = d.Load( directory ); // no recursion
  d.Print( std::cout );
  std::cout << "done retrieving file list. " << nfiles << " files found." <<  std::endl;

  gdcm::Scanner s;
  const gdcm::Tag t1(0x0020,0x000d); // Study Instance UID
  const gdcm::Tag t2(0x0020,0x000e); // Series Instance UID
  const gdcm::Tag t3(0x0010,0x0010); // Patient's Name
  const gdcm::Tag t4(0x0004,0x5678); // DUMMY element
  s.AddTag( t1 );
  s.AddTag( t2 );
  s.AddTag( t3 );
  s.AddTag( t4 );
  bool b = s.Scan( d.GetFilenames() );
  if( !b )
    {
    std::cerr << "Scanner failed" << std::endl;
    return 1;
    }
  s.Print( std::cout );

  // Let's get the value for tag t1 in first file:
  gdcm::Scanner::MappingType const &mt = s.GetMappings();
  const char *filename = d.GetFilenames()[0].c_str();
  std::cout << "Mapping for " << filename << " is :" << std::endl;
  gdcm::Scanner::MappingType::const_iterator it = mt.find(filename);
  if( it == mt.end() )
    {
    return 1;
    }
  const gdcm::Scanner::TagToValue &tv = it->second;
  //const std::string &filename = d.GetFilenames()[0];
  gdcm::Scanner::TagToValue::const_iterator it2 = tv.find( t1 );
  if( t1 != it2->first ) return 1;
  std::cout << filename << " -> " << t1 << " = " << it2->second << std::endl;

  const gdcm::Directory::FilenamesType &filenames = d.GetFilenames();
{
  gdcm::Directory::FilenamesType::const_iterator it = filenames.begin();
  for(; it != filenames.end(); ++it)
    {
    const char *filename = it->c_str();
    const char *value =  s.GetValue( filename, t1 );
    if( value )
      {
      std::cout << filename << " has " << t1 << " = " << value << std::endl;
      }
    else
      {
      std::cout << filename << " has " << t1 << " = no value !" << std::endl;
      }
    }
}
/*
{
  std::vector<const char *> keys = s.GetKeys();
  for( std::vector<const char *>::const_iterator it = keys.begin(); it != keys.end(); ++it)
    {
    const char *filename = *it;
    const gdcm::Directory::FilenamesType::const_iterator it2 
      = std::find(filenames.begin(), filenames.end(), filename);
    if( it2 == filenames.end() )
      {
      return 1;
      }
    if( !s.IsKey( filename ) )
      {
      return 1;
      }
    }
}
*/
  

  return 0;
}

