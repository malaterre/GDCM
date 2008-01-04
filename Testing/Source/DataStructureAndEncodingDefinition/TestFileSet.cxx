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
#include "gdcmFileSet.h"
#include "gdcmFile.h"

int TestFileSet(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  gdcm::FileSet fs;
  gdcm::File f1;
  gdcm::File f2;
  fs.AddFile( f1 );
  fs.AddFile( f2 );

  return 0;
}

