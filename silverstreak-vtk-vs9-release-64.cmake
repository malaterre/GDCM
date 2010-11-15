# Client maintainer: mmroden gmail . com
cmake_minimum_required(VERSION 2.8.2)

set(CTEST_SITE "silverstreak")
set(CTEST_BUILD_NAME "Win32-windows7-vs9-2.1-Release")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "Visual Studio 9 2008 Win64")
set(CTEST_DASHBOARD_ROOT "H:/src/dashboard/gdcm-dashboard/")
set(dashboard_binary_name "vtk-build-release-64-nightly")
set(dashboard_source_name VTK)
set(dashboard_model Nightly)
set(dashboard_do_test FALSE)

SET(CTEST_GIT_COMMAND "C:/Program Files (x86)/Git/bin/git.exe")
SET(ENV{CFLAGS} "/W4")
SET(ENV{CXXFLAGS} "/W4")

set(dashboard_cache "
BUILD_SHARED_LIBS:BOOL=ON
BUILD_EXAMPLES:BOOL=OFF
VTK_DEBUG_LEAKS:BOOL=ON
VTK_USE_PARALLEL:BOOL=OFF
VTK_USE_RENDERING:BOOL=ON
VTK_WRAP_JAVA:BOOL=ON
")

include(${CTEST_SCRIPT_DIRECTORY}/vtk_common.cmake)
