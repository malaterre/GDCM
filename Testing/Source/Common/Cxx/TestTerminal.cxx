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
#include <windows.h>
#include <conio.h>
#include <stdio.h>

namespace term = gdcm::terminal;

int TestTerminal(int argc, char *argv[])
{
#if 0
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

#endif
  //std::cout << term::setfgcolor( term::black ) << "coucou black" << std::endl;
  //std::cout << term::setfgcolor( term::red )   << "coucou red" << std::endl;
  //std::cout << term::setfgcolor( term::blue ) << term::bold()   << "coucou red" << std::endl;
  std::cout << term::setattribute( term::bright ) << "bright" << std::endl;
  std::cout << term::setattribute( term::dim ) << "dim" << std::endl;
  std::cout << term::setattribute( term::underline ) << "underline" << std::endl;
  std::cout << term::setattribute( term::blink ) << "blink" << std::endl;
  std::cout << term::setattribute( term::reverse ) << "reverse" << std::endl;
  std::cout << term::setattribute( term::reset ) << "reset" << std::endl;
  std::cout << term::setfgcolor( term::black ) << "fg:black" << std::endl;
  std::cout << term::setfgcolor( term::red ) << "fg:red " << std::endl;
  std::cout << term::setfgcolor( term::green ) << "fg:green" << std::endl;
  std::cout << term::setfgcolor( term::yellow ) << "fg:yellow" << std::endl;
  std::cout << term::setfgcolor( term::blue ) << "fg:blue" << std::endl;
  std::cout << term::setfgcolor( term::magenta ) << "fg:magenta" << std::endl;
  std::cout << term::setfgcolor( term::cyan ) << "fg:cyan" << std::endl;
  std::cout << term::setfgcolor( term::white ) << "fg:white" << std::endl;
  std::cout << term::setattribute( term::reverse ) << term::setfgcolor( term::white ) << "fg:white" << std::endl;
  std::cout << term::setbgcolor( term::black ) << "bg:black" << std::endl;
  std::cout << term::setbgcolor( term::red ) << "bg:red " << std::endl;
  std::cout << term::setbgcolor( term::green ) << "bg:green" << std::endl;
  std::cout << term::setbgcolor( term::yellow ) << "bg:yellow" << std::endl;
  std::cout << term::setbgcolor( term::blue ) << "bg:blue" << std::endl;
  std::cout << term::setbgcolor( term::magenta ) << "bg:magenta" << std::endl;
  std::cout << term::setbgcolor( term::cyan ) << "bg:cyan" << std::endl;
  std::cout << term::setbgcolor( term::white ) << "bg:white" << std::endl;
  std::cout << term::setattribute( term::reset ) << "reset" << std::endl;
  std::cerr << term::setbgcolor( term::blue ) << "cerr:bg:blue" << std::endl;
  //std::cout << term::resetcolor()   << "after reset" << std::endl;
#if 0
  HANDLE hConsoleHandle;
  CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
  hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleHandle, &ConsoleInfo);
    WORD attributes = 0;
    attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsoleHandle, attributes);
    std::cout << "test again" << std::endl;
    WORD reset; 
    reset = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetConsoleTextAttribute(hConsoleHandle, reset);
#endif
    std::cout <<  "\33[31m" "rxvt" << std::endl;
  return 0;
}

