# File name:
#
# OS:
# Hardware:
# GPU:
#
cmake_minimum_required(VERSION 2.8.2)

# Client maintainer: mathieu malaterre
set(CTEST_SITE "tomate")
set(CTEST_BUILD_NAME "Linux-gcc")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_DASHBOARD_ROOT "/local/mmalater")
set(dashboard_root_name "MyTests")
set(dashboard_source_name VTK)
set(dashboard_binary_name VTK-gcc-tomate)
set(dashboard_model Nightly)
set(dashboard_do_test FALSE)

SET(ENV{PATH} "/opt/bin:/opt/jdk/bin:/opt/jre/bin:/usr/local/sbin:/usr/local/bin:$ENV{PATH}")


set(dashboard_cache "
BUILD_SHARED_LIBS:BOOL=ON
BUILD_EXAMPLES:BOOL=OFF
VTK_DEBUG_LEAKS:BOOL=ON
VTK_USE_PARALLEL:BOOL=OFF
VTK_USE_RENDERING:BOOL=ON
VTK_USE_N_WAY_ARRAYS:BOOL=OFF
VTK_USE_INFOVIS:BOOL=OFF
VTK_WRAP_JAVA:BOOL=ON
VTK_WRAP_PYTHON:BOOL=ON
")

include(${CTEST_SCRIPT_DIRECTORY}/vtk_common.cmake)
