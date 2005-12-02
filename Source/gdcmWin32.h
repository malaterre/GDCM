
#ifndef __gdcmWin32_h
#define __gdcmWin32_h

//#include "gdcmConfigure.h"


//-----------------------------------------------------------------------------
#if defined(_WIN32) && defined(BUILD_SHARED_LIBS)
  #ifdef gdcm_EXPORTS
    #define GDCM_EXPORT __declspec( dllexport )
  #else
    #define GDCM_EXPORT __declspec( dllimport )
  #endif
#else
  #define GDCM_EXPORT
#endif

//-----------------------------------------------------------------------------
#endif //__gdcmWin32_h
