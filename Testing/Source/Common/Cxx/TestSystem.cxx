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
#include "gdcmSystem.h"
#include "gdcmFilename.h"
#include <iostream>
#include <string.h> // strlen

int TestSystem(int, char *[])
{
  const char s1[] = "HELLO, wORLD !";
  const char s2[] = "Hello, World !";
  if( gdcm::System::StrCaseCmp(s1,s2) != 0 )
    {
    return 1;
    }
  if( gdcm::System::StrNCaseCmp(s1,s2, strlen(s1)) != 0 )
    {
    return 1;
    }
  const char s3[] = "Hello, World ! ";
  if( gdcm::System::StrCaseCmp(s1,s3) == 0 )
    {
    return 1;
    }
  if( gdcm::System::StrNCaseCmp(s1,s3, strlen(s1)) != 0 )
    {
    return 1;
    }
  if( gdcm::System::StrNCaseCmp(s1,s3, strlen(s3)) == 0 )
    {
    return 1;
    }

  // struct stat {
  // off_t         st_size;     /* total size, in bytes */
  // }

  unsigned long size1 = sizeof(off_t);
  unsigned long size2 = sizeof(size_t);
  unsigned long size3 = sizeof(uintmax_t);
  unsigned long size4 = sizeof(std::streamsize);
  if( size1 > size2 )
    {
    std::cerr << "size_t is not approriate on this system" << std::endl;
    return 1;
    }
  if( size2 != size4 )
    {
    std::cerr << "size_t is diff from uintmax_t: " << size2 << " " << size4 << std::endl;
    return 1;
    }

  char datetime[18];
  int res = gdcm::System::GetCurrentDateTime(datetime);
  std::cerr << datetime << std::endl;

/*
 * I can do this kind of testing here since I know testing:
 * - cannot be installed (no rule in cmakelists)
 * - they cannot be moved around since cmake is not relocatable
 * thus this is safe to assume that current process directory is actually the executable output
 * path as computed by cmake:
 *
 * TODO: there can be trailing slash...
 */
  const char *path = gdcm::System::GetCurrentProcessFileName();
  gdcm::Filename fn( path );
//std::cerr << path << std::endl;
  if( strncmp(GDCM_EXECUTABLE_OUTPUT_PATH, fn.GetPath(), strlen(GDCM_EXECUTABLE_OUTPUT_PATH)) != 0 )
    {
    std::cerr << GDCM_EXECUTABLE_OUTPUT_PATH << "!=" << fn.GetPath() << std::endl;
    return 1;
    }
  // gdcmCommonTests
  const char exename[] = "gdcmCommonTests";
  if( strncmp(exename, fn.GetName(), strlen(exename)) != 0 )
    {
    std::cerr << exename << "!=" << fn.GetName() << std::endl;
    return 1;
    }
 
  return 0;
}
