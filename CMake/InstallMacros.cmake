#
# This module install PDB files.
#
# Based on users posts:
# http://www.cmake.org/pipermail/cmake/2007-October/016924.html
#
#  Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
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
    get_target_property(library_dll ${library} LOCATION)
    string(REPLACE .dll .pdb library_pdb ${library_dll})
    IF(CMAKE_CONFIGURATION_TYPES)
      # Visual Studio
      #string(REPLACE "$(OutDir)" "\${BUILD_TYPE}" library_pdb "${library_dll}")
      #string(REPLACE "$(Configuration)" "\${BUILD_TYPE}" library_pdb "${library_dll}")
      string(REPLACE "${CMAKE_CFG_INTDIR}" "\${BUILD_TYPE}" library_pdb "${library_pdb}")
    ELSE(CMAKE_CONFIGURATION_TYPES)
      # nmake
      # nothing to do ...
    ENDIF(CMAKE_CONFIGURATION_TYPES)
    install (FILES ${library_pdb}
      DESTINATION ${GDCM_INSTALL_BIN_DIR}
      COMPONENT Development
      )
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
