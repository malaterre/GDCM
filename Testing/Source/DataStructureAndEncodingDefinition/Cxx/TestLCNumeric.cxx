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
#include "gdcmAttribute.h"

#include <stdlib.h> /* setenv */
#include <locale.h>


int TestLCNumeric(int argc, char *argv[])
{
  //setenv("LC_NUMERIC", "fr_FR", 1);
  //const char ss[] = "LC_NUMERIC=fr_FR";
  //setlocale(LC_NUMERIC,"C");
  char *l = setlocale(LC_NUMERIC,"fr_FR.UTF-8");
  if( !l )
    {
    std::cerr << "Could not set LC_NUMERIC" << std::endl;
    return 1;
    }
  //char *copy = strdup(ss);
  //putenv(copy);
  //free(copy);
  std::ostringstream os;
  double d = 1.2;
  os << d;
  std::string s = os.str();
  std::cout << "s:" << s << std::endl;
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
