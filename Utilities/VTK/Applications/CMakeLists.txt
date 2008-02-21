# Build the vtk-gdcm simple viewer
INCLUDE_DIRECTORIES(
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )
SET(GDCM_VIEWER_APP_SRCS
  gdcmviewer.cxx
  )
SET(GDCM_VTK_APPS
  gdcmviewer # vtkImageViewer
  gdcmviewer2 # vtkImageViewer2
  )

FOREACH(app ${GDCM_VTK_APPS})
  ADD_EXECUTABLE(${app} 
#MACOSX_BUNDLE 
${GDCM_VIEWER_APP_SRCS})
  TARGET_LINK_LIBRARIES(${app} vtkgdcm vtkRendering)
  IF(NOT GDCM_INSTALL_NO_LIBRARIES)
    INSTALL(TARGETS ${app}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
    )
  ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
ENDFOREACH(app)

IF(LINUX)
# Dev only: I dont need to install that one:
ADD_EXECUTABLE(threadgdcm threadgdcm.cxx)
TARGET_LINK_LIBRARIES(threadgdcm gdcmMSFF pthread vtkIO)
ENDIF(LINUX)

#ADD_EXECUTABLE(gdcm2vtk gdcm2vtk.cxx)
#TARGET_LINK_LIBRARIES(gdcm2vtk gdcmMSFF pthread)

