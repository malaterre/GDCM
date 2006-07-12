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
#include "gdcmImageReader.h"

#include "gdcmDataImages.h"

int TestImageRead(const char* filename)
{
  gdcm::ImageReader reader;

  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read image from file: " << filename << std::endl;
    return 1;
    }

  //reader.GetPointer();
  std::cerr << "Success to read image from file: " << filename << std::endl;

  return 0;
}

int TestImageReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestImageRead(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestImageRead( filename );
    ++i;
    }

  return r;
}
