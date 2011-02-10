# Client maintainer: setupgdcm.sh

#set(CTEST_SITE "todo")
#set(CTEST_BUILD_NAME "todo")
#set(CTEST_CMAKE_GENERATOR "todo")

macro(dashboard_hook_init)
  set( dashboard_cache "
    GDCM_BUILD_SHARED_LIBS:BOOL=ON
    GDCM_BUILD_TESTING:BOOL=ON
    GDCM_BUILD_APPLICATIONS:BOOL=ON
    GDCM_BUILD_EXAMPLES:BOOL=ON
    GDCM_USE_VTK:BOOL=OFF
    GDCM_WRAP_PYTHON:BOOL=OFF
    GDCM_WRAP_CSHARP:BOOL=OFF
    GDCM_WRAP_JAVA:BOOL=OFF
    GDCM_USE_SYSTEM_OPENSSL:BOOL=OFF
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
