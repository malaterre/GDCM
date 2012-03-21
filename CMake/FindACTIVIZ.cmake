#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# Testing on Linux with:
# ActiViz.NET-5.4.0.455-Linux-x86_64-Personal

# Note:
# IMHO I cannot use FIND_LIBRARY on Linux because of the .dll extension...
# instead switch to FIND_FILE

FIND_FILE(ACTIVIZ_KITWARE_VTK_LIBRARY
  NAMES Kitware.VTK.dll
  PATHS /usr/lib /usr/local/lib /usr/lib/cli/activiz-cil /usr/lib/cli/ActiViz.NET
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Kitware\\ActiVizDotNet 5.2.1]/bin"
  $ENV{ACTIVIZ_ROOT}/bin
  )

FIND_FILE(ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY
  NAMES Kitware.mummy.Runtime.dll
  PATHS /usr/lib /usr/local/lib /usr/lib/cli/activiz-cil /usr/lib/cli/Kitware.mummy.Runtime-1.0
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Kitware\\ActiVizDotNet 5.2.1]/bin"
  $ENV{ACTIVIZ_ROOT}/bin
  )

IF (ACTIVIZ_KITWARE_VTK_LIBRARY AND ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY)
    SET(ACTIVIZ_LIBRARIES ${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY} ${ACTIVIZ_KITWARE_VTK_LIBRARY})
    SET(ACTIVIZ_FOUND "YES")
ELSE(ACTIVIZ_KITWARE_VTK_LIBRARY AND ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY)
  SET(ACTIVIZ_FOUND "NO")
ENDIF (ACTIVIZ_KITWARE_VTK_LIBRARY AND ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY)


IF (ACTIVIZ_FOUND)
   IF (NOT ACTIVIZ_FIND_QUIETLY)
      MESSAGE(STATUS "Found ACTIVIZ: ${ACTIVIZ_LIBRARIES}")
   ENDIF (NOT ACTIVIZ_FIND_QUIETLY)
ELSE (ACTIVIZ_FOUND)
   IF (ACTIVIZ_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find ACTIVIZ library")
   ENDIF (ACTIVIZ_FIND_REQUIRED)
ENDIF (ACTIVIZ_FOUND)

MARK_AS_ADVANCED(
  ACTIVIZ_KITWARE_VTK_LIBRARY
  ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY
  )
