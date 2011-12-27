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
  Fork::suicide_signal (SIGTERM);

  Fork a(0, 1);
  
  print ("a", a.process_id ());

  if (a.is_child ()) {
    sleep (3000);
  } else if (a.is_parent ()) {
    Fork b (1, 1);
    print ("b", b.process_id ());
    {
      Fork c (b.is_parent (), 1);
      if (b.is_child ())
	print ("cchild", c.process_id ());
      else
	print ("cparent", c.process_id ());
      if (c.is_child ()) {
	sleep (3000);
	return 0;
      }
    }
    if (b.is_child ()) {
      sleep (120);
      return 0x8;
    }
  }

  return 0;
}
      
