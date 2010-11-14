# File name:
#
# OS:
# Hardware:
# GPU:
#
cmake_minimum_required(VERSION 2.8.2)

# Client maintainer: mathieu malaterre
set(CTEST_SITE "brocoli")
set(CTEST_BUILD_NAME "Linux-gcc")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
set(dashboard_source_name VTK)
set(dashboard_binary_name VTK-gcc-brocoli)
set(dashboard_model Nightly)
set(dashboard_do_test FALSE)

#set(VTK_DATA_ROOT ${CTEST_DASHBOARD_ROOT}/VTKData)
#set(VTK_LARGE_DATA_ROOT ${CTEST_DASHBOARD_ROOT}/VTKLargeData)
#set(CTEST_TEST_TIMEOUT 120)

set(dashboard_cache "
BUILD_SHARED_LIBS:BOOL=ON
BUILD_EXAMPLES:BOOL=OFF
VTK_DEBUG_LEAKS:BOOL=ON
VTK_USE_PARALLEL:BOOL=OFF
VTK_USE_RENDERING:BOOL=OFF
#VTK_DATA_ROOT:PATH=${CTEST_DASHBOARD_ROOT}/VTKData
")

include(${CTEST_SCRIPT_DIRECTORY}/vtk_common.cmake)
