// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11


#include <socket++/sockinet.h>

using namespace std;

int main(int ac, char** av)
{
	if (ac != 2 && ac != 3) {
		cerr << "USAGE: " << av[0] << " [ -l ] user_name\n";
		return 1;
	}
	
	iosockinet	sio (sockbuf::sock_stream);

	if (ac == 3) {
	    if (av[1][0] != '-' || av[1][1] != 'l') {
		cerr << "USAGE: " << av[0] << " [ -l ] user_name\n";
		return 1;
	    }
	    // use local whois server
	    sio->connect ("128.143.2.20", "whois", "tcp"); 
	    sio << av[2] << "\r\n" << flush;
	} else {
	    sio->connect ("nic.ddn.mil", "whois", "tcp");
	    sio << av[1] << "\r\n" << flush;
	}

	char buf[1024];
	while ( sio.getline(buf, 1023) ) cout << buf << endl;
	cout << endl;

	return 0;
}
