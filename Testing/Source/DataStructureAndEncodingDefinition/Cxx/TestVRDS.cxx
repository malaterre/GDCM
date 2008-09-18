/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmVR.h"

#include <sstream>
#include <iostream>
#include <iomanip>


template <typename T, unsigned int MAXBYTES>
std::string TestVRDSFunc(const char *str)
{
  std::istringstream is( str );
  T d;
  is >> d;
  std::ostringstream os;
  os << std::setprecision(MAXBYTES);
  os << d;
  std::cout << std::setprecision(MAXBYTES);
  std::cout << d << std::endl;
  std::string copy = os.str();
  return copy;
}

/*
 * Test to make sure that double precision ieee 'double' is ok for DICOM VR = 'DS'
 */
int TestVRDS(int, char *[])
{
  const unsigned int dsmaxbytes = 16;
  const char str[dsmaxbytes+1] = "0.123456789123";
  std::string copy;

  // Let's demonstrate the float can easily fails;
  if( (copy = TestVRDSFunc<float,dsmaxbytes>(str)) == str )
    {
    std::cerr << "Float works:" << copy << " vs " << str << std::endl;
    return 1;
    }
  
  // Repeat with double, it works this time
  if( (copy = TestVRDSFunc<double,dsmaxbytes>(str)) != str )
    {
    std::cerr << "Double does not work:" << copy << " vs " << str << std::endl;
    return 1;
    }

  return 0;
}
