INCLUDE_DIRECTORIES(
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )


IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
  SET(GDCM_VTK_APPS
    gdcmorthoplanes
    gdcmscene
    gdcmrtion
    gdcmvolume
    gdcmtexture
  )
  IF(GDCM_BUILD_TESTING)
  SET(GDCM_VTK_APPS
    ${GDCM_VTK_APPS}
    ConvertRGBToLuminance
    Convert16BitsTo8Bits
  )
  ENDIF(GDCM_BUILD_TESTING)
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )

FOREACH(app ${GDCM_VTK_APPS})
  ADD_EXECUTABLE(${app} ${app}.cxx)
  #SET_TARGET_PROPERTIES(${app} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  TARGET_LINK_LIBRARIES(${app} ${VTKGDCM_NAME} vtkRendering)
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
    TARGET_LINK_LIBRARIES(${app} vtkWidgets vtkVolumeRendering)
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
ENDFOREACH(app)

IF(CMAKE_HAVE_PTHREAD_H)
# Dev only: I dont need to install that one:
  ADD_EXECUTABLE(threadgdcm threadgdcm.cxx)
  TARGET_LINK_LIBRARIES(threadgdcm gdcmMSFF pthread vtkIO)
ENDIF(CMAKE_HAVE_PTHREAD_H)

#ADD_EXECUTABLE(gdcm2vtk gdcm2vtk.cxx)
#TARGET_LINK_LIBRARIES(gdcm2vtk gdcmMSFF pthread)


