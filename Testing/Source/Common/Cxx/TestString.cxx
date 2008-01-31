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
#include "gdcmString.h"
#include <iostream>

int TestString(int argc, char *argv[])
{
  gdcm::String s = "coucou";
  std::cout << s << std::endl;

  const char str[] = "WINDOW1\\WINDOW2\\WINDOW3";
  //const size_t lenstr = strlen(str);

  gdcm::String ms1, ms2, ms3;
  std::stringstream ss;
  ss << str;
  ss >> ms1;
  ss.get(); // discard backslash
  std::cout << ms1 << std::endl;
  if( ms1 != "WINDOW1" ) return 1;
  ss >> ms2;
  ss.get();
  std::cout << ms2 << std::endl;
  if( ms2 != "WINDOW2" ) return 1;
  ss >> ms3;
  ss.get();
  std::cout << ms3 << std::endl;
  if( ms3 != "WINDOW3" ) return 1;

  // we are at the end:
  if( ss ) return 1;

  return 0;
}

