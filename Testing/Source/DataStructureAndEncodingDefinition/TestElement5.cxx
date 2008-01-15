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
#include "gdcmElement.h"
#include "gdcmVR.h"

#include <sstream>

int TestElement5(int , char *[])
{
  gdcm::Element<gdcm::VR::DS, gdcm::VM::VM1_n> spacing;
  const char strspacing[] = "1.2345\\6.7890";
  std::stringstream ss;
  ss.str( strspacing );
  unsigned int len = 2 * sizeof(float);
  gdcm::VM vm = gdcm::VM::VM2;
  gdcm::VR vr = gdcm::VR::DS;
  if( len != vr.GetSizeof() * vm.GetLength() )
    {
    return 1;
    }
  spacing.SetLength( len );
  spacing.Read( ss );
  std::cout << spacing.GetValue() << std::endl;
  std::cout << spacing.GetValue(1) << std::endl;

  return 0;
}
