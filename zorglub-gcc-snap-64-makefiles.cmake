# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Debian-stable-gcc4-64bit")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-nightly-snap")
set(dashboard_do_memcheck TRUE)

SET(CTEST_MEMORYCHECK_COMMAND           "/usr/bin/valgrind")
SET(CTEST_MEMORYCHECK_COMMAND_OPTIONS   "-q --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=10")

macro(dashboard_hook_init)
  set( dashboard_cache "
  #CMAKE_BUILD_TYPE:STRING=Debug
  #MEMORYCHECK_COMMAND:FILEPATH=${CTEST_MEMORYCHECK_COMMAND}
MEMORYCHECK_COMMAND_OPTIONS:STRING=${CTEST_MEMORYCHECK_COMMAND_OPTIONS}
GDCM_WRAP_PYTHON:BOOL=ON
GDCM_WRAP_CSHARP:BOOL=ON
GDCM_WRAP_JAVA:BOOL=ON
#CMAKE_OVERRIDE_COMPILER_MISMATCH:BOOL=ON
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON
# problem with ld.gold...
GDCM_USE_VTK:BOOL=OFF
GDCM_DOCUMENTATION:BOOL=OFF
GDCM_VTK_DOCUMENTATION:BOOL=OFF
#MAKECOMMAND:STRING=/usr/bin/make -j8
GDCM_DATA_EXTRA_ROOT:PATH=$ENV{HOME}/Creatis/gdcmDataExtra
#GDCM_PIXEL_SPACING_DATA_ROOT:PATH=${CTEST_GDCM_PIXEL_SPACING_DATA_ROOT}
# secret option:
GDCM_USE_ITK_I_UNDERSTAND_WHAT_I_AM_DOING:BOOL=OFF
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
