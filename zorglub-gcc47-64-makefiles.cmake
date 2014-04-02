# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Linux-gcc-snap-GIT")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
#set(CTEST_DASHBOARD_ROOT "/local/mmalater")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j2")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-gcc47-nightly")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)

SET(ENV{CC} "gcc-4.7")
SET(ENV{CXX} "g++-4.7")
#SET(ENV{GDCM_DATA_ROOT} "$ENV{HOME}/Creatis/gdcmData")
#SET(CTEST_GDCM_PIXEL_SPACING_DATA_ROOT "$ENV{HOME}/Dashboards/Theralys/pixelspacingtestimages")
SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wextra -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -Wsign-promo -Wabi -D_GLIBCXX_DEBUG -fvisibility=hidden")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -Wextra -pedantic -Wno-long-long -fvisibility=hidden")

macro(dashboard_hook_init)
  set( dashboard_cache "
  #CMAKE_BUILD_TYPE:STRING=Debug
  #MEMORYCHECK_COMMAND:FILEPATH=${CTEST_MEMORYCHECK_COMMAND}
  #MEMORYCHECK_COMMAND_OPTIONS:STRING=${CTEST_MEMORYCHECK_COMMAND_OPTIONS}
GDCM_WRAP_PYTHON:BOOL=ON
PYTHON_EXECUTABLE:FILEPATH=/usr/bin/python3.2
PYTHON_INCLUDE_DIR:PATH=/usr/include/python3.2mu
PYTHON_INCLUDE_DIR2:PATH=/usr/include/python3.2mu
PYTHON_LIBRARY:FILEPATH=/usr/lib/libpython3.2mu.so
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_TEST_DCMTK:BOOL=OFF
GDCM_TEST_BOOTSTRAP:BOOL=OFF
CMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make
GDCM_BUILD_APPLICATIONS:BOOL=ON

GDCM_USE_VTK:BOOL=ON
GDCM_DOCUMENTATION:BOOL=OFF
GDCM_VTK_DOCUMENTATION:BOOL=ON
MAKECOMMAND:STRING=/usr/bin/make -j2
GDCM_DATA_EXTRA_ROOT:PATH=$ENV{HOME}/Creatis/gdcmDataExtra
#GDCM_PIXEL_SPACING_DATA_ROOT:PATH=${CTEST_GDCM_PIXEL_SPACING_DATA_ROOT}
CMAKE_OVERRIDE_COMPILER_MISMATCH:BOOL=ON

CMAKE_INSTALL_PREFIX:PATH=/tmp/local47
# secret option
#GDCM_TESTING_USE_LC_NUMERIC:BOOL=ON
GDCM_USE_SYSTEM_LIBXML2:BOOL=ON
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
