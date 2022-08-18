include_directories(
  ${GDCM_BINARY_DIR}/Utilities/VTK
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )


if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
  set(GDCM_VTK_APPS
    CreateFakeRTDOSE
    CreateFakePET
    ConvertSingleBitTo8Bits
  )
  if(VTK_USE_RENDERING OR vtkRenderingCore_LOADED)
    set(GDCM_VTK_APPS
      ${GDCM_VTK_APPS}
      GenerateRTSTRUCT
      offscreenimage
      )
  endif()
  if( ${VTK_MAJOR_VERSION} GREATER 5 )
    set(GDCM_VTK_APPS
      ${GDCM_VTK_APPS}
      Compute3DSpacing
      )
  endif()
  if(VTK_USE_RENDERING OR vtkRenderingCore_LOADED)
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
  endif()
  if(GDCM_BUILD_TESTING)
    set(GDCM_VTK_APPS
      ${GDCM_VTK_APPS}
      ConvertRGBToLuminance
      Convert16BitsTo8Bits
      ConvertMultiFrameToSingleFrame
      MagnifyFile
      )
    if(GDCM_DATA_EXTRA_ROOT)
      if(VTK_USE_RENDERING OR vtkRenderingCore_LOADED)
        set(GDCM_VTK_APPS
          ${GDCM_VTK_APPS}
          reslicesphere
          )
      endif()
    endif()
  endif()
endif()

foreach(app ${GDCM_VTK_APPS})
  add_executable(${app} ${app}.cxx)
  #set_target_properties(${app} PROPERTIES ${GDCM_EXECUTABLE_PROPERTIES})
  target_link_libraries(${app} ${VTKGDCM_NAME} ${vtkgdcm_LIBS})
  target_link_libraries(${app} gdcmDSED gdcmMSFF gdcmCommon)
  if(GDCM_BUILD_TESTING)
    # gdcmTesting is in Common:
    target_link_libraries(${app} gdcmCommon)
  endif()
  if(NOT VTK_VERSION VERSION_LESS 8.90)
    target_link_libraries(${app}
      VTK::FiltersCore VTK::FiltersModeling VTK::ImagingColor VTK::IOXML)
    set(_rendering_libs
      VTK::InteractionWidgets VTK::RenderingAnnotation VTK::RenderingCore
      VTK::InteractionStyle VTK::RenderingFreeType VTK::RenderingOpenGL2
      VTK::RenderingVolume VTK::RenderingVolumeOpenGL2)
    if(VTK_USE_RENDERING)
      target_link_libraries(${app} ${_rendering_libs})
      vtk_module_autoinit(TARGETS ${app} MODULES ${_rendering_libs})
    endif()
  elseif( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 6.0 )
    target_link_libraries(${app} ${VTK_LIBRARIES})
  else()
    if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 5.0 )
      if(VTK_USE_RENDERING)
        target_link_libraries(${app} vtkWidgets vtkVolumeRendering)
      endif()
    endif()
  endif()
endforeach()

if(GDCM_HAVE_PTHREAD_H)
# Dev only: I dont need to install that one:
  add_executable(threadgdcm threadgdcm.cxx)
  target_link_libraries(threadgdcm gdcmMSFF pthread )
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" GREATER 6.0 )
    target_link_libraries(threadgdcm ${VTK_LIBRARIES})
  else()
    target_link_libraries(threadgdcm vtkIO)
  endif()
endif()

#add_executable(gdcm2vtk gdcm2vtk.cxx)
#target_link_libraries(gdcm2vtk gdcmMSFF pthread)
