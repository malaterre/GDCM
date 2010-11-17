# Client maintainer: mmroden gmail . com

set(CTEST_SITE "silverstreak")
set(CTEST_BUILD_NAME "Win32-windows7-vs9-2.1-Debug-x64")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Visual Studio 9 2008 Win64")
set(CTEST_DASHBOARD_ROOT "H:/src/dashboard/gdcm-dashboard/")
set(dashboard_binary_name "gdcm-build-debug-64-nightly")

SET(CTEST_GIT_COMMAND "C:/Program Files (x86)/Git/bin/git.exe")
SET(ENV{CFLAGS} "/W4")
SET(ENV{CXXFLAGS} "/W4")

macro(dashboard_hook_init)
  set( dashboard_cache "
    GDCM_BUILD_SHARED_LIBS:BOOL=OFF
    GDCM_BUILD_APPLICATIONS:BOOL=ON
    GDCM_BUILD_EXAMPLES:BOOL=ON
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
