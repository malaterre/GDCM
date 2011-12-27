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
  if (ac < 3) {
    cerr << "USAGE: " << av [0] << " remote-host portno string...\n";
    return 1;
  }

  int portno = atoi (av [2]);

  echo e(protocol::tcp);

  if (portno == 0)
    e->connect (av [1]);
  else
    e->connect (av [1], portno);

  cout << e->rfc_name () << ' ' << e->rfc_doc () << endl;

  for (int i = 0; i < ac; i++) {
    char buf [256];

    cout << "sending: " << av [i] << endl;

    e << av [i] << endl;

    e.getline (buf, 255);

    cout << "got back: " << buf << endl;
  }

  return 0;
}
