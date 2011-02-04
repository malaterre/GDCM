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

MACRO (install_pdb library component)
  if (MSVC)
    get_target_property(library_dll ${library} LOCATION)
    IF(CMAKE_CONFIGURATION_TYPES)
      # Visual Studio
      FOREACH(cfg ${CMAKE_CONFIGURATION_TYPES})
        string(REPLACE $(OutDir) \${CMAKE_INSTALL_CONFIG_NAME} library_pdb ${library_pdb})
      ENDFOREACH(cfg ${CMAKE_CONFIGURATION_TYPES})
    ELSE(CMAKE_CONFIGURATION_TYPES)
      # nmake
      string(REPLACE .dll .pdb library_pdb ${library_dll})
      install (FILES ${library_pdb}
        DESTINATION ${GDCM_INSTALL_BIN_DIR}
        COMPONENT ${component}
        )
    ENDIF(CMAKE_CONFIGURATION_TYPES)
  endif (MSVC)
ENDMACRO (install_pdb)

