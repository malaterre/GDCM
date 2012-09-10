include_directories(
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )


if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
  set(GDCM_VTK_APPS
    ConvertSingleBitTo8Bits
    GenerateRTSTRUCT
    offscreenimage
  )
  if(VTK_USE_RENDERING)
    set(GDCM_VTK_APPS
      ${GDCM_VTK_APPS}
      gdcmorthoplanes
      gdcmreslice
      gdcmrtionplan
      gdcmrtplan
      gdcmscene
      gdcmtexture
      gdcmvolume
      rtstructapp
      )
  endif(VTK_USE_RENDERING)
  if(GDCM_BUILD_TESTING)
    set(GDCM_VTK_APPS
      ${GDCM_VTK_APPS}
      ConvertRGBToLuminance
      Convert16BitsTo8Bits
      ConvertMultiFrameToSingleFrame
      MagnifyFile
      )
    if(GDCM_DATA_EXTRA_ROOT)
      if(VTK_USE_RENDERING)
        set(GDCM_VTK_APPS
          ${GDCM_VTK_APPS}
          reslicesphere
          )
      endif(VTK_USE_RENDERING)
    endif(GDCM_DATA_EXTRA_ROOT)
  endif(GDCM_BUILD_TESTING)
endif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )

foreach(app ${GDCM_VTK_APPS})
  add_executable(${app} ${app}.cxx)
  #set_target_properties(${app} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  target_link_libraries(${app} ${VTKGDCM_NAME} ${vtkgdcm_LIBS})
  target_link_libraries(${app} gdcmDSED gdcmMSFF gdcmCommon)
  if(GDCM_BUILD_TESTING)
    # gdcmTesting is in Common:
    target_link_libraries(${app} gdcmCommon)
  endif(GDCM_BUILD_TESTING)
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
    if(VTK_USE_RENDERING)
      target_link_libraries(${app} vtkWidgets vtkVolumeRendering)
    endif(VTK_USE_RENDERING)
  endif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
endforeach(app)

if(GDCM_HAVE_PTHREAD_H)
# Dev only: I dont need to install that one:
  add_executable(threadgdcm threadgdcm.cxx)
  target_link_libraries(threadgdcm gdcmMSFF pthread vtkIO)
endif(GDCM_HAVE_PTHREAD_H)

#add_executable(gdcm2vtk gdcm2vtk.cxx)
#target_link_libraries(gdcm2vtk gdcmMSFF pthread)
