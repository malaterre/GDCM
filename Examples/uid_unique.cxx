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
#include "gdcmUIDGenerator.h"

#include <iostream>
#include <string>
#include <set>

int main()
{
  gdcm::UIDGenerator uid;
  std::set<std::string> uids;
  uint64_t c = 0;
  while(1)
  {
    const char *unique = uid.Generate();
    //std::cout << unique << std::endl;
    if( c % 1000 )
    {
            std::cout << "c=" << c << std::endl;
    }
    ++c;
    if ( uids.count(unique) == 1 )
    {
            std::cerr << "Failed with: " << unique << std::endl;
            return 1;
    }
    uids.insert( unique );
  }
  return 0;
}

