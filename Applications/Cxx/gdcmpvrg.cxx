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
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <string.h>

// forward declare
extern "C" {
int pvrgmain(int argc, char *argv[]);
}

int main(int argc, char *argv[])
{
  if( argc < 1 )
    {
    return 1;
    }
  const int pvrgargc = 7;
  static char *pvrgargv[pvrgargc+1];
  pvrgargv[0] = 0;
  static char args1[] = "-d";
  static char args2[] = "-s";
  static char args3[] = "-g";
  static char args4[] = "gdcmtmpfile.raw";
  pvrgargv[1] = args1;
  pvrgargv[2] = args2;
  pvrgargv[3] = argv[1];
  pvrgargv[4] = args3;
  FILE *dummy = tmpfile();
  if( !dummy ) return 1;
  int fd = fileno(dummy);
  if( !fd ) return 1;

  //off_t p = lseek(fd, 0, SEEK_END);
  //std::cout << " p:" << p << " err: " << strerror(errno) << std::endl;

  static char fdstr[256];
  sprintf(fdstr, "%d", fd);
  pvrgargv[5] = fdstr;
  pvrgargv[6] = args4;
  pvrgargv[7] = 0;
  int r = pvrgmain(pvrgargc, pvrgargv);
  std::cout << " done "  << std::endl;

  fseek(dummy, 0L, SEEK_END);
  long s = ftell(dummy);
  std::cout << r << " ftell:" << s << std::endl;
  //off_t p = lseek(fd, 0, SEEK_END);
  //std::cout << " p:" << p << " err: " << strerror(errno) << std::endl;

  return r;
}
