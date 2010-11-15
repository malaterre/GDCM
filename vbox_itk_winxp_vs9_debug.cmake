# Client maintainer: mathieu.malaterre@gmail.com

set(CTEST_SITE "vbox.malat")
set(CTEST_BUILD_NAME "Win32-VS9-Express")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "Visual Studio 10 2010")
set(CTEST_TEST_TIMEOUT 240)
#set(CTEST_GIT_COMMAND "C:/Program Files/Git/bin/git.exe")
set(CTEST_GIT_COMMAND "C:/cygwin/bin/git.exe")

# cannot reuse the same src for both vbox and physical
#set(dashboard_root_name "MyTests")

#set(dashboard_source_name "ITK")
set(dashboard_binary_name "Insight-VS9-Express")

macro(dashboard_hook_init)
  set(dashboard_cache "${dashboard_cache}
  BUILD_SHARED_LIBS:BOOL=ON
  BUILD_EXAMPLES:BOOL=OFF
  #ITK_LEGACY_SILENT:BOOL=ON
  #ITK_USE_REVIEW:BOOL=ON
  #ITK_USE_CONCEPT_CHECKING:BOOL=ON
  ")
endmacro()

include(${CTEST_SCRIPT_DIRECTORY}/itk_common.cmake)
