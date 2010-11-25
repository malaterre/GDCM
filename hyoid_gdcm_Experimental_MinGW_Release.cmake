# Client maintainer: inglis.dl gmail . com

set(CTEST_SITE "hyoid")
set(CTEST_BUILD_NAME "Win32-windowsVista-MingGW32-Release")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "MinGW Makefiles")
set(CTEST_DASHBOARD_ROOT "D:/Developer/Dashboards/Tests")
set(dashboard_binary_name "gdcm-build-release-experimental-mingw")
set(dashboard_model Experimental)
set(dashboard_root_name "D:/Developer/Dashboards/Tests")
set(dashboard_cache "
BUILD_TESTING:BOOL=ON
GDCM_BUILD_TESTING:BOOL=ON
CMAKE_BUILD_TYPE:STRING=Release
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_BUILD_EXAMPLES:BOOL=ON
GDCM_USE_VTK:BOOL=ON
VTK_DIR:PATH=D:/Developer/Releases/MinGW/SHARED/Install/lib/vtk-5.7
")

SET(CTEST_GIT_COMMAND "C:/cygwin/bin/git.exe")

SET (CTEST_ENVIRONMENT
  "PATH=C:/Qt/mingw/bin\;C:/Perl/site/bin\;C:/Perl/bin\;C:/Windows/system32\;C:/Windows\;C:/Windows/System32/Wbem\;C:/Program Files/CMake 2.6/bin"
  )

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
