# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)

# Define the src for the vtk-gdcm bridge
SET(VTK_GDCM_SRCS
  vtkGDCMReader.cxx
  )

INCLUDE(${VTK_USE_FILE})
INCLUDE_DIRECTORIES(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  )

ADD_LIBRARY(vtkgdcm ${VTK_GDCM_SRCS})
TARGET_LINK_LIBRARIES(vtkgdcm gdcmDSED vtkIO)
