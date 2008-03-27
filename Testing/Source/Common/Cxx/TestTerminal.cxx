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
#include "gdcmTerminal.h"

#include <iostream>

int TestTerminal(int argc, char *argv[])
{
  gdcm::Terminal term;

  FILE * file1 = stdout;
  //term.Setup( file1 );
  term.ColorPrint( file1, gdcm::Terminal::Black, "this is black\n" );

  std::ostream &file2 = std::cout;
  //term.Setup( file2 );
  term.ColorPrint( file2, gdcm::Terminal::Red, "this is red\n" );
  //term.ColorPrint( file2, gdcm::Terminal::ColorType(38), "this is 38\n" );
  for(int i =0; i < 60; ++i)
    {
    std::ostringstream os;
    os << "this is " << i << std::endl;
    std::string s = os.str();
    term.ColorPrint( file2, gdcm::Terminal::ColorType(i), s.c_str() );
    }

  return 0;
}

