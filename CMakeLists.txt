PROJECT(GDCM)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
#-----------------------------------------------------------------------------
# New cmake policy thingy
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)
MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY CMAKE_BUILD_TYPE CMAKE_INSTALL_PREFIX)
SET(GDCM_CMAKE_DIR "${GDCM_SOURCE_DIR}/CMake" CACHE INTERNAL "")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GDCM_CMAKE_DIR}")

FIND_PACKAGE(UUID)

#-----------------------------------------------------------------------------
# Disallow insource build since I never test that
STRING(COMPARE EQUAL "${GDCM_SOURCE_DIR}" "${GDCM_BINARY_DIR}" INSOURCE)
GET_FILENAME_COMPONENT(PARENTDIR ${GDCM_BINARY_DIR} PATH)
STRING(COMPARE EQUAL "${GDCM_SOURCE_DIR}" "${PARENTDIR}" INSOURCESUBDIR)
IF(INSOURCE OR INSOURCESUBDIR)
  MESSAGE(FATAL_ERROR "GDCM requires an out of source Build. "
    "Please create a separate binary directory and run CMake there.")
ENDIF(INSOURCE OR INSOURCESUBDIR)

#-----------------------------------------------------------------------------
SET(GDCM_MAJOR_VERSION 2)
SET(GDCM_MINOR_VERSION 1)
SET(GDCM_BUILD_VERSION 0)
SET(GDCM_VERSION
  "${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}.${GDCM_BUILD_VERSION}")
SET(GDCM_LIBRARY_PROPERTIES ${GDCM_LIBRARY_PROPERTIES}
  VERSION "${GDCM_VERSION}"
  SOVERSION "${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}"
)
SET(GDCM_EXECUTABLE_PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES}
  VERSION "${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}"
)

#-----------------------------------------------------------------------------
# VS 2005 declared that some C functions were deprecated...
IF(CMAKE_COMPILER_2005)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
  ADD_DEFINITIONS(-D_SCL_SECURE_NO_DEPRECATE)
ENDIF(CMAKE_COMPILER_2005) 


#-----------------------------------------------------------------------------
# Build shared lib by default
OPTION(GDCM_BUILD_SHARED_LIBS "Build GDCM with shared libraries." OFF)
SET(BUILD_SHARED_LIBS ${GDCM_BUILD_SHARED_LIBS})

