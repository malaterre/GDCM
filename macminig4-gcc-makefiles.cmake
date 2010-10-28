# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "macminig4")
set(CTEST_BUILD_NAME "Linux-gcc-GIT")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-gcc-nightly")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)

SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wextra -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -Wsign-promo -Weffc++ -Wabi -D_GLIBCXX_DEBUG")
SET(ENV{CFLAGS}   "-g -O0 -Wall -W -Wextra -pedantic -Wno-long-long")

macro(dashboard_hook_init)
  set( dashboard_cache "
  #GDCM_WRAP_PYTHON:BOOL=ON
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_BUILD_APPLICATIONS:BOOL=ON

#GDCM_DATA_EXTRA_ROOT:PATH=$ENV{HOME}/Creatis/gdcmDataExtra
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
