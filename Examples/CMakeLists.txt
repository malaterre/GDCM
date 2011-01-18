CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# Remove these policy lines when CMake 2.6 is the minimum version.
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# Choose behavior based on whether we are building inside the GDCM tree.
IF(GDCM_BINARY_DIR)
SUBDIRS(Cxx)

IF(GDCM_WRAP_PYTHON)
  SUBDIRS(Python)
ENDIF(GDCM_WRAP_PYTHON)

IF(GDCM_WRAP_CSHARP)
  SUBDIRS(Csharp)
ENDIF(GDCM_WRAP_CSHARP)

IF(GDCM_WRAP_JAVA)
  SUBDIRS(Java)
ENDIF(GDCM_WRAP_JAVA)

ELSE(GDCM_BINARY_DIR)

  # We are building outside the GDCM tree.  Build the examples directly.
  PROJECT(GDCMExamples)

  # Find and load the VTK configuration.
  FIND_PACKAGE(GDCM REQUIRED)
  INCLUDE(${GDCM_USE_FILE})

  SUBDIRS(Cxx)

ENDIF(GDCM_BINARY_DIR)
