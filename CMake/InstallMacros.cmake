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

MACRO (install_library library)
  IF(NOT GDCM_INSTALL_NO_LIBRARIES)
    # Runtime
    INSTALL(TARGETS ${library}
      EXPORT ${GDCM_TARGETS_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries ${NAMELINK_SKIP}
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
      )
    #Development
    if(NAMELINK_ONLY)
      INSTALL(TARGETS ${library}
        EXPORT ${GDCM_TARGETS_NAME}
        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
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
        install (FILES ${library_pdb}
          DESTINATION ${GDCM_INSTALL_BIN_DIR}
          COMPONENT Development
          CONFIGURATIONS ${cfg}
          )
      ENDFOREACH(cfg ${CMAKE_CONFIGURATION_TYPES})
    ELSE(CMAKE_CONFIGURATION_TYPES)
      # nmake
      # Same as above we need the explicit location_<config> variable to account for
      # the value of CMAKE_DEBUG_POSTFIX
      get_target_property(library_dll ${library} LOCATION_${CMAKE_BUILD_TYPE})
      string(REPLACE .dll .pdb library_pdb ${library_dll})
      install (FILES ${library_pdb}
        DESTINATION ${GDCM_INSTALL_BIN_DIR}
        COMPONENT Development
        )
    ENDIF(CMAKE_CONFIGURATION_TYPES)
  endif (MSVC)
ENDMACRO (install_pdb)

MACRO (install_includes glob_expression)
  IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
    FILE(GLOB header_files ${glob_expression})
    INSTALL(FILES ${header_files}
      DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT Headers
      )
  ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
ENDMACRO (install_includes)
