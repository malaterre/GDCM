# Build the vtk-gdcm simple viewer
INCLUDE_DIRECTORIES(
#  ${GDCM_BINARY_DIR}/Source/Common
#  ${GDCM_SOURCE_DIR}/Source/Common
#  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )
SET(GDCM_VIEWER_APP_SRCS
  gdcmviewer.cxx
  )

ADD_EXECUTABLE(gdcmviewer ${GDCM_VIEWER_APP_SRCS})
TARGET_LINK_LIBRARIES(gdcmviewer vtkgdcm vtkRendering)
