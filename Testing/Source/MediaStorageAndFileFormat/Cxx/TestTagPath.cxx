/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTagPath.h"

int TestTagPath(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  gdcm::TagPath tp;

  const char path[] = "/0010,0010";
  tp.ConstructFromString( path );

  tp.Print( std::cout );

  const char path2[] = "/0010,0011/1234,5678";
  tp.ConstructFromString( path2 );

  tp.Print( std::cout );


  return 0;
}

