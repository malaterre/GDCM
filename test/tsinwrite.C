// tsinwrite.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11
//
// 2003-04-26 Herbert Straub: try-catch block on connect (test sockerr)

#include <socket++/sockinet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int ac, char** av)
{
    if (ac < 3) {
	cerr << "USAGE: " << av[0] << " machinename port "
	     << "format-string data...\n";
	return 1;
    }
    
    iosockinet	sio (sockbuf::sock_stream);
    try {
    	sio->connect(av [1], atoi (av [2]));
    }
    catch (sockerr e) {
    	    cout << "sockerr!!" << endl;
	    cout << "errno: " << e.serrno () << endl;
	    cout << "operation: " << e.operation () << endl;
	    cout << "errstr: " << e.errstr () << endl;
	    return 1;
    }
    //  sio->shutdown(sockbuf::shut_read);
    
    // 	cout << "local port = " << sio->localport() << endl
    // 	     << " peer port = " << sio->peerport() << endl
    // 	     << "local host = " << sio->localhost() << endl
    // 	     << " peer host = " << sio->peerhost() << endl;
    
    av += 3;
    while (*av) sio << *av++ << ' '; // space is neccessary
    sio << endl; // endl to flush output
    
    char buf[256];
    while (sio >> buf) cout << buf << ' ';
    cout << endl;
    
    
    // 	sio << "%f%d%c " // space is necessary
    // 	    << 236.9 << ' '
    // 	    << 56 << ' '
    // 	    << 'c' << endl; // endl to flush output

    return 0;
}
