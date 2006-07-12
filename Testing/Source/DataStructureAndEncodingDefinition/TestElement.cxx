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
#include "gdcmElement.h"

#define TPI 3.1415926535897931

namespace gdcm
{
  
int TestFL()
{
  Element<VR::FL, VM::VM1> a = { TPI };
  a.Print( std::cout );
  std::cout << std::endl;

  Element<VR::FL, VM::VM8> b = 
    { 0,1,2,3,4,5,6,7 };
  b.Print( std::cout );
  std::cout << std::endl;

  return 0;
}

int TestFD()
{
  Element<VR::FD, VM::VM1> a = { TPI };
  std::ostringstream os;
  a.Print( os );
  const std::string st = os.str(); // important
  const char *s = st.c_str();
  std::cout << s << std::endl;
  //double t = *reinterpret_cast<const double*>(*s);
  //std::cout << t << std::endl;

  Element<VR::FD, VM::VM8> b; 
  double array[] = { 1,2,3,4,5,6,7,9 };
  b = reinterpret_cast<Element<VR::FD, VM::VM8>& >( array );
  b.Print( std::cout );
  std::cout << std::endl;

  return 0;
}

int TestAS()
{
  Element<VR::AS, VM::VM1> a = { "019Y" };
  a.Print( std::cout );
  std::cout << std::endl;

  return 0;
}

}

int TestElement(int , char *[])
{
  int r = 0;
  r += gdcm::TestFL();
  r += gdcm::TestFD();
  r += gdcm::TestAS();

  return r;
}

