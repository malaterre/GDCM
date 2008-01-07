# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)

# Define the src for the vtk-gdcm bridge
SET(VTK_GDCM_SRCS
  vtkGDCMReader.cxx
  vtkGDCMWriter.cxx
  )

INCLUDE(${VTK_USE_FILE})
INCLUDE_DIRECTORIES(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
  )

ADD_LIBRARY(vtkgdcm ${VTK_GDCM_SRCS})
TARGET_LINK_LIBRARIES(vtkgdcm gdcmMSFF vtkIO)

IF(BUILD_WRAPPING)
  IF(VTK_WRAP_PYTHON)
    SET(VTK_GDCM_PYTHON_SRCS
      ${VTK_GDCM_SRCS}
    )
    INCLUDE("${VTK_CMAKE_DIR}/vtkWrapPython.cmake")
    VTK_WRAP_PYTHON2(vtkgdcmPython WRAP_VTK_GDCM_PYTHON_SRCS
      ${VTK_GDCM_PYTHON_SRCS})
    INCLUDE_DIRECTORIES(
      ${CMAKE_CURRENT_SOURCE_DIR}
    )
    ADD_LIBRARY(vtkgdcmPython MODULE ${WRAP_VTK_GDCM_PYTHON_SRCS})
    TARGET_LINK_LIBRARIES(vtkgdcmPython vtkgdcm vtkCommonPythonD vtkIOPythonD)
  ENDIF(VTK_WRAP_PYTHON)
ENDIF(BUILD_WRAPPING)

IF(BUILD_TESTING)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

