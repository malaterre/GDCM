// socket++ library. tsig-0.C
// Copyright (C) 1992-1996 Gnanasekaran Swaminathan <gs4t@virginia.edu>
//
// Permission is granted to use at your own risk and distribute this software
// in source and  binary forms provided  the above copyright notice and  this
// paragraph are  preserved on all copies.  This software is provided "as is"
// with no express or implied warranty.

#include <iostream>
#include <socket++/sig.h>
#include <unistd.h>

using namespace std;

  class hnd: public sig::hnd {
    public:
    int id;

    hnd (int signo): sig::hnd (signo), id (signo) {}
    hnd (int signo, int i): sig::hnd (signo), id (i) {}
    void operator () (int s) {
      cout << "handler for " << id << endl;
      cout << "Sleeping .." << endl;
      sleep (5);
      cout << "..finished" << endl;
	  if (sig::nal.ispending (s)) {
			cout << "Signal pendig" << endl;
		}
	
      // cout << "Pending signals = " << hex << sig::nal.pending () << dec << endl; // commented out by LN
			sigset_t set;
			for (unsigned int i=0; i<_SIGSET_NWORDS; i++) {
				cout << "sigset[" << i << "]: " << set.__val[i] << endl;
			}
			for (unsigned int i=1; i<15; i++) {
				cout << "ispending(" << i << "): " << sig::nal.ispending (i) << endl;
			}
      cout << "called by " << s << endl;
    }
  };

int main (int ac, char** av)
{

  hnd sterm0 (SIGTERM);
  hnd sterm1 (SIGTERM, SIGTERM * 100);
  hnd sint (SIGINT);
  hnd susr1 (SIGUSR1);
  hnd susr2 (SIGUSR2);
  hnd squit (SIGQUIT);

  /*
  sig::nal.set (SIGTERM, &sterm0);
  sig::nal.set (SIGTERM, &sterm1);
  sig::nal.set (SIGINT, &sint);
  sig::nal.set (SIGUSR1, &susr1);
  sig::nal.set (SIGUSR2, &susr2);
  sig::nal.set (SIGQUIT, &squit);
  */

	cout << "SIGSET_NWORDS: " << _SIGSET_NWORDS << endl;
  try {
    hnd illegal (300);
  }
  catch (sigerr e) {
    //cout << "sigerr exception thrown by illegal(300)\n";
		cout << "catched..." << endl;
	}

  sig::nal.mask (SIGTERM, SIGUSR1);
  sig::nal.mask (SIGTERM, SIGUSR2);

  pid_t pid = getpid ();

  cout << "send SIGUSR2\n";
  kill (pid, SIGTERM);

  sleep (20);
  sig::nal.unmask (SIGTERM, SIGUSR2);
  
  cout << "send SIGUSR2 again\n";
  kill (pid, SIGTERM);

  sleep (300);
  return 0;
}
