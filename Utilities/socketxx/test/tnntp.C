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

using namespace std;

static int send_cmd(const char*, iosockstream&);
static int get_text(istream&);

int main()
{
	iosockinet     sio(sockbuf::sock_stream);
	sio->connect("localhost", "nntp", "tcp");

	send_cmd(0, sio);
	
	send_cmd("HELP", sio); get_text(sio);
	send_cmd("QUIT", sio);

	return 0;
}

int send_cmd(const char* cmd, iosockstream& s)
{
	if (cmd) s << cmd << "\r\n" << flush;

	char buf[256];
	s.getline(buf, 255);

	cout << buf << endl;

	if (buf[0] == '4' || buf[1] == '5') return 1;
	return 0;
}

int get_text(istream& s)
{
	char buf[256];
	while (s.getline(buf, 255))
		if (buf[0] == '.') {
			if (buf[1] == '.') cout << buf+1 << endl;
			else return 0;
		}else
			cout << buf << endl;
	return 1;
}
		
