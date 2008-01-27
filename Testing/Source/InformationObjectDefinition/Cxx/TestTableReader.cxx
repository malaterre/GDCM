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
#include "gdcmTableReader.h"

// generated file:
#include "gdcmTables.h"

void TestReadTable(const char *filename)
{
  gdcm::TableReader tr;
  tr.SetFilename(filename);
  tr.Read();
}

int TestTableReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestReadTable(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmTables[i]) )
    {
    TestReadTable( filename );
    ++i;
    }

  return 0;
}

