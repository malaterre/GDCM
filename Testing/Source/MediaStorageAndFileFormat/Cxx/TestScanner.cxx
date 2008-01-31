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

// dcmdump /path/to/image/*.dcm 2>&/dev/null| grep 0020 | grep "000e\|000d" | sort | uniq

int TestScanner(int argc, char *argv[])
{
  if( argc < 2 )
    {
    std::cerr << "Need a directory" << std::endl;
    return 1;
    }
  gdcm::Directory d;
  unsigned int nfiles = d.Load( argv[1] );
  //d.Print( std::cout );
  std::cout << "done retrieving file list" << std::endl;

  gdcm::Scanner s;
  const gdcm::Tag t1(0x0020,0x000d);
  const gdcm::Tag t2(0x0020,0x000e);
  s.AddTag( t1 );
  s.AddTag( t2 );
  bool b = s.Scan( d.GetFilenames() );
  if( !b )
    {
    std::cerr << "Scanner failed" << std::endl;
    return 1;
    }
  //s.Print( std::cout );

  // Let's get the value for tag t1 in first file:
  gdcm::Scanner::MappingType const &mt = s.GetMappings();
  std::cout << "Mapping for " << t1 << " is :" << std::endl;
  gdcm::Scanner::MappingType::const_iterator it = mt.find(t1);
  if( it == mt.end() )
    {
    return 1;
    }
  const gdcm::Scanner::FilenameToValue &tv = it->second;
  const std::string &filename = d.GetFilenames()[0];
  gdcm::Scanner::FilenameToValue::const_iterator it2 = tv.find( filename.c_str() );
  std::cout << it2->first << " -> " << t1 << " = " << it2->second << std::endl;

  return 0;
}

