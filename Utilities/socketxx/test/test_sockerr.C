/* test_sockerr.cxx
 * -- Copyright (C) 2002 by Herbert Straub
 *
 * Permission is granted to use at your own risk and distribute this software
 * in source and  binary forms provided  the above copyright notice and  this
 * paragraph are  preserved on all copies.  This software is provided "as is"
 * with no express or implied warranty.
 */


#include <socket++/sockstream.h>

using namespace std;

void f1 ();

int main (int argc, char *argv[]) 
{
	sockerr err (4711, "Test Error");

	try {
		throw (err);
	} catch (sockerr e) {
		cout << "Catching sockeer with " << e.serrno () << " and "
		     << e.operation () << endl;
	} catch (...) {
		cout << "Catching void" << endl;
	}

	try {
		f1();
	}  catch (sockerr e) {
		cout << "Catching sockeer with " << e.serrno () << " and "
		     << e.operation () << endl;
	} catch (...) {
		cout << "Catching void" << endl;
	}
}

void f1 ()
{
	throw (sockerr (311, "Test Error", "f1"));
}
