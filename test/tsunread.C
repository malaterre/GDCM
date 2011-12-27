// tsunread.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/sockunix.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

using namespace std;

#if defined (__alpha) && defined (__DECCXX)
extern "C" int chmod (const char*, int);
#endif

int main(int ac, char** av)
{
	if (ac != 2) {
		cerr << "USAGE: " << av[0] << " socket_path_name\n";
		return 1;
	}
	
	sockunixbuf 	su (sockbuf::sock_stream);

	su.bind (av[1]);
	cout << "Socket name = " << av[1] << endl;

	if (chmod(av[1], 0777) == -1) {
		perror("chmod");
		return 1;
	}

	su.listen (3);
	iosockunix iosun (su.accept());
	
	char        buf[1024];
	
	iosun << av[0] << ' ' << av[1] << endl;

	while ( iosun >> buf ) cout << av[0] << ": " << buf << endl;
		
	unlink (av[1]);
	return 0;
}

