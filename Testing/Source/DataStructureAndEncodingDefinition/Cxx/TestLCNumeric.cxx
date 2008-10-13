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
#include "gdcmAttribute.h"

#include <stdlib.h> /* setenv */

int TestLCNumeric(int argc, char *argv[])
{
  //setenv("LC_NUMERIC", "fr_FR", 1);
  putenv("LC_NUMERIC=fr_FR");
  std::ostringstream os;
  double d = 1.2;
  os << d;
  std::string s = os.str();
  std::cout << s << std::endl;
  std::string::size_type pos_comma = s.find( "," );
  if( pos_comma != std::string::npos )
    {
    return 1;
    }
  std::string::size_type pos_dot = s.find( "." );
  if( pos_dot == std::string::npos )
    {
    return 1;
    }
  return 0;
}
