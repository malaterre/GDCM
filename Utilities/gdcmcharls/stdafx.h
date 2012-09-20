// stdafx.h

#ifndef STDAFX
#define STDAFX

#if defined(_WIN32)
#define CHARLS_IMEXPORT __declspec(dllexport)
#else
#if __GNUC__ >= 4
#define CHARLS_IMEXPORT __attribute__ ((visibility ("default")))
#endif
#endif

#include "util.h"


#endif
