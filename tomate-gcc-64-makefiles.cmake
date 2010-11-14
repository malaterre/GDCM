# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "tomate")
set(CTEST_BUILD_NAME "Linux-gcc-GIT")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-gcc-tomate")
set(dashboard_do_memcheck TRUE)
set(dashboard_do_coverage FALSE)
set(CTEST_TEST_TIMEOUT 3000)

SET(CTEST_MEMORYCHECK_COMMAND           "/usr/bin/valgrind")
SET(CTEST_MEMORYCHECK_COMMAND_OPTIONS   "-q --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=10")
SET(ENV{GLIBCPP_FORCE_NEW} 1)
SET(ENV{GLIBCXX_FORCE_NEW} 1)

SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wextra -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -pedantic -Wno-long-long -Wsign-promo -Weffc++ -Wabi -D_GLIBCXX_DEBUG")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -Wextra -pedantic -Wno-long-long")

SET(ENV{PATH} "$ENV{HOME}/Software/cmake-2.8.2-Linux-i386/bin:$ENV{PATH}")

macro(dashboard_hook_init)
  set( dashboard_cache "
MEMORYCHECK_COMMAND_OPTIONS:STRING=${CTEST_MEMORYCHECK_COMMAND_OPTIONS}
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_BUILD_EXAMPLES:BOOL=ON
GDCM_USE_VTK:BOOL=ON
# Cannot use CTEST_DASHBOARD_ROOT directly...
VTK_DIR:PATH=$ENV{HOME}/Dashboards/${dashboard_root_name}/VTK-gcc-tomate
CMAKE_INSTALL_PREFIX:PATH=/tmp/tomate-gdcm
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
