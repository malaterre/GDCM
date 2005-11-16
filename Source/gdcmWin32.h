
#ifndef __GDCMTYPE_H
#define __GDCMTYPE_H

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

} //namespace gdcm
//-----------------------------------------------------------------------------
#endif
