/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmStringStream.h"

#include <iostream>

int TestStringStream(int, char *[])
{
  gdcm::StringStream ss;
  const char s[] = "GDCM";
  ss.Write(s, strlen(s));
  std::cout << ss.Str() << std::endl;

  return 0;
}
