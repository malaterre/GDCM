// tdunread.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <iostream>
#include <socket++/sockunix.h>
#include <unistd.h>
#include <stdio.h> // solaris2.3 perror is here
#include <sys/stat.h> // solaris 2.3 chmod is here
#include <errno.h>
#include <stdlib.h>

using namespace std;

void terminate (void) { exit (1); }
void unexpected (void) { abort (); }

int main(int ac, char** av)
{
  if (ac != 2) {
    cerr << "USAGE: " << av[0] << " socket_path_name\n";
    return 1;
  }
  
  isockunix su (sockbuf::sock_dgram);
  
  su->bind(av[1]);
  
  cout << "Socket name = " << av[1] << endl;
  
  if (chmod (av[1], 0777) == -1) {
    perror("chmod");
    return 1;
  }
  
  char buf[1024];
  int i;
  su >> i;
  cout << av[0] << ": " << i << " strings: ";
  while (i--) {
    su >> buf;
    cout << buf << ' ';
  }
  cout << endl;
  unlink(av[1]);
  
  return 0;
}
