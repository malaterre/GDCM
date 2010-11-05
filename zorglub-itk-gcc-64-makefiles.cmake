# Client maintainer: mathieu malaterre gmail com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Debian-stable-gcc4-64bit")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
#set(CTEST_TEST_ARGS PARALLEL_LEVEL 2)

macro(dashboard_hook_init)
  set( dashboard_cache "
    BUILD_EXAMPLES:BOOL=OFF
    BUILD_SHARED_LIBS:BOOL=ON
    BUILD_TESTING:BOOL=ON
    ITK_USE_SYSTEM_GDCM:BOOL=OFF
    "
    )
endmacro(dashboard_hook_init)


include(${CTEST_SCRIPT_DIRECTORY}/itk_common.cmake)
