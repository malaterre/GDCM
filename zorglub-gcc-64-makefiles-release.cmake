# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Linux-gcc-GIT-release")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_DASHBOARD_ROOT "/local/mmalater")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm-release")
set(dashboard_binary_name "gdcm-nightly-release")
set(dashboard_git_branch release)
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)

SET(ENV{GDCM_DATA_ROOT} "$ENV{HOME}/Creatis/gdcmData")
SET(CTEST_GDCM_PIXEL_SPACING_DATA_ROOT "$ENV{HOME}/Dashboards/Theralys/pixelspacingtestimages")
SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -pedantic -Wno-long-long")
# set any extra envionment variables here
SET (ENV{JAVA_HOME} "/usr/lib/jvm/default-java")

# http://www.cmake.org/Wiki/CTest:Coverage
SET(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
#SET(ENV{CXXFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -Wno-deprecated -W -Wall")
#SET(ENV{CFLAGS} "-g -O0 -fprofile-arcs -ftest-coverage -W -Wall")
#SET(ENV{LDFLAGS} "-fprofile-arcs -ftest-coverage")

macro(dashboard_hook_init)
  set( dashboard_cache "
GDCM_WRAP_PYTHON:BOOL=ON
GDCM_WRAP_CSHARP:BOOL=ON
GDCM_WRAP_JAVA:BOOL=ON
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_TEST_DCMTK:BOOL=ON
GDCM_TEST_BOOTSTRAP:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_USE_VTK:BOOL=OFF
VTK_DIR:PATH=/home/mathieu/Kitware/VTK56-gcc
GDCM_DOCUMENTATION:BOOL=OFF
GDCM_VTK_DOCUMENTATION:BOOL=OFF

# Temp fix for:
# Program received signal SIGSEGV, Segmentation fault.
# 0x00007fffe9c8a2b0 in cio_tell () from /usr/lib/libopenjpeg.so.2
GDCM_USE_SYSTEM_OPENJPEG:BOOL=OFF

# To do some more testing for the anonymizer
GDCM_USE_SYSTEM_OPENSSL:BOOL=ON

CMAKE_INSTALL_PREFIX:PATH=/tmp/local-gcc-rel
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
