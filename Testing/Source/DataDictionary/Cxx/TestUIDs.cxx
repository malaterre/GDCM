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
#include "gdcmUIDs.h"

#include <iostream>

int TestUIDs(int, char *[])
{
  gdcm::UIDs uids;
  // uid_1_2_840_10008_5_1_4_1_1_2_1 = 117, // Enhanced CT Image Storage
  static const char* s = gdcm::UIDs::GetUIDString( gdcm::UIDs::uid_1_2_840_10008_5_1_4_1_1_2_1 );
  std::cout << s << std::endl;
  static const char* n = gdcm::UIDs::GetUIDName( gdcm::UIDs::uid_1_2_840_10008_5_1_4_1_1_2_1 );
  std::cout << n << std::endl;

  return 0;
}
