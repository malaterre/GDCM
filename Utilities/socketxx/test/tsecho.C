// This may look like C code, but it is really -*- C++ -*-

// tpopentest.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11


#include <socket++/echo.h>
#include <stdlib.h>

using namespace std;

int main (int ac, char** av)
{
  if (ac != 2) {
    cerr << "USAGE: " << av [0] << " portno\n";
    return 1;
  }

  echo server (protocol::tcp);
  server->serve_clients (atoi (av [1]));
  return 2;
}
