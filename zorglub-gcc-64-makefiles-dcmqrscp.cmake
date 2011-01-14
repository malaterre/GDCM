# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "zorglub")
set(CTEST_BUILD_NAME "Linux-gcc-GIT-dcmqrscp")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_DASHBOARD_ROOT "/local/mmalater")
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j16")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-nightly-dcmqrscp")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)

#SET(ENV{GDCM_DATA_ROOT} "$ENV{HOME}/Creatis/gdcmData")
#SET(CTEST_GDCM_PIXEL_SPACING_DATA_ROOT "$ENV{HOME}/Dashboards/Theralys/pixelspacingtestimages")
#SET(ENV{CXXFLAGS} "-g -O0 -Wall -W -Wshadow -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings ")
#SET(ENV{CFLAGS}   "-g -O0 -Wall -W -pedantic -Wno-long-long")

macro(dashboard_hook_init)
  set( dashboard_cache "
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_SUPPORT_BROKEN_IMPLEMENTATION:BOOL=OFF
GDCM_BUILD_APPLICATIONS:BOOL=ON

# setup DICOM Q/R
# client side (server restriction)
GDCM_DICOM_CLIENT_AETITLE:STRING=GDCMDASH
# only needed for a C-MOVE
GDCM_DICOM_CLIENT_PORT:STRING=5677

# Server side conf:
GDCM_DICOM_SERVER_AETITLE:STRING=GDCM_STORE
GDCM_DICOM_SERVER_PEER:STRING=patate
GDCM_DICOM_SERVER_PORT:STRING=5678
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
