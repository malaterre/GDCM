# Client maintainer: mathieu . malaterre  gmail . com

set(CTEST_SITE "macminig4")
set(CTEST_BUILD_NAME "GDCM2-Linux-kwstyle-SVN")
set(CTEST_BUILD_CONFIGURATION Debug)
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(dashboard_root_name "MyTests")
set(dashboard_source_name "gdcm")
set(dashboard_binary_name "gdcm-nightly-kwstyle")
set(dashboard_do_memcheck FALSE)
set(dashboard_do_coverage FALSE)
set(dashboard_do_test     FALSE)
set(dashboard_no_clean    TRUE)

macro(dashboard_hook_init)
  set( dashboard_cache "
GDCM_BUILD_SHARED_LIBS:BOOL=ON
GDCM_USE_KWSTYLE:BOOL=ON

GDCM_DOCUMENTATION:BOOL=ON
GDCM_VTK_DOCUMENTATION:BOOL=ON
    "
    )
endmacro(dashboard_hook_init)

macro(dashboard_hook_submit)
  execute_process(COMMAND KWStyle
    -lesshtml
    -html /tmp/${CTEST_PROJECT_NAME}
    -kwsurl http://gdcm.git.sf.net/
    -xml ${CTEST_BINARY_DIRECTORY}/Utilities/KWStyle/GDCM.kws.xml
    -dart ${CTEST_BINARY_DIRECTORY} -1 1
    -o ${CTEST_SOURCE_DIRECTORY}/Utilities/KWStyle/GDCMOverwrite.txt
    -D ${CTEST_BINARY_DIRECTORY}/Utilities/KWStyle/GDCMFiles.txt
    OUTPUT_FILE /tmp/gdcm-kwstyle.log
    RESULT_VARIABLE RES)
endmacro(dashboard_hook_submit)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
