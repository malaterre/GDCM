# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "tomate")
set(CTEST_BUILD_NAME "Linux-gcc-GIT-release-cov")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_DASHBOARD_ROOT "/local/mmalater")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm-release")
set(dashboard_binary_name "gdcm-nightly-release-cov")
set(dashboard_git_branch release)
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage TRUE)

SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -pedantic -Wno-long-long")
# set any extra envionment variables here
SET(ENV{JAVA_HOME} "/opt/jdk")

# http://www.cmake.org/Wiki/CTest:Coverage
SET(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
SET(ENV{CXXFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -Wno-deprecated -W -Wall")
SET(ENV{CFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -W -Wall")
SET(ENV{LDFLAGS} "-fprofile-arcs -ftest-coverage")

macro(dashboard_hook_init)
  set( dashboard_cache "
GDCM_WRAP_PYTHON:BOOL=ON
GDCM_WRAP_CSHARP:BOOL=OFF
GDCM_WRAP_JAVA:BOOL=ON
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_TEST_BOOTSTRAP:BOOL=OFF
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_USE_VTK:BOOL=ON
VTK_DIR:PATH=${CTEST_DASHBOARD_ROOT}/VTK-gcc-tomate
GDCM_DOCUMENTATION:BOOL=OFF
GDCM_VTK_DOCUMENTATION:BOOL=OFF
GDCM_BUILD_TESTING:BOOL=ON
GDCM_DATA_EXTRA_ROOT:PATH=${CTEST_DASHBOARD_ROOT}/gdcmDataExtra
GDCM_USE_SYSTEM_OPENSSL:BOOL=ON
GDCM_TEST_DCMTK:BOOL=ON
CMAKE_INSTALL_PREFIX:PATH=/tmp/local-gcc-cov
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
