PROJECT(GDCM)
CMAKE_MINIMUM_REQUIRED(VERSION 2.2)

#-----------------------------------------------------------------------------
SET(GDCM_MAJOR_VERSION 0)
SET(GDCM_MINOR_VERSION 0)
SET(GDCM_BUILD_VERSION 0)
SET(GDCM_VERSION 
  "${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}.${GDCM_BUILD_VERSION}")

#-----------------------------------------------------------------------------
# Build shared lib by default
OPTION(GDCM_BUILD_SHARED_LIBS "Build GDCM with shared libraries." ON)
SET(BUILD_SHARED_LIBS ${GDCM_BUILD_SHARED_LIBS})

#-----------------------------------------------------------------------------
SET (EXECUTABLE_OUTPUT_PATH ${GDCM_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
SET (LIBRARY_OUTPUT_PATH ${GDCM_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

#-----------------------------------------------------------------------------
# Adding GDCM_DATA_ROOT
FIND_PATH(GDCM_DATA_ROOT gdcm-ACR-LibIDO.acr
  ${GDCM_SOURCE_DIR}/../gdcmData
  $ENV{GDCM_DATA}
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
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)



#-----------------------------------------------------------------------------
#OPTION(GDCM_DOCUMENTATION "Build source documentation using doxygen." OFF)
## if doxygen enable
#IF(GDCM_DOCUMENTATION)
#  # Search Doxygen:
#  FIND_PACKAGE(Doxygen)
#  IF(DOXYGEN)
#    SUBDIRS(Doc)
#  ENDIF(DOXYGEN)
#ENDIF(GDCM_DOCUMENTATION)

OPTION(GDCM_USE_VTK "vtk bridge ?" OFF)
IF(GDCM_USE_VTK)
  SUBDIRS(Utilities/VTK)
ENDIF(GDCM_USE_VTK)

OPTION(GDCM_BUILD_APPLICATIONS "apps ?" OFF)
SET(BUILD_APPLICATIONS ${GDCM_BUILD_APPLICATIONS})
IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

#-----------------------------------------------------------------------------
# CPack stuff
IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
IF("${GDCM_BINARY_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GDCM - Grass Root DICOM")
  SET(CPACK_PACKAGE_VENDOR "CREATIS")
  SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
  SET(CPACK_PACKAGE_VERSION_MAJOR "${GDCM_MAJOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_MINOR "${GDCM_MINOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_PATCH "${GDCM_BUILD_VERSION}")
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY "GDCM ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
  SET(CPACK_SOURCE_PACKAGE_FILE_NAME "gdcm-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
  SET(CPACK_PACKAGE_EXECUTABLES "gdcmviewer" "VIEWER")

  IF(WIN32)
    #STRING(REGEX REPLACE "/" "\\\\\\\\" CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Release/GDCMInstall.bmp")

    SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\gdcmviewer.exe")
    SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
    SET(CPACK_NSIS_HELP_LINK "http://gdcm.sourceforge.net")
    SET(CPACK_NSIS_URL_INFO_ABOUT "http://gdcm.sourceforge.net")
    SET(CPACK_NSIS_CONTACT "gdcm-developers@lists.sourceforge.net")
  ENDIF(WIN32)

  INCLUDE(CPack)

ENDIF("${GDCM_BINARY_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

