// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


// for best accuracy, getTime is implemented platform dependent.
// to avoid a global include of windows.h, this is a separete file. 


#include "config.h"

#if defined(_WIN32)

#include <windows.h>


double getTime() 
{ 
	LARGE_INTEGER time;
	::QueryPerformanceCounter(&time);
	LARGE_INTEGER freq;
	::QueryPerformanceFrequency(&freq);

	return double(time.LowPart) * 1000.0/double(freq.LowPart);
}

#else

#include <sys/time.h>
double getTime() 
{ 	

	timeval t;
	gettimeofday(&t, 0);
	
	return (t.tv_sec * 1000000.0 + t.tv_usec) / 1000.0;	
}

#endif
