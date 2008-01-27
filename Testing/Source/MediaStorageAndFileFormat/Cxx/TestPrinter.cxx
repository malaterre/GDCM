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
#include "gdcmReader.h"
#include "gdcmPrinter.h"

#include "gdcmDataImages.h"

int TestPrint(const char *filename)
{
  gdcm::Reader r;
  r.SetFileName( filename );
  r.Read();

  gdcm::Printer p;
  p.SetFile( r.GetFile() );
  p.Print( std::cout );

  return 0;
}


int TestPrinter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestPrint(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestPrint( filename );
    ++i;
    }

  return r;
}

