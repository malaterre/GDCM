# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Linux-gcc-snap-GIT")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-nightly-snap")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)
set(CTEST_TEST_TIMEOUT 3000)

SET(CTEST_MEMORYCHECK_COMMAND           "/usr/bin/valgrind")
SET(CTEST_MEMORYCHECK_COMMAND_OPTIONS   "-q --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=10")

SET(ENV{GLIBCPP_FORCE_NEW} 1)
SET(ENV{GLIBCXX_FORCE_NEW} 1)
# $ apt-cache policy gcc-snapshot 20090923-1
SET(JAVA_HOME_PATH "/usr/lib/gcc-snapshot/lib/jvm/java-1.5.0-gcj-4.5-snap")
SET(ENV{JAVA_HOME} ${JAVA_HOME_PATH})

# http://www.cmake.org/Wiki/CTest:Coverage
SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wextra -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -pedantic -Wno-long-long -Wsign-promo -Weffc++ -Wabi -D_GLIBCXX_DEBUG")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -Wextra -pedantic -Wno-long-long")
SET(ENV{PATH} "/usr/lib/jvm/java-1.5.0-gcj-4.6-snap/bin/:${JAVA_HOME_PATH}/bin/:/usr/lib/gcc-snapshot/bin:$ENV{PATH}")
SET(ENV{LD_LIBRARY_PATH} "/usr/lib/gcc-snapshot/lib")

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
