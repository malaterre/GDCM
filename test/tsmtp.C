// socket++ library. tsmtp.C
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11
// 2003-03-06 Herbert Straub: variable from and to

#include <socket++/sockinet.h>
#include <stdio.h>
#include <string>

using namespace std;

static void send_cmd(iosockstream&, const char* cmd=0);
static void get_text(iosockstream&);

int main(int ac, char** av)
{
  if (ac != 4) {
    cerr << "USAGE: " << av[0] << " hostname from to\n";
    return 1;
  }
    
  try {
  iosockinet sio (sockbuf::sock_stream);
  sio.rdbuf()->setname ("smtp socket");
  string buffer;
    
  sio->connect(av[1], "smtp", "tcp");
    
  //send_cmd(sio, 0);
  send_cmd(sio, "HELO kelvin.seas.virginia.edu");
  send_cmd(sio, "HELP");
  buffer = "MAIL FROM: ";
  buffer += av[2];
  send_cmd(sio, buffer.c_str());
    
  buffer = "RCPT TO: ";
  buffer += av[3];
  send_cmd(sio, buffer.c_str());
    
  send_cmd(sio, "DATA");
  cout << "terminate your input with cntrl-D\n\n";
  while(getline(cin, buffer)) {
    if (buffer[0] == '.') sio << '.';
    sio <<  buffer << "\r\n";
  }
  sio << "\r\n.\r\n" << flush;
  send_cmd(sio, 0);
    
    
  send_cmd(sio, "HELP");
    
  send_cmd(sio, "QUIT");
  }
  catch (sockerr err) {
	  cout << "catched"<< endl;
	  cout << "catched sockerr: " << err.serrno() 
	       << " : " << err.operation ()
	       << endl;
  }
  catch (...) {
	  cout << "unknown exception" << endl;
  }

  return 0;
}

void send_cmd(iosockstream& s, const char* cmd)
{
  if (cmd) {
    s << cmd << "\r\n" << flush;
  }
  get_text (s);
}

void get_text(iosockstream& s)
{
  string buffer;
  int tmo = s->recvtimeout(2); // wait for 1 sec before timing out
  try { // FIXME: Straub debug
  	while ( getline(s, buffer) ) {
    		if (buffer[0] == '.' && buffer[1] == '\r' && buffer[2] == '\n')
			break;
    	cout << buffer << endl;
  	}
  }
  catch (sockerr e) {
	  cout << "catched sockerr" << endl;
  }
  if ( !s.eof() ) s.clear();
  s->recvtimeout(tmo); //reset timeout to the previous value
}
