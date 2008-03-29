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
#include <windows.h> /* SetConsoleTextAttribute */
//#include <ext/stdio_filebuf.h>
//typedef __gnu_cxx::stdio_filebuf<char> filebuf_gnu;

namespace gdcm
{

#if 0
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
#endif

namespace terminal
{

class ConsoleImp
{
private:
  HANDLE hConsoleHandle;
  //COORD ConsoleOutputLocation;
  CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
  WORD wNormalAttributes;
public:
  ConsoleImp(/*std::ostream &os*/)
  {
//	  if( &os == &std::cout)
    hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//	  if( &os == &std::cerr)
  //  hConsoleHandle = GetStdHandle(STD_ERRROR_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleHandle, &ConsoleInfo);
    wNormalAttributes = ConsoleInfo.wAttributes;
  }
  ~ConsoleImp()
  {
	  SetConsoleTextAttribute(hConsoleHandle, wNormalAttributes);
  }
//void set_attributes(const unsigned char *color) {
WORD get_attributes() {
	//CONSOLE_SCREEN_BUFFER_INFO scrbuf;
	GetConsoleScreenBufferInfo(hConsoleHandle, &ConsoleInfo);
	return ConsoleInfo.wAttributes;
}
  
#ifndef COMMON_LVB_REVERSE_VIDEO
#define COMMON_LVB_REVERSE_VIDEO   0x4000
#define COMMON_LVB_UNDERSCORE      0x8000
#endif

void set_attributes(int color) {

	static const colors[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };
	WORD wAttributes;
	//const char *t;

	//if (color[0] == '\x1b' && color[1] == '[')
	//	color += 2;

	//if (!('0' <= color[0] && color[0] <= '9')) {
	//	SetConsoleTextAttribute(ghstdout, wNormalAttributes);
	//	return;
	//}

	wAttributes = get_attributes();
	//t = color;
	int t = 1;
	//int mask = 0xFFFFFFFF;

	// http://swapoff.org/browser/todo/trunk/util/Terminal.cc
	// http://www.koders.com/cpp/fid5D5965EDC640274BE13A63CFEC649FA76F65A59D.aspx
	// http://cvs.4suite.org/viewcvs/4Suite/Ft/Lib/Terminal.py?rev=1.1&content-type=text/vnd.viewcvs-markup
	// http://linuxgazette.net/issue65/padala.html
	// https://svn.linux.ncsu.edu/svn/cls/branches/ncsu-gdm/pre-gdm-2.14/Xdefaults.old
	// http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/475116
	// http://techpubs.sgi.com/library/tpl/cgi-bin/getdoc.cgi?coll=linux&db=man&fname=/usr/share/catman/man4/console_codes.4.html
	// http://www.columbia.edu/kermit/ftp/k95/terminal.txt
	// http://www.codeproject.com/KB/cpp/Colored_Conslole_Messages.aspx
	// http://www.betarun.com/Pages/ConsoleColor/
	// http://support.microsoft.com/?scid=kb%3Ben-us%3B319883&x=20&y=8
	//http://www.dreamincode.net/code/snippet921.htm
	//http://www.codeproject.com/KB/cpp/Colored_Conslole_Messages.aspx
	//http://fabrizio.net/ccode/Old/20070427/Console.cpp
	//http://www.opensource.apple.com/darwinsource/10.4.8.x86/tcsh-46/tcsh/win32/console.c
	//http://msdn2.microsoft.com/en-us/library/ms682088(VS.85).aspx
	//
	while (t) {
		int n = color;
		t = 0;
		//int n = t & mask;
		//mask = (mask << 1) + 1;
		//mask /= 2;
		//std::cerr << "mask:" << std::hex << mask << std::endl;
		//if ((t = strchr(t, ';')))
		//	t++;

		if      (n == 0)				// Normal (default)
			wAttributes = wNormalAttributes;
		else if (n == 1)				// Bold
			wAttributes |= FOREGROUND_INTENSITY;
		else if (n == 4)				// Underlined
			wAttributes |= COMMON_LVB_UNDERSCORE;
		else if (n == 5)				// Blink (appears as BACKGROUND_INTENSITY)
			wAttributes |= BACKGROUND_INTENSITY;
		else if (n == 7)				// Inverse
			wAttributes |= COMMON_LVB_REVERSE_VIDEO;
		else if (n == 21)				// Not bold
			wAttributes &= ~FOREGROUND_INTENSITY;
		else if (n == 24)				// Not underlined
			wAttributes &= ~COMMON_LVB_UNDERSCORE;
		else if (n == 25)				// Steady (not blinking)
			wAttributes &= ~BACKGROUND_INTENSITY;
		else if (n == 27)				// Positive (not inverse)
			wAttributes &= ~COMMON_LVB_REVERSE_VIDEO;
		else if (30 <= n && n <= 37)	// Set foreground color
			wAttributes = (wAttributes & ~0x0007) | colors[n - 30];
		else if (n == 39)				// Set foreground color to default
			wAttributes = (wAttributes & ~0x0007) | (wNormalAttributes & 0x0007);
		else if (40 <= n && n <= 47)	// Set background color
			wAttributes = (wAttributes & ~0x0070) | (colors[n - 40] << 4);
		else if (n == 49)				// Set background color to default
			wAttributes = (wAttributes & ~0x0070) | (wNormalAttributes & 0x0070);
		else if (90 <= n && n <= 97)	// Set foreground color (bright)
			wAttributes = (wAttributes & ~0x0007) | colors[n - 90]
				| FOREGROUND_INTENSITY;
		else if (100 <= n && n <= 107)	// Set background color (bright)
			wAttributes = (wAttributes & ~0x0070) | (colors[n - 100] << 4)
				| BACKGROUND_INTENSITY;
		else							// (default)
			wAttributes = wNormalAttributes;
	}

	// Though Windows' console supports COMMON_LVB_REVERSE_VIDEO,
	// it seems to be buggy.  So we must simulate it.
	if (wAttributes & COMMON_LVB_REVERSE_VIDEO)
		wAttributes = (wAttributes & COMMON_LVB_UNDERSCORE)
			| ((wAttributes & 0x00f0) >> 4) | ((wAttributes & 0x000f) << 4);
	SetConsoleTextAttribute(hConsoleHandle, wAttributes);
}
  
