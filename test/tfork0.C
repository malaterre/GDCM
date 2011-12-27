// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <iostream>
#include <socket++/fork.h>

using namespace std;

static void print (char* name, pid_t child)
{
  if (child) {
    cerr << "Parent " << getppid () << "; "
      << name << ' ' << getpid () << "; Child " << child << ";\n";
  } else if (0) {
    cerr << "Parent " << getppid () << "; "
      << name << "'s child " << getpid () << ";\n";
  }
}

int main (int ac, char** av)
{
  Fork A (1, 1);
  
  print ("A", A.process_id ());
  if (A.is_child ()) {
    sleep (120);
    return 0x8;
  }
  sleep (30);
  return 0;
}
    
