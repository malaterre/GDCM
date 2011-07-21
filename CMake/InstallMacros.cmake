#
# This module install PDB files.
#
# Based on users posts:
# http://www.cmake.org/pipermail/cmake/2007-October/016924.html
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

MACRO (install_swig_module module_name module_type)
  # The following trick permits installion of module to the right destination:
  # binary path for dll (on windows)
  # library for non-dll platform
  IF(WIN32)
    SET(MODDST ${GDCM_INSTALL_BIN_DIR})
  ELSE()
    SET(MODDST ${GDCM_INSTALL_LIB_DIR})
  ENDIF()
  IF(NOT GDCM_INSTALL_NO_LIBRARIES)
    INSTALL(TARGETS ${SWIG_MODULE_${module_name}_REAL_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT ${module_type}Module
      LIBRARY DESTINATION ${MODDST}               COMPONENT ${module_type}Module
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT ${module_type}Module
      )
  ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
ENDMACRO (install_swig_module)

MACRO (install_library library)
  IF(NOT GDCM_INSTALL_NO_LIBRARIES)
    # Runtime
    INSTALL(TARGETS ${library}
      EXPORT ${GDCM_TARGETS_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries ${NAMELINK_SKIP}
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT DebugDevel
      )
    #Development
    if(NAMELINK_ONLY)
      INSTALL(TARGETS ${library}
        EXPORT ${GDCM_TARGETS_NAME}
        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT DebugDevel ${NAMELINK_ONLY}
        )
    endif(NAMELINK_ONLY)
  ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
ENDMACRO (install_library)

MACRO (install_pdb library)
  if (MSVC)
    IF(CMAKE_CONFIGURATION_TYPES)
      # Visual Studio
      # The following does not work with LOCATION keyword. See:
      # http://www.cmake.org/pipermail/cmake/2011-February/042579.html
      FOREACH(cfg ${CMAKE_CONFIGURATION_TYPES})
        get_target_property(library_dll ${library} LOCATION_${cfg})
        string(REPLACE .dll .pdb library_pdb ${library_dll})
        string(TOLOWER ${cfg} lcfg)
        if(lcfg STREQUAL "debug" OR lcfg STREQUAL "relwithdebinfo")
          install (FILES ${library_pdb}
            DESTINATION ${GDCM_INSTALL_BIN_DIR}
            COMPONENT DebugDevel
            CONFIGURATIONS ${cfg}
            )
        endif()
      ENDFOREACH(cfg ${CMAKE_CONFIGURATION_TYPES})
    ELSE(CMAKE_CONFIGURATION_TYPES)
      # nmake
      # Same as above we need the explicit location_<config> variable to account for
      # the value of CMAKE_DEBUG_POSTFIX
      get_target_property(library_dll ${library} LOCATION_${CMAKE_BUILD_TYPE})
      string(REPLACE .dll .pdb library_pdb ${library_dll})
      string(TOLOWER ${CMAKE_BUILD_TYPE} lcfg)
      if(lcfg STREQUAL "debug" OR lcfg STREQUAL "relwithdebinfo")
        install (FILES ${library_pdb}
          DESTINATION ${GDCM_INSTALL_BIN_DIR}
          COMPONENT DebugDevel
          )
      endif()
    ENDIF(CMAKE_CONFIGURATION_TYPES)
  endif (MSVC)
ENDMACRO (install_pdb)

# At least one argument is required
MACRO (install_includes glob_expression)
  IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
    FILE(GLOB header_files ${glob_expression} ${ARGN})
    INSTALL(FILES ${header_files}
      DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Headers
      )
  ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
ENDMACRO (install_includes)
