# Generate the GDCMConfig.cmake file in the build tree. Also configure
# one for installation. The file tells external projects how to use
# GDCM.

# Help store a literal dollar in a string.  CMake 2.2 allows escaped
# dollars but we have to support CMake 2.0.
SET(DOLLAR "$")

#-----------------------------------------------------------------------------
# Settings shared between the build tree and install tree.

EXPORT_LIBRARY_DEPENDENCIES(
  ${GDCM_BINARY_DIR}/GDCMLibraryDepends.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/CMakeExportBuildSettings.cmake)
CMAKE_EXPORT_BUILD_SETTINGS(
  ${GDCM_BINARY_DIR}/GDCMBuildSettings.cmake)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  INSTALL_FILES(${GDCM_INSTALL_PACKAGE_DIR} FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/UseGDCM.cmake
    ${GDCM_BINARY_DIR}/GDCMLibraryDepends.cmake
    ${GDCM_BINARY_DIR}/GDCMBuildSettings.cmake
    )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

#-----------------------------------------------------------------------------
# Settings specific to the build tree.

# The install-only section is empty for the build tree.
SET(GDCM_CONFIG_INSTALL_ONLY)

# The "use" file.
SET(GDCM_USE_FILE_CONFIG 
  ${CMAKE_CURRENT_SOURCE_DIR}/UseGDCM.cmake)

# The build settings file.
SET(GDCM_BUILD_SETTINGS_FILE_CONFIG 
  ${GDCM_BINARY_DIR}/GDCMBuildSettings.cmake)

# The library directories.
SET(GDCM_LIBRARY_DIRS_CONFIG ${GDCM_LIBRARY_DIRS})

# The runtime directories.
SET(GDCM_RUNTIME_DIRS_CONFIG ${GDCM_RUNTIME_DIRS})

# The include directories.
SET(GDCM_INCLUDE_DIRS_CONFIG ${GDCM_INCLUDE_PATH})

# The library dependencies file.
SET(GDCM_LIBRARY_DEPENDS_FILE 
  ${GDCM_BINARY_DIR}/GDCMLibraryDepends.cmake)

# The CMake macros dir.
SET(GDCM_CMAKE_DIR_CONFIG 
  ${GDCM_CMAKE_DIR})

# The VTK options.
SET(GDCM_VTK_DIR_CONFIG ${VTK_DIR})

# The build configuration information.
SET(GDCM_CONFIGURATION_TYPES_CONFIG ${GDCM_CONFIGURATION_TYPES})
SET(GDCM_BUILD_TYPE_CONFIG ${CMAKE_BUILD_TYPE})

# Configure GDCMConfig.cmake for the build tree.
CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/GDCMConfig.cmake.in
  ${GDCM_BINARY_DIR}/GDCMConfig.cmake @ONLY IMMEDIATE)

#-----------------------------------------------------------------------------
# Settings specific to the install tree.

# The "use" file.
SET(GDCM_USE_FILE_CONFIG 
  ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_PACKAGE_DIR}/UseGDCM.cmake)

# The build settings file.
SET(GDCM_BUILD_SETTINGS_FILE_CONFIG 
  ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_PACKAGE_DIR}/GDCMBuildSettings.cmake)

# The library directories.
IF(CYGWIN AND GDCM_BUILD_SHARED_LIBS)
  # In Cygwin programs directly link to the .dll files.
  SET(GDCM_LIBRARY_DIRS_CONFIG 
    ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_BIN_DIR})
ELSE(CYGWIN AND GDCM_BUILD_SHARED_LIBS)
  SET(GDCM_LIBRARY_DIRS_CONFIG 
    ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_LIB_DIR})
ENDIF(CYGWIN AND GDCM_BUILD_SHARED_LIBS)

# The runtime directories.
IF(WIN32)
  SET(GDCM_RUNTIME_DIRS_CONFIG 
    ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_BIN_DIR})
ELSE(WIN32)
  SET(GDCM_RUNTIME_DIRS_CONFIG 
    ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_LIB_DIR})
ENDIF(WIN32)

# The include directories.
SET(GDCM_INCLUDE_DIRS_CONFIG
  ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_INCLUDE_DIR})

