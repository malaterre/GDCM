// tpipe.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/pipestream.h>
#include <iostream>

using namespace std;


int main(int ac, char** av)
{
  iopipestream p;

  if ( p.fork() ) {
    // I am the parent
    cout << "parent got: ";
    while (ac--) {
      char buf[32];
      buf [0] = 0;
      p << ac << endl;
      p >> buf;
      cout << buf << ' ';
    }
    cout << endl;
  } else {
    // I am the child
    int i;
    cout << "child got: ";
    while (p >> i) {
      p << av[i] << endl;
      cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}

	
		
			
