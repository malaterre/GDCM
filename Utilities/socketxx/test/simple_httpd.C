/* simple_httpd.C
 * -- Copyright (C) 2003 by Herbert Straub
 *  
 * Permission is granted to use at your own risk and distribute this software
 * in source and  binary forms provided  the above copyright notice and  this
 * paragraph are  preserved on all copies.  This software is provided "as is"
 * with no express or implied warranty.
 */

/*
 * This little program implements a very simple http server (only for
 * testing purposes). It usess: iosockinet, sockbuf, Fork.
 */

#include <config.h>
#include <socket++/fork.h>
#include <socket++/sockinet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif

using namespace std;

int process_request (iosockinet *sock);
void get_filesize (const char *name, string &buffer);

int main (int argc, char **argv)
{
	sockinetbuf sin (sockbuf::sock_stream);
	Fork *pF;

	sin.bind ();

	cout << "localhost = " << sin.localhost() << endl;
	cout << "localport = " << sin.localport() << endl;

	sin.listen ();

	for (;;) {
		iosockinet *sock;
		sock = new iosockinet (sin.accept ());
		sockaddr_in *remote_sock = sock->rdbuf()->peeraddr().addr_in();
		cout << "socksockaddr_in.addr() = " << remote_sock << endl;
		cout << "port: " << ntohs(remote_sock->sin_port) << endl;
		cout << "addr: " << hex << inet_ntoa(remote_sock->sin_addr) << endl;
		cout << "peerhost: " << sock->rdbuf()->peerhost() << endl;
		pF = new Fork (0, 1);
		if (pF->is_child ()) {
			sock->rdbuf()->keepalive (1);
			process_request (sock);
			return (0);
		}
	}
}

int process_request (iosockinet *sock)
{
	string buffer;
	string filename; 
	ifstream file;

	try {
	while (1) {
		getline (*sock, buffer);
		buffer[buffer.length()-1] = '\n';
		cout << "buffer: " << buffer << endl;
		if (sock->eof())
			break;
		// g++ < 3.0 : strncmp !!
		if (strncmp (buffer.c_str(), "quit", 4) == 0)
		//if (buffer.compare (0, 4, "quit") == 0)
			break;
		if (buffer.length() == 0)
			break;
		if (buffer[0] == '\n')
			break;
		// g++ < 3.0 : strncmp !!
		if (strncmp (buffer.c_str(), "GET", 4) == 0)
		//if (buffer.compare (0, 4, "GET") == 0)
			filename.assign (buffer, 4, buffer.rfind (" HTTP")-3);
	}
	}
	catch (sockerr s) {
		cout << "catched " << endl;
		goto END;
	}
	
	//filename.insert (0, ".");
	filename.replace (filename.length()-1, 1, "");
	cout << "Filename: " << filename << endl;
	file.open (filename.c_str());
	if (file.bad() || !file.is_open() || !file.good()) {
		cout << "Error opening file: " << filename << endl;
		goto END;
	}
	*sock << "HTTP/1.1 200 OK\r\n";
	*sock << "Server: socket++ Testserver\r\n";
	get_filesize (filename.c_str(), buffer);
	*sock << "Content-Length: " << buffer << "\r\n";
	*sock << "Connection: close\r\n";
	*sock << "Content-Type: plain/text; charset=iso-8859-1\r\n";
	*sock << "\r\n";
	sock->flush();
	try {
		for (getline(file, buffer); !file.eof(); getline(file,buffer)) {
			cout << "Sending Buffer: " << buffer << endl;
			*sock << buffer << "\r\n";
		}
		sock->flush();
	}
	catch (sockerr e) {
		cout << "Catched sockerr" << endl;
	}
	file.close ();
END:
	try {
		sock->rdbuf()->shutdown(sockbuf::shut_readwrite);
	}
	catch (...) 
	{
		// if the client break the connection, then
		// the shutdown method throws sockerr
	}
	delete sock;

	return 0;
}

void get_filesize (const char *name, string &buffer)
{
	struct stat buf;
#ifdef HAVE_SSTREAM
      stringstream sb;
#else
      strstream sb;
#endif

	if (stat (name, &buf) == -1) 
		buf.st_size = 0;
	sb << buf.st_size;
	buffer = sb.rdbuf()->str();
}
