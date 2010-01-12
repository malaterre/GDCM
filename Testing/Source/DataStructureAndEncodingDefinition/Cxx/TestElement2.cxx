/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmElement.h"
#include "gdcmVR.h"

struct dummy
{
  unsigned short I[3];
};
//<entry group="0018" element="1624" retired="false" version="3">
//      <representation vr="US" vm="3"/>

template<int,int> struct TagToElement;
template<> struct TagToElement<0x0018,0x1624> {
  typedef gdcm::Element<gdcm::VR::US,gdcm::VM::VM3> Type;
};

int TestElement2(int, char *[])
{
  gdcm::Element<gdcm::VR::US, gdcm::VM::VM3> ref = {0,1,2};
  dummy d = {0,1,2};

  TagToElement<0x0018,0x1624>::Type t = {1,2,3};
  t.Print( std::cout );
  std::cout << std::endl;

  return 0;
}
