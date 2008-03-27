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
#include <iostream>
#include <fstream>
//#include <ext/stdio_filebuf.h>
//typedef __gnu_cxx::stdio_filebuf<char> filebuf_gnu;

namespace gdcm
{

bool Terminal::Setup(FILE *file) {return false;}

bool Terminal::Setup(std::ostream &os)
{
  std::streambuf* sbuf = os.rdbuf();
  std::filebuf* fbuf = dynamic_cast<std::filebuf*>(sbuf);
  if( fbuf )
    {
    //int t = fbuf->fd();
    //std::filebuf::__file_type * t = fbuf->_M_file;
    //filebuf_gnu *f = static_cast<filebuf_gnu*>(fbuf);
    //int fd = f->fd();
    //std::cout << fd << std::endl;
    return true;
    }
  return false;
}

#define GDCM_TERMINAL_VT100_NORMAL              "\33[0m"
#define GDCM_TERMINAL_VT100_BOLD                "\33[1m"
#define GDCM_TERMINAL_VT100_UNDERLINE           "\33[4m"
#define GDCM_TERMINAL_VT100_BLINK               "\33[5m"
#define GDCM_TERMINAL_VT100_INVERSE             "\33[7m"
#define GDCM_TERMINAL_VT100_FOREGROUND_BLACK    "\33[30m"
#define GDCM_TERMINAL_VT100_FOREGROUND_RED      "\33[31m"
#define GDCM_TERMINAL_VT100_FOREGROUND_GREEN    "\33[32m"
#define GDCM_TERMINAL_VT100_FOREGROUND_YELLOW   "\33[33m"
#define GDCM_TERMINAL_VT100_FOREGROUND_BLUE     "\33[34m"
#define GDCM_TERMINAL_VT100_FOREGROUND_MAGENTA  "\33[35m"
#define GDCM_TERMINAL_VT100_FOREGROUND_CYAN     "\33[36m"
#define GDCM_TERMINAL_VT100_FOREGROUND_WHITE    "\33[37m"
#define GDCM_TERMINAL_VT100_BACKGROUND_BLACK    "\33[40m"
#define GDCM_TERMINAL_VT100_BACKGROUND_RED      "\33[41m"
#define GDCM_TERMINAL_VT100_BACKGROUND_GREEN    "\33[42m"
#define GDCM_TERMINAL_VT100_BACKGROUND_YELLOW   "\33[43m"
#define GDCM_TERMINAL_VT100_BACKGROUND_BLUE     "\33[44m"
#define GDCM_TERMINAL_VT100_BACKGROUND_MAGENTA  "\33[45m"
#define GDCM_TERMINAL_VT100_BACKGROUND_CYAN     "\33[46m"
#define GDCM_TERMINAL_VT100_BACKGROUND_WHITE    "\33[47m"

void Terminal::ColorPrint(FILE * file, ColorType color, const char *str) const
{
}

void Terminal::ColorPrint(std::ostream & file, ColorType color, const char *str) const
{
  if( color == Terminal::Black )
    {
    file << GDCM_TERMINAL_VT100_FOREGROUND_BLACK << str;
    file << GDCM_TERMINAL_VT100_NORMAL;
    }
  else if( color == Terminal::Red )
    {
    file << GDCM_TERMINAL_VT100_FOREGROUND_RED << str;
    file << GDCM_TERMINAL_VT100_NORMAL;
    }
  else
    {
    file << "\33[" << (int)color << "m" << str;
    file << GDCM_TERMINAL_VT100_NORMAL;
    }
}



} // end namespace gdcm
