// tsockpair.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/pipestream.h>

using namespace std;

int main(int ac, char** av)
{
  iopipestream p(sockbuf::sock_dgram);

  if (p.fork()) {
    // I am the Parent
    p << ac << endl;
    while (*av) {
      p << *av++ << ' ';
    }
    p << endl;

    char buf[128];
    p.getline(buf,127);
    cout << "Parent: " << buf << endl;
  } else {
    // I am the Child
    int cnt=0;
    int	i;
    char buf[32];
		
    p >> i;
    cout << "Child: " << i << ": ";
    while (i--){
      p >> buf;
      cout << buf << ' ';
      cnt++;
    }
    cout << endl;

    p << "Child received " << cnt << " strings\n" << flush;
  }
  return 0;
}
