# Client maintainer: mathieu malaterre gmail com

set(CTEST_SITE "tomate")
set(CTEST_BUILD_NAME "Linux-gcc")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
#set(CTEST_TEST_ARGS PARALLEL_LEVEL 2)
set(dashboard_source_name ITK)
set(dashboard_binary_name ITK-gcc-tomate)
set(dashboard_model Nightly)

macro(dashboard_hook_init)
  set( dashboard_cache "
    BUILD_EXAMPLES:BOOL=OFF
    BUILD_SHARED_LIBS:BOOL=ON
    BUILD_TESTING:BOOL=ON
    ITK_USE_SYSTEM_GDCM:BOOL=ON
    GDCM_DIR:PATH=$ENV{HOME}/Dashboards/${dashboard_root_name}/gdcm-gcc-tomate
    "
    )
endmacro(dashboard_hook_init)


include(${CTEST_SCRIPT_DIRECTORY}/itk_common.cmake)
