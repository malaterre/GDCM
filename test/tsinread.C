// tsinread.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/sockinet.h>
#include <unistd.h>

using namespace std;

static void process_input (iosockinet& s);

int main()
{
  sockinetbuf sin (sockbuf::sock_stream);
    
  sin.bind();
    
  cout << "localhost = " << sin.localhost() << endl
       << "localport = " << sin.localport() << endl;
    
  sin.listen();
    
  for(;;) {
    {
      iosockinet s (sin.accept());
      process_input(s);
    }
	
    // lets use select to find out whether a socket is ready
    if (!sin.is_readready(2)) {
      // the socket is not ready. Let us sleep for 1 sec.
      sleep(1);
    }
	
    iosockinet s2 (sin.accept());
    process_input(s2);
    break; // let us get out of here forever
  }
  return 0;
}

static void process_input(iosockinet& sio)
{
  char	buf[256];
  char*	p = buf;
    
  sio >> p;
    
  while (*p) {
    if (*p != '%')
      cout << *p;
    else
      switch (*++p) {
      case 'd': {
	int i;
	sio >> i;
	cout << i << ' ';
	sio << "INT ";
	break;
      }
      case 'f': {
	double d;
	sio >> d;
	cout << d << ' ';
	sio << "DOUBLE ";
	break;
      }
      case 's': {
	char str[256];
	sio >> str;
	cout << str << ' ';
	sio <<  "STRING ";
	break;
      }
      case 'c': {
	char c;
	sio >> c;
	cout << c << ' ';
	sio << "CHAR ";
	break;
      }
      case '%':
	cout << '%' << ' ';
	break;
      default:
	cout << '%' << *p;
      }
    p++;
  }
  sio << "received" << endl;
  cout << endl;
}


