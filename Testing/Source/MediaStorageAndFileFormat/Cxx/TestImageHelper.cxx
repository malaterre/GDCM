/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageHelper.h"

int TestImageHelper(int, char *[])
{
  gdcm::ImageHelper sh;
  const double pos[] = { 0,0,0,
                         1,1,1};
  const double answer[3] = {1,1,1};
  
  std::vector<double> impos(pos,pos+6);
  std::vector<double> spacing;
  spacing.resize(3);
  if( !gdcm::ImageHelper::ComputeSpacingFromImagePositionPatient(impos, spacing) )
    {
    return 1;
    }
  std::cout << spacing[0] << std::endl;
  std::cout << spacing[1] << std::endl;
  std::cout << spacing[2] << std::endl;
  
  return 0;
}

