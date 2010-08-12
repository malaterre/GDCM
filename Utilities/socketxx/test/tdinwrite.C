// tdinwrite.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/sockinet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int ac, char** av)
{
  if (ac < 3) {
    cerr << "USAGE: " << av[0] << " thostname port-number "
	 << "data ... " << endl;
    return 1;
  }

  osockinet osin (sockbuf::sock_dgram);

  osin->connect (av[1], atoi (av[2]));

  cout << "local: " << osin->localport() << ' ' << osin->localhost() << endl
       << "peer:  " << osin->peerport() << ' ' << osin->peerhost() << endl;

  // test socket options
  cout << "socket type = " << osin->gettype() << endl;
  cout << "socket linger time = " << osin->linger(1, 10).l_linger << endl;
  cout << "socket linger time = " << osin->linger(1, 0).l_linger << endl;
  cout << "socket linger time = " << osin->linger().l_linger << endl;
  // cout << "socket send bufsz = " << osin->sendbufsz() << endl;
  // cout << "socket recv bufsz = " << osin->recvbufsz() << endl;
  cout << "socket keepalive  = " << osin->keepalive(true) << endl;
  cout << "socket keepalive  = " << osin->keepalive(false) << endl;
  cout << "socket clearerror = " << osin->clearerror() << endl;
  cout << "socket debug = " << osin->debug(true) << endl;
  cout << "socket debug = " << osin->debug(false) << endl;
  cout << "socket reuse = " << osin->reuseaddr(true) << endl;
  cout << "socket reuse = " << osin->reuseaddr(false) << endl;

#if 0 // def __linux__
  int timeo = 0;
  osin->getopt(sockbuf::so_sndtimeo, &timeo, sizeof(timeo));
  cout << "socket sendtimeo = " << timeo << endl;
  osin->getopt(sockbuf::so_rcvtimeo, &timeo, sizeof(timeo));
  cout << "socket recvtimeo = " << timeo << endl;
#endif

  osin << ac-3; av += 3;
  while(*av) osin << *av++ << ' ';
  osin << endl;
	
  return 0;
}

	
	