# The library dependencies file.
SET(GDCM_LIBRARY_DEPENDS_FILE 
  ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_PACKAGE_DIR}/GDCMLibraryDepends.cmake)

# The CMake macros dir.
SET(GDCM_CMAKE_DIR_CONFIG 
  ${DOLLAR}{GDCM_INSTALL_PREFIX}${GDCM_INSTALL_PACKAGE_DIR}/CMake)

# The VTK options.
# If VTK_BINARY_DIR is set, then GDCM is part of a larger parent project
# that also builds VTK. In that case, GDCM_VTK_INSTALL_PACKAGE_DIR
# should be set to the value of VTK_INSTALL_PACKAGE_DIR. Otherwise, if not set,
# then we are using an outside VTK whose location will not change when we
# install.
IF(VTK_BINARY_DIR)
  IF(NOT GDCM_VTK_INSTALL_PACKAGE_DIR)
    MESSAGE(
      "GDCM_VTK_INSTALL_PACKAGE_DIR must be set by the parent project to the value of VTK_INSTALL_PACKAGE_DIR it uses to configure VTK.")
  ENDIF(NOT GDCM_VTK_INSTALL_PACKAGE_DIR)
  SET(GDCM_VTK_DIR_CONFIG ${GDCM_VTK_INSTALL_PACKAGE_DIR})
ELSE(VTK_BINARY_DIR)
  SET(GDCM_VTK_DIR_CONFIG ${VTK_DIR})
ENDIF(VTK_BINARY_DIR)

# The build configuration information.
# The install tree only has one configuration.
SET(GDCM_CONFIGURATION_TYPES_CONFIG)

# Configure GDCMConfig.cmake for the install tree.

# Construct the proper number of GET_FILENAME_COMPONENT(... PATH)
# calls to compute the installation prefix from GDCM_DIR.
STRING(REGEX REPLACE "/" ";" GDCM_INSTALL_PACKAGE_DIR_COUNT
  "${GDCM_INSTALL_PACKAGE_DIR}")
SET(GDCM_CONFIG_INSTALL_ONLY "
# Compute the installation prefix from GDCM_DIR.
SET(GDCM_INSTALL_PREFIX \"${DOLLAR}{GDCM_DIR}\")
")
FOREACH(p ${GDCM_INSTALL_PACKAGE_DIR_COUNT})
  SET(GDCM_CONFIG_INSTALL_ONLY
    "${GDCM_CONFIG_INSTALL_ONLY}GET_FILENAME_COMPONENT(GDCM_INSTALL_PREFIX \"${DOLLAR}{GDCM_INSTALL_PREFIX}\" PATH)\n"
    )
ENDFOREACH(p)

IF(CMAKE_CONFIGURATION_TYPES)
  # There are multiple build configurations.  Configure one
  # GDCMConfig.cmake for each configuration.
  FOREACH(config ${CMAKE_CONFIGURATION_TYPES})
    SET(GDCM_BUILD_TYPE_CONFIG ${config})
    CONFIGURE_FILE(
      ${CMAKE_CURRENT_SOURCE_DIR}/GDCMConfig.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/${config}/GDCMConfig.cmake
      @ONLY IMMEDIATE)
  ENDFOREACH(config)

  # Install the config file corresponding to the build configuration
  # specified when building the install target.  The BUILD_TYPE variable
  # will be set while CMake is processing the install files.
  IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
    INSTALL_FILES(${GDCM_INSTALL_PACKAGE_DIR} FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${DOLLAR}{BUILD_TYPE}/GDCMConfig.cmake)
  ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
ELSE(CMAKE_CONFIGURATION_TYPES)
  # There is only one build configuration. Configure one GDCMConfig.cmake.
  SET(GDCM_BUILD_TYPE_CONFIG ${CMAKE_BUILD_TYPE})
  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/GDCMConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/GDCMConfig.cmake @ONLY IMMEDIATE)

  # Setup an install rule for the config file.
  IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
    INSTALL_FILES(${GDCM_INSTALL_PACKAGE_DIR} FILES
      ${CMAKE_CURRENT_BINARY_DIR}/GDCMConfig.cmake)
  ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
ENDIF(CMAKE_CONFIGURATION_TYPES)
