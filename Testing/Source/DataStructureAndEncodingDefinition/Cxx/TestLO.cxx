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
#include "gdcmLO.h"
#include <iostream>

int TestLO(int argc, char *argv[])
{
  gdcm::LO lo = "hello world !";
  if( !lo.IsValid() ) return 1;

  const char str[] = "this is LO1 \\this is LO2 \\ this is LO 3 ";
  gdcm::LO lo1, lo2, lo3;
  std::stringstream ss;
  ss << str;
  ss >> lo1;
  ss.get();
  std::cout << lo1 << std::endl;
  ss >> lo2;
  ss.get();
  std::cout << lo2 << std::endl;
  ss >> lo3;
  ss.get();
  std::cout << lo3 << std::endl;

  return 0;
}

