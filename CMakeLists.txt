PROJECT(GDCM)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#-----------------------------------------------------------------------------
# Disallow insource build since I never test that
STRING(COMPARE EQUAL "${GDCM_SOURCE_DIR}" "${GDCM_BINARY_DIR}" INSOURCE)
IF(INSOURCE)
  MESSAGE(FATAL_ERROR "GDCM requires an out of source Build. "
    "Please create a separate binary directory and run CMake there.")
ENDIF(INSOURCE)

#-----------------------------------------------------------------------------
SET(GDCM_MAJOR_VERSION 2)
SET(GDCM_MINOR_VERSION 0)
SET(GDCM_BUILD_VERSION 0)
SET(GDCM_VERSION
  "${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}.${GDCM_BUILD_VERSION}")

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

#-----------------------------------------------------------------------------
INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
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
  SET(GDCM_INSTALL_BIN_DIR "/bin")
ENDIF(NOT GDCM_INSTALL_BIN_DIR)

IF(NOT GDCM_INSTALL_LIB_DIR)
  SET(GDCM_INSTALL_LIB_DIR "/lib/${PROJECT_NAME}")
ENDIF(NOT GDCM_INSTALL_LIB_DIR)

IF(NOT GDCM_INSTALL_DATA_DIR)
  SET(GDCM_INSTALL_DATA_DIR "/share/${PROJECT_NAME}")
ENDIF(NOT GDCM_INSTALL_DATA_DIR)

IF(NOT GDCM_INSTALL_INCLUDE_DIR)
  SET(GDCM_INSTALL_INCLUDE_DIR "/include/${PROJECT_NAME}")
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

SUBDIRS(
  Utilities
  Source
  )

#-----------------------------------------------------------------------------
# Add the testing directories
OPTION(GDCM_BUILD_TESTING "Build testing." ON)
SET(BUILD_TESTING ${GDCM_BUILD_TESTING})

IF(BUILD_TESTING)
  #CONFIGURE_FILE(${GDCM_SOURCE_DIR}/CMake/CTestCustom.ctest.in
  #    ${GDCM_BINARY_DIR}/CMake/CTestCustom.ctest @ONLY)
  #INCLUDE (${CMAKE_ROOT}/Modules/Dart.cmake)
  #MARK_AS_ADVANCED(DART_ROOT)
  ENABLE_TESTING()
  INCLUDE(CTest)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)



#-----------------------------------------------------------------------------
OPTION(GDCM_DOCUMENTATION "Build source documentation using doxygen." OFF)
#SET(BUILD_APPLICATIONS ${GDCM_BUILD_APPLICATIONS})

OPTION(GDCM_USE_VTK "vtk bridge ?" OFF)
IF(GDCM_USE_VTK)
  SUBDIRS(Utilities/VTK)
ENDIF(GDCM_USE_VTK)

OPTION(GDCM_USE_WXWIDGETS "wxWidgets bridge ?" OFF)
IF(GDCM_USE_WXWIDGETS)
  SUBDIRS(Utilities/wxWidgets)
ENDIF(GDCM_USE_WXWIDGETS)

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
    #SET(CPACK_STRIP_FILES "bin/MyExecutable")
    #SET(CPACK_SOURCE_STRIP_FILES "")
  ENDIF(WIN32 AND NOT UNIX)

#TODO FIXME
    SET(CPACK_NSIS_CONTACT "gdcm-developers@lists.sourceforge.net")

  # List executables
  SET(CPACK_PACKAGE_EXECUTABLES "gdcmviewer" "VIEWER")
  INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

#-----------------------------------------------------------------------------
OPTION(GDCM_BUILD_WRAPPING "wrapping ?" OFF)
SET(BUILD_WRAPPING ${GDCM_BUILD_WRAPPING})
IF(BUILD_WRAPPING)
  SUBDIRS(Wrapping)
ENDIF(BUILD_WRAPPING)


SUBDIRS(CMake/ExportConfiguration)

