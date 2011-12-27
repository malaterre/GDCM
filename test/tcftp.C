// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/ftp.h>
#include <unistd.h>

using namespace std;

int main (int ac, char** av)
{
  // this is an ftp client
  // It retrieves the file from the host
  if (ac != 4) {
    cerr << "USAGE: " << av [0] << " hostname user filename\n";
    return 1;
  }

  ftp f (&cout);

  // establish connection
  f->connect (av [1]);
  f->get_response (); // get the connection response

  // set access 
  f->user (av [2]);
  f->passwd (getpass ("passwd: "));

  // get help
  f->help ();

  // set representation type to image
  f->rep_type (ftp::rt_image);

  // list the home directory
  f->list ();

  // quit
  f->quit ();
}
    
