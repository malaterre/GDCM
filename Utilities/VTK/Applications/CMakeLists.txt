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

# vtkImageViewer
ADD_EXECUTABLE(gdcmviewer MACOSX_BUNDLE ${GDCM_VIEWER_APP_SRCS})
TARGET_LINK_LIBRARIES(gdcmviewer vtkgdcm vtkRendering)

# vtkImageViewer2
ADD_EXECUTABLE(gdcmviewer2 MACOSX_BUNDLE ${GDCM_VIEWER_APP_SRCS})
TARGET_LINK_LIBRARIES(gdcmviewer2 vtkgdcm vtkRendering)

ADD_EXECUTABLE(threadgdcm threadgdcm.cxx)
TARGET_LINK_LIBRARIES(threadgdcm gdcmMSFF pthread vtkIO)

#ADD_EXECUTABLE(gdcm2vtk gdcm2vtk.cxx)
#TARGET_LINK_LIBRARIES(gdcm2vtk gdcmMSFF pthread)

