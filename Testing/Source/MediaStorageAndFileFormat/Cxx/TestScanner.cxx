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
  (void)argc;
  (void)argv;
  
  gdcm::Directory d;
  unsigned int nfiles = d.Load( argv[1] );
  d.Print( std::cout );

  gdcm::Scanner s;
  gdcm::Tag t1(0x0020,0x000d);
  gdcm::Tag t2(0x0020,0x000e);
  s.AddTag( t1 );
  s.AddTag( t2 );
  bool b = s.Scan( d.GetFilenames() );
  s.Print( std::cout );

  return 0;
}

