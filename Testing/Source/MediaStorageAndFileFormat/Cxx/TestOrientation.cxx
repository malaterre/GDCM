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
#include "gdcmOrientation.h"

int TestOrientation(int, char *[])
{
  gdcm::Orientation o;
  double dircos[] = { 0, 1, 0, 0, 1, 0 };
  gdcm::Orientation::OrientationType type = gdcm::Orientation::GetType(dircos);
  return 0;
}
