// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11


#include <fstream>
#include <socket++/sockinet.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

static int send_cmd(iosockstream&, const char* cmd=0);

int main(int ac, char** av)
{
    if (ac < 3) {
	cerr << "USAGE: " << av[0] << " recipient-email-addr files...\n";
	return 1;
    }
    
    char         rcpt[512];
    char         sender[512];
    iosockinet   sio(sockbuf::sock_stream);
    sio->connect(sio->localhost(), "smtp", "tcp");
    
    send_cmd(sio, 0);
    send_cmd(sio, "HELO");
    
    
    sprintf(rcpt, "RCPT TO:%s", av[1]);
    
    passwd* pw = getpwuid( getuid() );
    sprintf(sender, "MAIL FROM:<%s@%s>", pw->pw_name, sio->localhost());
    
    for (int i=2; i < ac; i++) {
	send_cmd(sio, sender);
	send_cmd(sio, rcpt);
	send_cmd(sio, "DATA");
	sio << "\r\n------------------------" << av[i]
	    << "------------------------\r\n" << flush;
	
	ifstream cin(av[i]);
	char buf[512];
	while(cin.getline(buf, 511)) {
	    if (buf[0] == '.' && buf[1] == 0) {
		cerr << av[0]
		     << ": char '.' on a line of its own\n";
		return 1;
	    }
	    sio <<  buf << "\r\n" << flush;
	}
	sio << "\r\n.\r\n" << flush;
	send_cmd(sio, 0);
    }
    send_cmd(sio, "QUIT");
}

int send_cmd(iosockstream& s, const char* cmd)
{
    char buf[256];
    if (cmd) s << cmd << "\r\n" << flush;
    s.getline(buf, 255);
    cout << buf << endl;
    return 0;
}
