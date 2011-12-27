// tpopen.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992,1993,1994 Gnanasekaran Swaminathan <gs4t@virginia.edu>
// 
// Permission is granted to use at your own risk and distribute this software
// in source and binary forms provided the above copyright
// notice and this paragraph are preserved on all copies.
// This software is provided "as is" with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/pipestream.h>
#include <unistd.h>

using namespace std;

int main()
{
  char buf[128];

  ipipestream ipopen("./tpopentest -o");
  cout << "Got from ipopen: ";
  while(ipopen >> buf)
    cout << buf << ' ';
  cout << endl;
	
  opipestream opopen("./tpopentest -i");
  opopen << "this is sent to tpopentest" << endl;

  iopipestream iopopen("./tpopentest -b");
  iopopen << "echo test one two three" << endl;
  cout << "Result from iopopen: ";
  while (iopopen >> buf) cout << buf << ' ';
  cout << endl;

  return 0;
}