#-----------------------------------------------------------------------------
SET (EXECUTABLE_OUTPUT_PATH ${GDCM_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
SET (LIBRARY_OUTPUT_PATH ${GDCM_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

#-----------------------------------------------------------------------------
# Adding GDCM_DATA_ROOT
FIND_PATH(GDCM_DATA_ROOT gdcm-ACR-LibIDO.acr
  ${GDCM_SOURCE_DIR}/../gdcmData
  $ENV{GDCM_DATA_ROOT}
  $ENV{PUB_DICT_PATH}/../../gdcmData
  )
MARK_AS_ADVANCED(GDCM_DATA_ROOT)
# You can define a path where you extra the famous D. Clunie spacing dataset
# http://www.dclunie.com/images/pixelspacingtestimages.zip
# for example: 
# find $HOME/pixelspacingtestimages
# $HOME/pixelspacingtestimages
# $HOME/pixelspacingtestimages/DISCIMG
# $HOME/pixelspacingtestimages/DISCIMG/DICOMDIR
# $HOME/pixelspacingtestimages/DISCIMG/IMAGES
# $HOME/pixelspacingtestimages/DISCIMG/IMAGES/DXIMAGE
# $HOME/pixelspacingtestimages/DISCIMG/IMAGES/MGIMAGE
# $HOME/pixelspacingtestimages/DISCIMG/IMAGES/CRIMAGE
MARK_AS_ADVANCED(GDCM_PIXEL_SPACING_DATA_ROOT)

#-----------------------------------------------------------------------------
FIND_PATH(GDCM_DATA_EXTRA_ROOT gdcmData.tar.gz
  ${GDCM_SOURCE_DIR}/../gdcmDataExtra
  $ENV{GDCM_DATA_EXTRA_ROOT}
  $ENV{PUB_DICT_PATH}/../../gdcmDataExtra
  )
MARK_AS_ADVANCED(GDCM_DATA_EXTRA_ROOT)

# Define a temp directory in which we can output stuff
SET(GDCM_TEMP_DIRECTORY "${GDCM_BINARY_DIR}/Testing/Temporary" CACHE PATH "Path to a valid temp directory")
MARK_AS_ADVANCED(GDCM_TEMP_DIRECTORY)

#-----------------------------------------------------------------------------
INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFiles.cmake)
# Check if header file exists and add it to the list.
MACRO(CHECK_INCLUDE_FILE_CONCAT FILE VARIABLE)
  CHECK_INCLUDE_FILES("${UUID_INCLUDES};${FILE}" ${VARIABLE})
  IF(${VARIABLE})
    SET(UUID_INCLUDES ${UUID_INCLUDES} ${FILE})
  ENDIF(${VARIABLE})
ENDMACRO(CHECK_INCLUDE_FILE_CONCAT)

CHECK_INCLUDE_FILE("stdint.h"       CMAKE_HAVE_STDINT_H)
IF(UNIX) #Avoid polluting Win32 cmakecache
  CHECK_INCLUDE_FILE("inttypes.h"     CMAKE_HAVE_INTTYPES_H)
ENDIF(UNIX)

#INCLUDE(${GDCM_SOURCE_DIR}/CMake/gdcmPlatformCxxTests.cmake)
#
#GDCM_PLATFORM_CXX_TEST(GDCM_CXX_HAS_FUNCTION
#    "Checking whether compiler has __FUNCTION__" DIRECT)


#-----------------------------------------------------------------------------
# Build the main lib...
IF(WIN32 AND NOT CYGWIN)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/C99"
  )
ENDIF(WIN32 AND NOT CYGWIN)

# --------------------------------------------------------------------------
# Configure the export configuration

# You will also need to define a value for the following variables:
# GDCM_INSTALL_BIN_DIR          - binary dir (executables)
# GDCM_INSTALL_LIB_DIR          - library dir (libs)
# GDCM_INSTALL_DATA_DIR         - share dir (say, examples, data, etc)
# GDCM_INSTALL_INCLUDE_DIR      - include dir (headers)
# GDCM_INSTALL_PACKAGE_DIR      - package/export configuration files
# GDCM_VTK_INSTALL_PACKAGE_DIR  - VTK package/export configuration files
# GDCM_INSTALL_NO_DEVELOPMENT   - do not install development files
# GDCM_INSTALL_NO_RUNTIME       - do not install runtime files
# GDCM_INSTALL_NO_DOCUMENTATION - do not install documentation files

# --------------------------------------------------------------------------
# Install directories

IF(NOT GDCM_INSTALL_BIN_DIR)
  SET(GDCM_INSTALL_BIN_DIR "bin")
ENDIF(NOT GDCM_INSTALL_BIN_DIR)

IF(NOT GDCM_INSTALL_LIB_DIR)
  SET(GDCM_INSTALL_LIB_DIR "lib/${PROJECT_NAME}")
ENDIF(NOT GDCM_INSTALL_LIB_DIR)

IF(NOT GDCM_INSTALL_DATA_DIR)
  SET(GDCM_INSTALL_DATA_DIR "share/${PROJECT_NAME}")
ENDIF(NOT GDCM_INSTALL_DATA_DIR)

IF(NOT GDCM_INSTALL_INCLUDE_DIR)
  SET(GDCM_INSTALL_INCLUDE_DIR "include/${PROJECT_NAME}")
ENDIF(NOT GDCM_INSTALL_INCLUDE_DIR)

IF(NOT GDCM_INSTALL_PACKAGE_DIR)
  SET(GDCM_INSTALL_PACKAGE_DIR ${GDCM_INSTALL_LIB_DIR}
    CACHE INTERNAL "")
ENDIF(NOT GDCM_INSTALL_PACKAGE_DIR)

IF(NOT GDCM_VTK_INSTALL_PACKAGE_DIR)
  SET(GDCM_VTK_INSTALL_PACKAGE_DIR ${VTK_INSTALL_PACKAGE_DIR})
ENDIF(NOT GDCM_VTK_INSTALL_PACKAGE_DIR)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  SET(GDCM_INSTALL_NO_DEVELOPMENT 0)
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

IF(NOT GDCM_INSTALL_NO_RUNTIME)
  SET(GDCM_INSTALL_NO_RUNTIME 0)
ENDIF(NOT GDCM_INSTALL_NO_RUNTIME)

IF(NOT GDCM_INSTALL_NO_DOCUMENTATION)
  SET(GDCM_INSTALL_NO_DOCUMENTATION 0)
ENDIF(NOT GDCM_INSTALL_NO_DOCUMENTATION)

SET(GDCM_INSTALL_NO_LIBRARIES)
IF(GDCM_BUILD_SHARED_LIBS)
  IF(GDCM_INSTALL_NO_RUNTIME AND GDCM_INSTALL_NO_DEVELOPMENT)
    SET(GDCM_INSTALL_NO_LIBRARIES 1)
  ENDIF(GDCM_INSTALL_NO_RUNTIME AND GDCM_INSTALL_NO_DEVELOPMENT)
ELSE(GDCM_BUILD_SHARED_LIBS)
  IF(GDCM_INSTALL_NO_DEVELOPMENT)
    SET(GDCM_INSTALL_NO_LIBRARIES 1)
  ENDIF(GDCM_INSTALL_NO_DEVELOPMENT)
ENDIF(GDCM_BUILD_SHARED_LIBS)

#-----------------------------------------------------------------------------
OPTION(GDCM_BUILD_EXAMPLES "Build GDCM examples." OFF)
SET(BUILD_EXAMPLES ${GDCM_BUILD_EXAMPLES})
IF(BUILD_EXAMPLES)
  SUBDIRS(Examples)
ENDIF(BUILD_EXAMPLES)

#-----------------------------------------------------------------------------
# Add the testing directories
OPTION(GDCM_BUILD_TESTING "Build testing." ON)
SET(BUILD_TESTING ${GDCM_BUILD_TESTING} CACHE BOOL "" FORCE)
MARK_AS_ADVANCED(BUILD_TESTING)

#-----------------------------------------------------------------------------
# Wrapping
OPTION(GDCM_WRAP_PYTHON "build python wrapping" OFF)
IF(GDCM_BUILD_WRAPPING)
  MESSAGE(STATUS "GDCM_BUILD_WRAPPING option is deprecate, please specify explicitely which target language to wrap")
  SET(GDCM_WRAP_PYTHON ON CACHE BOOL "(deprecated) build python wrapping" FORCE)
ENDIF(GDCM_BUILD_WRAPPING)
OPTION(GDCM_WRAP_PHP "php wrapping (experimental !)" OFF)
OPTION(GDCM_WRAP_JAVA "build java wrapping (experimental !)" OFF)
MARK_AS_ADVANCED(GDCM_WRAP_PHP GDCM_WRAP_JAVA)

#-----------------------------------------------------------------------------
# Special CMake Module required when doing Python Testing
IF(BUILD_TESTING AND GDCM_WRAP_PYTHON)
  INCLUDE(${GDCM_SOURCE_DIR}/CMake/UsePythonTest.cmake)
ENDIF(BUILD_TESTING AND GDCM_WRAP_PYTHON)

#-----------------------------------------------------------------------------
# Need pthread for the following class:
CHECK_INCLUDE_FILE("pthread.h"      CMAKE_HAVE_PTHREAD_H)

SUBDIRS(
  Utilities
  Source
  )

IF(BUILD_TESTING)
  CONFIGURE_FILE(${GDCM_SOURCE_DIR}/CMake/CTestCustom.ctest.in
      ${GDCM_BINARY_DIR}/CMake/CTestCustom.ctest @ONLY)
  FILE(WRITE ${GDCM_BINARY_DIR}/CTestCustom.cmake
    "INCLUDE(\"${GDCM_BINARY_DIR}/CMake/CTestCustom.ctest\")\n")
  MARK_AS_ADVANCED(DART_TESTING_TIMEOUT)
  ENABLE_TESTING()
  INCLUDE(CTest)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)


#-----------------------------------------------------------------------------
# Here is one cool test: you can pretty much test all configuration using
# ctest...well except one, the case where a user set BUILD_TESTING=OFF
# since this would deactivate the dashboard and would not submit...doh!
# So instead let's create a test that would build gdcm with this option
IF(UNIX AND GDCM_TEST_BOOSTRAP)
  ADD_TEST(BuildGDCM ${CMAKE_CTEST_COMMAND}
    #${VTK_EXAMPLE_TEST_CONFIG_TYPE}
    --build-and-test
    ${GDCM_SOURCE_DIR}
    ${GDCM_BINARY_DIR}/GDCMLocal
    --build-two-config
    --build-generator ${CMAKE_GENERATOR}
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-project GDCMLOCAL
    #--build-run-dir ${VTK_EXAMPLE_TEST_RUN_DIR}
    --build-options -DGDCM_BUILD_TESTING:BOOL=OFF -DGDCM_BUILD_SHARED_LIBS:BOOL=ON -DGDCM_WRAP_PYTHON:BOOL=ON -DGDCM_SUPPORT_BROKEN_IMPLEMENTATION:BOOL=OFF
    #--test-command "${VTK_BINARY_DIR}/Examples/Build/vtkLocal/bin/vtkLocalTest"
    )
ENDIF(UNIX AND GDCM_TEST_BOOSTRAP)


#-----------------------------------------------------------------------------
OPTION(GDCM_DOCUMENTATION "Build source documentation using doxygen." OFF)

#-----------------------------------------------------------------------------
OPTION(GDCM_USE_VTK "vtk bridge ?" OFF)
IF(GDCM_USE_VTK)
  SUBDIRS(Utilities/VTK)
ENDIF(GDCM_USE_VTK)

#-----------------------------------------------------------------------------
OPTION(GDCM_USE_ITK "itk bridge ?" OFF)
IF(GDCM_USE_ITK)
  SUBDIRS(Utilities/Insight)
ENDIF(GDCM_USE_ITK)

#-----------------------------------------------------------------------------
OPTION(GDCM_USE_WXWIDGETS "wxWidgets bridge ?" OFF)
IF(GDCM_USE_WXWIDGETS)
  SUBDIRS(Utilities/wxWidgets)
ENDIF(GDCM_USE_WXWIDGETS)

#-----------------------------------------------------------------------------
OPTION(GDCM_BUILD_APPLICATIONS "apps ?" OFF)
SET(BUILD_APPLICATIONS ${GDCM_BUILD_APPLICATIONS})
IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

#-----------------------------------------------------------------------------
# CPack stuff
IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GDCM - Grass Root DICOM")
  SET(CPACK_PACKAGE_VENDOR "GDCM")
  SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
  SET(CPACK_PACKAGE_VERSION_MAJOR "${GDCM_MAJOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_MINOR "${GDCM_MINOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_PATCH "${GDCM_BUILD_VERSION}")
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY "GDCM ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
  SET(CPACK_SOURCE_PACKAGE_FILE_NAME "gdcm-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

  #SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
  IF(WIN32 AND NOT UNIX)
    #STRING(REGEX REPLACE "/" "\\\\\\\\" CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Release/GDCMInstall.bmp")

    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    #SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
    SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\gdcmviewer.exe")
    SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
    SET(CPACK_NSIS_HELP_LINK "http://gdcm.sourceforge.net")
    SET(CPACK_NSIS_URL_INFO_ABOUT "http://gdcm.sourceforge.net")
    SET(CPACK_NSIS_MODIFY_PATH ON)
  ELSE(WIN32 AND NOT UNIX)
    SET(CPACK_STRIP_FILES "bin/gdcmdump;bin/gdcmconv;bin/gdcmimg;bin/gdcmscanner")
    SET(CPACK_SOURCE_STRIP_FILES "")
    SET(CPACK_PACKAGE_EXECUTABLES "gdcmviewer" "VIEWER")

  ENDIF(WIN32 AND NOT UNIX)
  IF(NOT DEFINED CPACK_SYSTEM_NAME)
    SET(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
  ENDIF(NOT DEFINED CPACK_SYSTEM_NAME)
  # Need to set the architecture for debian package

  SET(CPACK_PACKAGE_CONTACT "gdcm-developers@lists.sourceforge.net")

  # List executables
  #SET(CPACK_PACKAGE_EXECUTABLES "gdcmviewer" "VIEWER")
  IF(CYGWIN)
    SET(CPACK_CYGWIN_PATCH_NUMBER 1)
    SET(CPACK_CYGWIN_BUILD_SCRIPT
    "${GDCM_BINARY_DIR}/@CPACK_PACKAGE_FILE_NAME@-@CPACK_CYGWIN_PATCH_NUMBER@.sh")
    SET(CPACK_CYGWIN_PATCH_FILE
  "${GDCM_BINARY_DIR}/@CPACK_PACKAGE_FILE_NAME@-@CPACK_CYGWIN_PATCH_NUMBER@.patch")
    CONFIGURE_FILE(${GDCM_SOURCE_DIR}/CMake/Release/cygwin-patch.diff.in ${CPACK_CYGWIN_PATCH_FILE})
    CONFIGURE_FILE(${GDCM_SOURCE_DIR}/CMake/Release/cygwin-package.sh.in ${CPACK_CYGWIN_BUILD_SCRIPT})
  ENDIF(CYGWIN)
  INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

SUBDIRS(Wrapping)

#-----------------------------------------------------------------------------
# Need to be the last operation:
SUBDIRS(CMake/ExportConfiguration)

