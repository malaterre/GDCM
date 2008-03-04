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

int TestSystem(int, char *[])
{
	const char s1[] = "HELLO, wORLD !";
	const char s2[] = "Hello, World !";
	if( gdcm::System::StrCaseCmp(s1,s2) != 0 )
	{
		 return 1;
	}

  // struct stat {
  // off_t         st_size;     /* total size, in bytes */
  // }

  unsigned long size1 = sizeof(off_t);
  unsigned long size2 = sizeof(size_t);
  if( size1 != size2 ) return 1;

  return 0;
}
