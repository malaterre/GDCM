// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/smtp.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

int main (int ac, char** av)
{
  if (ac < 4) {
    cerr << "USAGE: " << av [0] << " host recipient files...\n";
    return 1;
  }

  smtp client (&cout);

  // establish connection
  client->connect (av [1]);
  client->helo ();

  // get help
  client->help ();

  // get the FROM address
  char    sender [256];
  passwd* pw = getpwuid( getuid() );
  sprintf(sender, "%s@%s", pw->pw_name, client->localhost());

  // send the files
  for (int i = 3; i < ac; i++) {
    client->mail (sender);
    client->rcpt (av [2]);
    client->data (av [i]);
    client->rset ();
  }

  // finally quit
  client->quit ();

  return 0;
}
