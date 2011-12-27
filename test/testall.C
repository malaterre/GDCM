// testall.cc. Test for -*- C++ -*- socket library
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.
//
// Version: 12Jan97 1.11

#include <socket++/pipestream.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(int ac, char** av)
{
  char	buf[256];
  int	portno;
  char	thostname[64];
  
  ipipestream tdunread("./tdunread /tmp/soc");
  tdunread.getline(buf, 255);
  cout << buf << endl;
  ipipestream tdunwrite("./tdunwrite /tmp/soc mary had a little lamb");
  while ( tdunread.getline(buf, 255) ) cout << buf << endl;
  cout << endl;
  
  ipipestream tdinread("./tdinread");
  tdinread >> buf >> buf >> thostname >> buf >> buf >> portno;
  tdinread.getline(buf, 255);
  sprintf(buf, "./tdinwrite %s %d mary had a little lamb",
	  thostname, portno);
  ipipestream tdinwrite(buf);
  while ( tdinread.getline(buf, 255) ) cout << buf << endl;
  tdinwrite.getline(buf, 255);
  tdinwrite.getline(buf, 255);
  while ( tdinwrite.getline(buf, 255) ) cout << buf << endl;
  cout << endl;
  
  ipipestream tsunread("./tsunread /tmp/soc");
  tsunread.getline(buf, 255);
  cout << buf << endl;
  ipipestream tsunwrite("./tsunwrite /tmp/soc mary had a little lamb");
  while ( tsunread.getline(buf, 255) ) cout << buf << endl;
  cout << endl;
  
  ipipestream tsinread("./tsinread");
  tsinread >> buf >> buf >> thostname >> buf >> buf >> portno;
  tsinread.getline(buf, 255);
  sprintf(buf, "./tsinwrite %s %d %%d%%s%%f 356 haha 23.5",
	  thostname, portno);
  ipipestream tsinwrite1(buf);
  sprintf(buf, "./tsinwrite %s %d %%s%%c oooiiii !",
	  thostname, portno);
  cout << "sleeping for 3 sec\n";
  sleep(3);
  ipipestream tsinwrite2(buf);
  while ( tsinread.getline(buf, 255) ) cout << "tsinread: " << buf << endl;
  while ( tsinwrite1.getline(buf, 255) )
    cout << "tsinwrite1: " << buf << endl;
  while ( tsinwrite2.getline(buf, 255) )
    cout << "tsinwrite2: " << buf << endl;
  cout << endl;
  
  ipipestream tpipe("./tpipe mary had a little lamb");
  while ( tpipe.getline(buf, 255) ) cout << "tpipe " << buf << endl;
  cout << endl;
  
  ipipestream tsockpair("./tsockpair mary had a little lamb");
  while ( tsockpair.getline(buf, 255) )
    cout << "tsockpair " << buf << endl;
  cout << endl;
  
  ipipestream tpopen ("./tpopen");
  while ( tpopen.getline(buf, 255) )
    cout << "tpopen " << buf << endl;
  cout << endl;
  
  ipipestream twhois("./twhois .knuth,donald");
  cout <<"twhois:\n";
  while ( twhois.getline(buf, 255) ) cout << buf << endl;
  cout << endl;
  
  ipipestream thost("./thostnames uvaarpa.virginia.edu");
  cout << "thostnames:\n";
  while ( thost.getline(buf, 255) ) cout << buf << endl;
  cout << endl;
  
  return 0;
}

