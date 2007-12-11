/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDictEntry.h"

int TestDictEntry(int, char *[])
{
  gdcm::DictEntry de(0,0,0);
  std::cout << sizeof(de) << std::endl;

  gdcm::PrivateDictEntry pde(0,0,0);
  std::cout << sizeof(pde) << std::endl;

  return 0;
}
