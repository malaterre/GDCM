# - Find MONO
# This module finds an installed MONO.  It sets the following variables:
#  MONO_FOUND - set to true if MONO is found
#  MONO_DIR - the directory where swig is installed
#  MONO_EXECUTABLE - the path to the swig executable
#  MONO_VERSION   - the version number of the swig executable
#
# All informations are collected from the MONO_EXECUTABLE so the
# version to be found can be changed from the command line by
# means of setting MONO_EXECUTABLE
#
SET(MONO_FOUND FALSE)

# apt-get install mono-jit mono-mcs mono-gac mono-gmcs

# eg.
# $ gmcs HelloWorld.cs
# $ mono HelloWorld.exe

FIND_PROGRAM(MONO_EXECUTABLE mono)
FIND_PROGRAM(MCS_EXECUTABLE mcs)
FIND_PROGRAM(GMCS_EXECUTABLE gmcs)
FIND_PROGRAM(GACUTIL_EXECUTABLE gacutil)

IF(MONO_EXECUTABLE)
# TODO get version
ENDIF(MONO_EXECUTABLE)

IF(NOT MONO_FOUND)
  IF(NOT MONO_FIND_QUIETLY)
    IF(MONO_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "MONO was not found. Please specify Swig executable location")
    ELSE(MONO_FIND_REQUIRED)
      MESSAGE(STATUS "MONO was not found. Please specify Swig executable location")
    ENDIF(MONO_FIND_REQUIRED)
  ENDIF(NOT MONO_FIND_QUIETLY)
ENDIF(NOT MONO_FOUND)

MARK_AS_ADVANCED(MONO_EXECUTABLE MCS_EXECUTABLE GMCS_EXECUTABLE GACUTIL_EXECUTABLE)

