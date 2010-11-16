# Client maintainer: mmroden gmail . com

set(CTEST_SITE "silverstreak")
set(CTEST_BUILD_NAME "Win32-windows7-vs9-2.1-Release")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "Visual Studio 9 2008 Win64")
set(CTEST_DASHBOARD_ROOT "H:/src/dashboard/gdcm-dashboard/")
set(dashboard_binary_name "gdcm-build-release-64-nightly")

SET(CTEST_GIT_COMMAND "C:/Program Files (x86)/Git/bin/git.exe")
SET(ENV{CFLAGS} "/W4")
SET(ENV{CXXFLAGS} "/W4")

macro(dashboard_hook_init)
  set( dashboard_cache "
  GDCM_BUILD_SHARED_LIBS:BOOL=ON
  GDCM_BUILD_APPLICATIONS:BOOL=ON
  GDCM_BUILD_EXAMPLES:BOOL=ON
  GDCM_USE_VTK:BOOL=ON
  VTK_DIR:PATH=${CTEST_DASHBOARD_ROOT}/vtk-build-release-64-nightly
  #set up DICOM Q/R
  #client side (server restriction)
  GDCM_DICOM_CLIENT_AETITLE:STRING=UNITED1
  #only needed for cmove
  GDCM_DICOM_CLIENT_PORT:STRING=11111

  #server side conf:
  GDCM_DICOM_SERVER_AETITLE:STRING=COMMON
  GDCM_DICOM_SERVER_PEER:STRING=192.168.1.4
  GDCM_DICOM_SERVER_PORT:STRING=11112
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
