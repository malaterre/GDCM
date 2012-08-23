# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "minimacg4")
set(CTEST_BUILD_NAME "Linux-gcc-cov")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-cov-brocoli")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage TRUE)

#SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ")
#SET(ENV{CFLAGS}   "-g -O0 -Wall -W -pedantic -Wno-long-long")
#SET(ENV{PATH} "$ENV{HOME}/Software/cmake-2.8.2-Linux-i386/bin:$ENV{PATH}")

# http://www.cmake.org/Wiki/CTest:Coverage
SET(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
SET(ENV{CXXFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -Wno-deprecated -Wno-deprecated-declarations -W -Wall")
SET(ENV{CFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -W -Wall")
SET(ENV{LDFLAGS} "-fprofile-arcs -ftest-coverage")

macro(dashboard_hook_init)
  set( dashboard_cache "
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_BUILD_EXAMPLES:BOOL=ON
GDCM_USE_VTK:BOOL=OFF
GDCM_DATA_EXTRA_ROOT:PATH=${CTEST_DASHBOARD_ROOT}/gdcmDataExtra
GDCM_USE_SYSTEM_OPENSSL:BOOL=ON
GDCM_USE_SYSTEM_LIBXML2:BOOL=ON
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
