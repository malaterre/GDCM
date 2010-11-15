# Client maintainer: mmroden gmail . com
cmake_minimum_required(VERSION 2.8.2)

set(CTEST_SITE "vbox.malat")
set(CTEST_BUILD_NAME "Windows7-vs10-Debug")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Visual Studio 10")
set(dashboard_binary_name "vtk-vs10-debug")
set(dashboard_source_name VTK)
set(dashboard_model Nightly)

SET(CTEST_GIT_COMMAND "C:/cygwin/bin/git.exe")
#SET(ENV{CFLAGS} "/W4")
#SET(ENV{CXXFLAGS} "/W4")

set(dashboard_cache "
BUILD_SHARED_LIBS:BOOL=ON
BUILD_EXAMPLES:BOOL=OFF
VTK_DEBUG_LEAKS:BOOL=ON
VTK_USE_PARALLEL:BOOL=OFF
VTK_USE_RENDERING:BOOL=ON
VTK_WRAP_JAVA:BOOL=OFF
")

include(${CTEST_SCRIPT_DIRECTORY}/vtk_common.cmake)
