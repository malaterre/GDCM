/* Export macros for shared libraries */

#ifndef vtkgdcmModule_h
#define vtkgdcmModule_h

#include "vtkABI.h"
#include "gdcmConfigure.h"

#if defined(GDCM_BUILD_SHARED_LIBS)
# if defined(vtkgdcm_EXPORTS)
#  define VTKGDCM_EXPORT VTK_ABI_EXPORT
# else
#  define VTKGDCM_EXPORT VTK_ABI_IMPORT
# endif
#else
# define VTKGDCM_EXPORT
#endif

#endif
