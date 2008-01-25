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
#include "gdcmUID.h"

#include <iostream>
#include <string>
#include <set>

int TestUIDValid()
{
  gdcm::UID uid( "" );
  uid.SetRoot( "1.2.3.4.0.0.1" );
  const char *s = uid.
}

int TestUID(int argc, char *argv[])
{
  gdcm::UID uid;
  std::cout << gdcm::UID::GetGDCMUID() << std::endl;
  std::cout << uid.GetRoot() << std::endl;
  if( strcmp( gdcm::UID::GetGDCMUID(), uid.GetRoot() ) != 0 )
    {
    return 1;
    }
  uid.SetRoot( "1" );
  if( strcmp( gdcm::UID::GetGDCMUID(), uid.GetRoot() ) == 0 )
    {
    return 1;
    }

/*
  std::string s0 = "123456";
  std::cout << (s0.c_str() + s0.find_first_not_of('0')) << std::endl;
  std::string s1 = "0123456";
  std::cout << (s1.c_str() + s1.find_first_not_of('0')) << std::endl;
  std::string s2 = "00123456";
  std::cout << (s2.c_str() + s2.find_first_not_of('0')) << std::endl;
  std::string s3 = "000";
  if( s3.find_first_not_of('0') != std::string::npos )
    std::cout << (s3.c_str() + s3.find_first_not_of('0')) << std::endl;
*/

  // Threading issue, make sure that two different UIDs cannot generate same UID
  gdcm::UID uid1;
  gdcm::UID uid2;
  const unsigned int n = 100;
  std::set<std::string> uids;
  for(unsigned int i = 0; i < n; ++i)
    {
    const char *unique1 = uid1.GenerateUniqueUID();
    const char *unique2 = uid2.GenerateUniqueUID();
    if( !unique1 || !unique2 ) return 1;
    std::cout << unique1 << std::endl;
    std::cout << unique2 << std::endl;
    if ( uids.count(unique1) == 1 )
      {
      std::cerr << "Already found: " << unique1 << std::endl;
      return 1;
      }
    uids.insert( unique1 );
    if ( uids.count(unique2) == 1 )
      {
      std::cerr << "Already found: " << unique2 << std::endl;
      return 1;
      }
    uids.insert( unique2 );
    if( strcmp(unique1 , unique2 ) == 0 )
      {
      // That would be very bad !
      return 1;
      }
    }

  return 0;
}
