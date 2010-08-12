// socket++ library. thostnames.C
// Copyright (C) 2002 Herbert Straub
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 1.2 2002-07-25 Herbert Straub
// 	Test bind and improved Error Handling


#include <socket++/sockinet.h>
#include <ctype.h>
#include <string.h>

using namespace std;

static void get_text (iosockstream& s);

class test : public iosockinet
{
	public:
		test () : iosockinet (sockbuf::sock_stream) {
			cout << "Constructor rdbuf: " << (unsigned int) rdbuf() << endl;
		}
};

int main(int ac, char** av)
{
  iosockinet sio(sockbuf::sock_stream);
  test t;


  if (ac != 4) {
    cerr << "USAGE: " << av[0] << " toServer service bindAddr\n";
    return 1;
  }

  sio.rdbuf()->setname ("Testsocket");
  cout << "rdbuf: " << (unsigned int) sio.rdbuf() << "\n";
  cout << "socketname: " << sio.rdbuf()->getname() << endl;

  try {
  sockinetaddr addrInterface (av[3]);
  sockinetaddr addrServer (av[1], av[2]);
  sio->bind (addrInterface);
  sio->connect (addrServer);
  } catch (sockerr e) {
	cout << "Catched sockerr while in connect" << endl;
	cout << "errno: " << e.serrno() << endl;
	cout << "errtext: " << e.errstr () << endl;
	cout << "Operation: " << e.operation () << endl;
	sio.setstate(ios::badbit);
  }
  catch (...) {
	  cout << "Catchall Zweig" << endl;
	  return 1;
  }

  cout << "good: " << sio.good() << endl;

  try {
	sio->keepalive (55);
	cout << "Keepalive: " << sio->keepalive() << endl;
  } catch (sockerr e) {
	cout << "Catched sockerr in keepalive" << endl;
	cout << "errno: " << e.serrno() << endl;
	cout << "errtext: " << e.errstr () << endl;
	cout << "Operation: " << e.operation () << endl;
	sio.setstate(ios::badbit);
  }

  sio << "help" << "\r\n" << flush;
  get_text (sio);

  return 0;
}

void get_text(iosockstream& s)
{
  char buf[1024];
  int tmo = s->recvtimeout(30); // wait for 30 sec before timing out

  if (s.getline (buf, 1023))
    cout << buf << endl;

  if (strncmp (buf, "BEGIN", 5) == 0)
    while (s.getline (buf, 1023)) {
      cout << buf << endl;
      if (strncmp (buf, "END", 3) == 0) break;
    }
  else
    while (s.getline (buf, 1023)) {
      cout << buf << endl;
      if (!isspace (buf [0])) break;
    }
  if ( !s.eof() ) s.clear();
  s->recvtimeout(tmo); //reset timeout to the previous value
}