  void SetAttribute(int att)
  {
    WORD attributes = 0;
    //attributes |= ConsoleInfo.wAttributes & color;
    //attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    //if(!hConsoleHandle) std::cerr << "error";
    //if( att & Attribute::fg )
    {
       std::cerr << "fg" << std::endl;
    }
    //else if( att & Attribute::bg )
    {
       std::cerr << "bg" << std::endl;
    }
    SetConsoleTextAttribute(hConsoleHandle, attributes);
    //std::cout << "test\n";
  }
# define KWSYS_TERMINAL_MASK_FOREGROUND \
  (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
# define KWSYS_TERMINAL_MASK_BACKGROUND \
  (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)
  void Reset()
  {
    WORD attributes = 0;
    //if( ConsoleInfo.wAttributes & FOREGROUND_INTENSITY )
    {
      attributes |= ConsoleInfo.wAttributes & KWSYS_TERMINAL_MASK_FOREGROUND;
    }
    /*
    if( ConsoleInfo.wAttributes & BACKGROUND_INTENSITY )
    {
      attributes |= ConsoleInfo.wAttributes & KWSYS_TERMINAL_MASK_BACKGROUND;
    }*/
      attributes |= ConsoleInfo.wAttributes & KWSYS_TERMINAL_MASK_BACKGROUND;
    SetConsoleTextAttribute(hConsoleHandle, attributes);
  }
};
// http://linuxgazette.net/issue65/padala.html
//  The Color Code:     <ESC>[{attr};{fg};{bg}m

	static ConsoleImp cimp;
std::string textcolor(int attr, int fg, int bg)
{
//char command[13];
//sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
//return command;
	cimp.SetAttribute(fg);
	return "";
}

std::string setfgcolor( Color c)
{
	cimp.set_attributes(30+c);
  //return textcolor(0,c,0);
	return "";
}
std::string setbgcolor( Color c )
{
	cimp.set_attributes(40+c);
	return "";
}

std::string resetcolor()
{
	cimp.Reset();
	return "";
}
std::string bold()
{
	return "bold";
}
std::string setattribute( Attribute att )
{
	//cimp.SetAttribute(fg);
	cimp.set_attributes(att);
	return "";
}

}


} // end namespace gdcm
