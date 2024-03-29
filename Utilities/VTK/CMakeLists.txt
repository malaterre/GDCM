project(vtkgdcm)
# We need VTK
# Technically we require VTK 5.0 and above

# Define the src for the vtk-gdcm bridge
set(vtkgdcm_SRCS
  vtkGDCMTesting.cxx
  vtkGDCMImageReader.cxx
  vtkGDCMImageWriter.cxx
  vtkGDCMMedicalImageProperties.cxx
  )

if(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)
  set(vtkgdcm_SRCS ${vtkgdcm_SRCS}
  vtkGDCMThreadedImageReader.cxx
  )
endif()

if(VTK_VERSION VERSION_LESS 8.90)
  include(${VTK_USE_FILE})
else()
  if(VTK::RenderingCore IN_LIST VTK_LIBRARIES)
    # VTK 5 used to export VTK_USE_RENDERING, now we set it ourselves
    set(VTK_USE_RENDERING 1)
  endif()
endif()

if( ${VTK_MAJOR_VERSION} GREATER 5 )
  list(APPEND vtkgdcm_SRCS
    vtkGDCMImageReader2.cxx
  )
endif()

include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_INCLUDES ${VTK_INCLUDE_DIRS})
CHECK_CXX_SOURCE_COMPILES(
  "\#include <vtkSmartVolumeMapper.h>\nint main() { vtkSmartVolumeMapper* p; return 0;}"
  VTK_HAS_SMARTVOLUMEMAPPER)
CHECK_CXX_SOURCE_COMPILES(
  "\#include <vtkImageResliceMapper.h>\nint main() { vtkImageResliceMapper* p; return 0;}"
  VTK_HAS_IMAGERESLICEMAPPER)

include_directories(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
  ${GDCM_SOURCE_DIR}/Source/DataDictionary
  ${GDCM_BINARY_DIR}/Utilities/VTK
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )

# FIXME: temp fix
#if(UNIX)
#  link_directories(/usr/X11R6/lib)
#endif()

# List the kits from VTK that are needed by this project.
if("${VTK_MAJOR_VERSION}" LESS 6)
  set(vtkgdcm_LIBS
    vtkCommon
    vtkFiltering
    vtkIO
    vtkImaging
  )
  if(VTK_USE_RENDERING)
    set(vtkgdcm_LIBS
      ${vtkgdcm_LIBS}
      vtkRendering
      )
  endif()
elseif(VTK_VERSION VERSION_LESS 8.90)
  set(vtkgdcm_LIBS
    vtkCommonCore
    vtkImagingCore
    vtkImagingSources
    vtkIOImage
    vtkIOLegacy
    #vtksys
  )
  set(vtkgdcm_COND_LIBS
    vtkIOMPIImage
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingFreeTypeOpenGL
    vtkFiltersParallelDIY2
  )
  if(("${VTK_MAJOR_VERSION}" EQUAL 6) OR ("${VTK_RENDERING_BACKEND}" STREQUAL "OpenGL"))
    list(APPEND vtkgdcm_COND_LIBS vtkRenderingOpenGL)
  else()
    list(APPEND vtkgdcm_COND_LIBS vtkRenderingOpenGL2)
  endif()
  foreach(TMP_LIB ${VTK_LIBRARIES})
    foreach(TRY_LIB ${vtkgdcm_COND_LIBS})
      if("${TMP_LIB}" STREQUAL "${TRY_LIB}")
        set(vtkgdcm_LIBS ${vtkgdcm_LIBS} "${TRY_LIB}")
      endif()
    endforeach()
  endforeach()
elseif() # (VTK_VERSION VERSION_LESS 8.90)
  # for VTK 9, target dependencies are handled automatically
  set(vtkgdcm_LIBS)
endif()

# Use wrapping hints for this project.
#set(VTK_WRAP_HINTS "${PROJECT_SOURCE_DIR}/hints")

# Create the instantiator for these classes.
# FIXME: Are instantiator really needed when only doing python wrapping ?
if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  set(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkMedicalImageProperties.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkStringArray.cxx
  )
  # Setup vtkInstantiator registration for this library's classes.
  include_directories(
    ${GDCM_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4
  )
  VTK_MAKE_INSTANTIATOR2(
    "${VTKGDCM_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
    EXPORT_MACRO "" #GDCM_EXPORT
    HEADER_LOCATION ${GDCM_BINARY_DIR}
  )
else()
  set(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToWindowLevelColors2.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageYBRToRGB.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageRGBToYBR.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMPolyDataReader.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMPolyDataWriter.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkRTStructSetProperties.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkLookupTable16.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToColors16.cxx
    #${CMAKE_CURRENT_SOURCE_DIR}/vtkImagePlanarComponentsToComponents.cxx
  )

  if(VTK_USE_RENDERING OR vtkRenderingCore_LOADED)
    set(vtkgdcm_SRCS ${vtkgdcm_SRCS}
      ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageColorViewer.cxx
      )
  endif()

  #if(GDCM_HAVE_PTHREAD_H)
    set(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    vtkGDCMThreadedImageReader2.cxx
    )
  #endif()

  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0 )
    set(VTK_USE_INSTANTIATOR_NEW 1)
    VTK_MAKE_INSTANTIATOR3(
      "${VTKGDCM_NAME}Instantiator"
      vtkgdcmInstantiator_SRCS
      "${vtkgdcm_SRCS}"
      "" #"VTK_${VTKGDCM_NAME}_EXPORT"
      ${PROJECT_BINARY_DIR}
      "" #"${VTKGDCM_NAME}Configure.h"
    )
  endif()
endif()

if(VTK_VERSION VERSION_LESS 8.90)

#Hum... not sure why this is needed.
#if(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)
#  add_library(vtkgdcm STATIC ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#else()
  add_library(${VTKGDCM_NAME} ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#endif()

set_target_properties(${VTKGDCM_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
target_link_libraries(${VTKGDCM_NAME} LINK_PRIVATE gdcmMSFF ${vtkgdcm_LIBS})
if(GDCM_HAVE_PTHREAD_H)
  target_link_libraries(${VTKGDCM_NAME} LINK_PRIVATE pthread)
endif()
if(NOT GDCM_INSTALL_NO_LIBRARIES)
  install(TARGETS ${VTKGDCM_NAME}
    EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKLibraries
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKLibraries #${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKDebugDevel
  )
#if(NAMELINK_ONLY)
#  install(TARGETS vtkgdcm
#    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT DebugDevel ${NAMELINK_ONLY}
#  )
#  endif()
endif()

# Generate the header file for VTKGDCM_EXPORT
configure_file(vtkgdcmModule.h.in
  "${CMAKE_CURRENT_BINARY_DIR}/vtkgdcmModule.h" COPYONLY)

if(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  set(header_files_glob "${CMAKE_CURRENT_BINARY_DIR}/*.h" "*.h" "*.txx")
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    set(header_files_glob ${header_files_glob}
      "VTK4/*.h"
    )
  endif()
  file(GLOB header_files ${header_files_glob})
  install(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT VTKHeaders
  )
endif()

elseif(DEFINED VTK_MODULE_ENABLE_GDCM_vtkgdcm)
  # When building as a module for VTK 8.90 or later
  set(vtkgdcm_SRC_HDRS)
  foreach(_src ${vtkgdcm_SRCS})
    get_filename_component(_base ${_src} NAME_WE)
    list(APPEND vtkgdcm_SRC_HDRS ${_base}.h)
  endforeach()
  vtk_module_add_module(GDCM::vtkgdcm
    SOURCES ${vtkgdcm_SRCS}
    HEADERS ${vtkgdcm_SRC_HDRS} ${vtkgdcm_HDRS})
  vtk_module_link(GDCM::vtkgdcm
    PRIVATE gdcmMSFF)
endif()

if(GDCM_WRAP_PHP)
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    message(FATAL_ERROR "you need a newer VTK version >= 5.0")
  endif()

  find_package(PHP5 REQUIRED)
  include_directories(
    ${PHP5_INCLUDE_PATH}
    )

  find_package(SWIG REQUIRED)
  mark_as_advanced(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
  include(${SWIG_USE_FILE})
  set_source_files_properties(vtkgdcm.i PROPERTIES CPLUSPLUS ON)
  #set_source_files_properties(vtkgdcm.i PROPERTIES COMPILE_FLAGS -DUSEACTIVIZ)
  #if(GDCM_USE_ACTIVIZ)
  #set(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue -DUSEACTIVIZ")
  #else()
  #set(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue")
  #endif()
  #separate_arguments(CMAKE_SWIG_FLAGS)

  SWIG_ADD_LIBRARY(
    php_vtkgdcm
    LANGUAGE php
    SOURCES vtkgdcm.i
  )
  SWIG_LINK_LIBRARIES(php_vtkgdcm vtkgdcm)
  target_link_libraries(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} LINK_PRIVATE ${vtkgdcm_LIBS})
  if(UNIX)
    set_target_properties(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTIES OUTPUT_NAME "vtkgdcm")
  endif()
  set_target_properties(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTIES PREFIX "")
  set_property(TARGET ${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTY NO_SONAME 1)

if(NOT GDCM_INSTALL_NO_LIBRARIES)
  install(TARGETS ${SWIG_MODULE_php_vtkgdcm_REAL_NAME}
    EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries
  )
#if(NAMELINK_ONLY)
#  install(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
#    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT DebugDevel ${NAMELINK_ONLY}
#  )
#  endif()

# See gdcm bug #3175803
if(${SWIG_VERSION} LESS 2.0.2)
add_custom_command(TARGET ${SWIG_MODULE_php_vtkgdcm_REAL_NAME}
  PRE_BUILD
  COMMAND sed -i -e 's/zend_error_noreturn/zend_error/g' "${swig_generated_file_fullname}"
  COMMENT "Patching zend_error_noreturn into zend_error"
  )
endif()

# Let's copy vtkgdcm.php into the bin dir:
add_custom_command(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vtkgdcm.php ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT "copying vtkgdcm.php"
)
add_custom_target(VTKGDCMPHP ALL
  DEPENDS ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  COMMENT "building vtkgdcm.php"
)
      install(FILES ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
        DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKPythonModule
      )

endif()
endif()

if(VTKGDCM_WRAP_CSHARP)
  if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    message(FATAL_ERROR "you need a newer VTK version >= 5.0")
  endif()
  if(GDCM_USE_ACTIVIZ)
    find_package(ACTIVIZ REQUIRED)
  else()
    message(STATUS "You are using the SWIG version of VTKGDCM. This is not compatible with Activiz")
    find_package(SWIG REQUIRED)
    mark_as_advanced(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
    include(${SWIG_USE_FILE})
    set_source_files_properties(vtkgdcm.i PROPERTIES CPLUSPLUS ON)
    #set_source_files_properties(vtkgdcm.i PROPERTIES COMPILE_FLAGS -DUSEACTIVIZ)
  endif()
  if(GDCM_USE_ACTIVIZ)
    #set(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue -DUSEACTIVIZ")
  else()
    set(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue")
    separate_arguments(CMAKE_SWIG_FLAGS)
    SWIG_ADD_LIBRARY(
      vtkgdcmsharpglue
      LANGUAGE csharp
      SOURCES vtkgdcm.i
    )
    target_link_libraries(${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} LINK_PRIVATE vtkgdcm)
    # Stupid cmake-swig module is doing that for us, when not needed
    if(UNIX)
      set_target_properties(${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} PROPERTIES PREFIX "lib")
    endif()
    target_link_libraries(${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} LINK_PRIVATE ${vtkgdcm_LIBS})
    if(NOT GDCM_INSTALL_NO_LIBRARIES)
      install(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
        EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_VTK_INSTALL_CSHARPMODULE_DIR} COMPONENT Applications
        LIBRARY DESTINATION ${GDCM_VTK_INSTALL_CSHARPMODULE_DIR} COMPONENT Libraries
        )
    endif()
  endif()

  configure_file(
    ${GDCM_SOURCE_DIR}/Wrapping/Csharp/key.snk
    ${CMAKE_CURRENT_BINARY_DIR}/key.snk
    COPYONLY)

  if(GDCM_USE_ACTIVIZ)
    find_package(Mummy REQUIRED)
    mark_as_advanced(Mummy_DIR)
    if(NOT Mummy_BASE_DIR)
      message(FATAL_ERROR "error: Mummy_BASE_DIR not defined. Please set Mummy_DIR to the directory containing MummyConfig.cmake")
    endif()
    include("${Mummy_DIR}/MummyCMakeMacros.cmake")
    if(NOT mummy_EXECUTABLE)
      find_program(mummy_EXECUTABLE mummy)
    endif()
    mark_as_advanced(mummy_EXECUTABLE)
    if(NOT mummy_EXECUTABLE)
      message(FATAL_ERROR "error: mummy not found. mummy_EXECUTABLE='${mummy_EXECUTABLE}'")
    endif()

    if(NOT castxml_EXECUTABLE)
      find_program(castxml_EXECUTABLE castxml)
    endif()
    mark_as_advanced(castxml_EXECUTABLE)
    if(NOT castxml_EXECUTABLE)
      message(FATAL_ERROR "error: castxml not found. castxml_EXECUTABLE='${castxml_EXECUTABLE}'")
    endif()
    set(castxml_include_args "")
    foreach(dir ${Mummy_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})
      set(castxml_include_args ${castxml_include_args} "-I${dir}")
    endforeach()
    configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/MummySettings.xml.in"
      "${CMAKE_CURRENT_BINARY_DIR}/xml/MummySettings.xml"
      @ONLY
      )
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/csharp")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/export-layer")

    set(theclasslist
      vtkGDCMImageReader
      vtkGDCMImageWriter
      vtkGDCMMedicalImageProperties
      vtkGDCMPolyDataReader
      vtkGDCMPolyDataWriter
      vtkGDCMTesting
      vtkGDCMThreadedImageReader
      vtkGDCMThreadedImageReader2
      vtkImageColorViewer
      vtkImageMapToColors16
      vtkImageMapToWindowLevelColors2
      #vtkImagePlanarComponentsToComponents
      vtkImageRGBToYBR
      vtkImageYBRToRGB
      vtkLookupTable16
      vtkRTStructSetProperties
      )
    set(kits gdcm)
    # foreach kit
    set(kit gdcm)
    foreach(class ${theclasslist})
      if(NOT VTK_CLASS_WRAP_EXCLUDE_${class})
        #set(header "${VTK_${ukit}_HEADER_DIR}/${class}.h")
        set(header "${CMAKE_CURRENT_SOURCE_DIR}/${class}.h")
        set(cxxclass "${class}")

        # handle full paths
        if("${class}" MATCHES "^(\\/|.\\/|.\\\\|.:\\/|.:\\\\)")
          set(header "${class}.h")
          string(REGEX MATCH "[^/]*$" cxxclass "${class}")

          get_filename_component(dir "${header}" PATH)
          include_directories("${dir}")
        endif()

        set(abstract 0)
        if(VTK_CLASS_ABSTRACT_${class})
          set(abstract 1)
          set_source_files_properties(${header} PROPERTIES ABSTRACT 1)
        endif()

        # Build one master in-memory table so that we don't have to re-do all the
        # logic in this nested FOREACH loop later on... Instead we'll simply iterate
        # the in-memory table built here:
        #
        set(WRAPPED_CLASS_TABLE ${WRAPPED_CLASS_TABLE} "${cxxclass} ${kit} ${abstract} ${header}")


        set(include_source_text "")
        string(REGEX REPLACE "(.*).h" "\\1.cxx" source "${header}")
        if(EXISTS "${source}")
          set(include_source_text "#include \"${source}\"")
        else()
          #message(FATAL_ERROR "error: Source file '${source}' does not exist...")
        endif()

        configure_file(
          "${CMAKE_CURRENT_SOURCE_DIR}/gccxml.cxx.in"
          "${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx"
          @ONLY
        )

        add_custom_command(
          OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
          COMMAND ${castxml_EXECUTABLE}
          ARGS
	    --castxml-gccxml
            -o ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
            --castxml-start _cable_
            ${castxml_include_args} -DCABLE_CONFIGURATION
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx
          # Remove the "Converter" and "Destructor" XML tags that are
          # generated by "castxml" with a format that is different
          # from that of "gccxml", and thus that are not properly
          # understood by "mummy". Removing these tags does not seem
          # to modify the output of "mummy".
          COMMAND sed
          ARGS
            -i
            "/^  <\\(Converter\\|Destructor\\) /d"
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
          DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx
            ${header}
            ${gccxml_EXECUTABLE}
	  VERBATIM
        )

#
# *before* custom command re-arranging:
#
#          OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs
#            ${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx
#
# Do not list the *.cs or *EL.cxx files as outputs of this custom command.
# If you do, the custom command chains out into other targets rather than
# being defined solely in the "generate wrappers" custom target.
#
# The output of this command is the generated sentinel file that the
# "generate wrappers" target depends on. The other files are generated as an
# intentional "side effect" and after the target is done building, the other
# targets that build the generated source code may build... That is controlled
# by target level dependencies to reduce complexity.
#
        add_custom_command(
          OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt
          COMMAND ${mummy_EXECUTABLE}
            --suppress-warnings 6005 6006 6009 6010 6012 6013 6015 6016 6017 6018 6019
            --settings-file ${CMAKE_CURRENT_BINARY_DIR}/xml/MummySettings.xml
            --gccxml-file ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
            --csharp-file ${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs
            --export-layer-file ${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx
          COMMAND ${CMAKE_COMMAND} -E touch
            ${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt
          DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
            ${CMAKE_CURRENT_BINARY_DIR}/xml/MummySettings.xml
            ${mummy_EXECUTABLE}
            ${${cxxclass}_EXTRA_DEPENDENCIES}
        )

        set(${kit}_EL_SOURCES ${${kit}_EL_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx")
        set(ALLKITS_EL_SOURCES ${ALLKITS_EL_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx")

        set(${kit}_CS_SOURCES ${${kit}_CS_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs")
        set(ALLKITS_CS_SOURCES ${ALLKITS_CS_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs")

        set(${kit}_SENTINELS ${${kit}_SENTINELS} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt")
        set(ALLKITS_SENTINELS ${ALLKITS_SENTINELS} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt")
      endif()
    endforeach()

    add_custom_target(
      "vtk${kit}GenerateWrappers" ALL
      DEPENDS ${${kit}_SENTINELS}
      )
    set_source_files_properties(
      ${ALLKITS_EL_SOURCES}
      ${ALLKITS_CS_SOURCES}
      PROPERTIES GENERATED 1)

    if(VTK_BUILD_SHARED_LIBS)
      set(MV_ONE_EXPORT_LAYER_DLL 0)
    else()
      set(MV_ONE_EXPORT_LAYER_DLL 1)
    endif()

    if(MV_ONE_EXPORT_LAYER_DLL)
      message(FATAL_ERROR "Unimplemented")
      #set(AVDN_INSTALL_TARGETS ${AVDN_INSTALL_TARGETS} "Kitware.VTK.Unmanaged")
      #add_library(Kitware.VTK.Unmanaged SHARED ${ALLKITS_EL_SOURCES})
      #set(unmanaged_targets ${unmanaged_targets} "Kitware.VTK.Unmanaged")
      #set(unmanaged_dlls ${unmanaged_dlls} "${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
      #if(WIN32)
      #  target_link_libraries(Kitware.VTK.Unmanaged "${exe_dir}/Kitware.mummy.Runtime.Unmanaged.lib")
      #else()
      #  target_link_libraries(Kitware.VTK.Unmanaged "${exe_dir}/${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.mummy.Runtime.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
      #endif()
      ## TODO -- rename this CopyLibraries here too...
      #add_dependencies(Kitware.VTK.Unmanaged Kitware.mummy.CopyLibraries2)
      #foreach(kit ${kits})
      #  target_link_libraries(Kitware.VTK.Unmanaged vtk${kit})
      #  add_dependencies(Kitware.VTK.Unmanaged "vtk${kit}GenerateWrappers")
      #endforeach()
    else()
      include_directories(${Mummy_INCLUDE_DIRS})
      foreach(kit ${kits})
        set(AVDN_INSTALL_TARGETS ${AVDN_INSTALL_TARGETS} "Kitware.VTK.vtk${kit}.Unmanaged")
        add_library(Kitware.VTK.vtk${kit}.Unmanaged SHARED ${${kit}_EL_SOURCES})
        set(unmanaged_targets ${unmanaged_targets} "Kitware.VTK.vtk${kit}.Unmanaged")
        set(unmanaged_dlls ${unmanaged_dlls} "${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.vtk${kit}.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
        if(WIN32)
          target_link_libraries(Kitware.VTK.vtk${kit}.Unmanaged "${exe_dir}/Kitware.mummy.Runtime.Unmanaged.lib")
        else()
          target_link_libraries(Kitware.VTK.vtk${kit}.Unmanaged ${Mummy_RUNTIME_LINK_LIBRARIES})
        endif()
        target_link_libraries(Kitware.VTK.vtk${kit}.Unmanaged vtk${kit})
        target_link_libraries(Kitware.VTK.vtk${kit}.Unmanaged vtkCommon)
        set_property(TARGET Kitware.VTK.vtk${kit}.Unmanaged PROPERTY NO_SONAME 1)
        # TODO -- rename this CopyLibraries here too...
        add_dependencies(Kitware.VTK.vtk${kit}.Unmanaged Kitware.mummy.CopyLibraries2)
        add_dependencies(Kitware.VTK.vtk${kit}.Unmanaged "vtk${kit}GenerateWrappers")
      endforeach()
    endif()

    set(csc_EXECUTABLE ${CMAKE_CSHARP_COMPILER})
    # Set list of export-layer dlls in C# syntax as CMake variable
    # MV_EXPORTLAYER_DLL_VARIABLES. This gets configured into
    # WrappedObject.cs below.
    #
    set(MV_EXPORTLAYER_DLL_VARIABLES "")
    foreach(kit ${kits})
      set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// <summary>\n")
      set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// Export layer functions for 'vtk${kit}' are exported from\n")
      set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// the DLL named by the value of this variable.\n")
      set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// </summary>\n")

      if(MV_ONE_EXPORT_LAYER_DLL)
        set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    public const string vtk${kit}EL_dll = \"${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}\";\n")
      else()
        set(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    public const string vtk${kit}EL_dll = \"${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.vtk${kit}.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}\";\n")
      endif()
    endforeach()

    set(csharp_namespace "Kitware.VTK.GDCM")
    configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in"
      "${CMAKE_CURRENT_BINARY_DIR}/csharp/AssemblyInfo.cs"
      @ONLY
      )

    set(ALLKITS_CS_SOURCES
      ${ALLKITS_CS_SOURCES}
      "${CMAKE_CURRENT_BINARY_DIR}/csharp/AssemblyInfo.cs"
      ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMImageReader_Extra.cs
      )

    set(AVDN_VTK_CSC_REFS ${ACTIVIZ_KITWARE_VTK_LIBRARY} ${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY})
    ADD_CSHARP_LIBRARY(
      "Kitware.VTK.GDCM" # name of library
      "${unmanaged_targets}" # list of CMake targets that need to build first
      "${AVDN_VTK_CSC_REFS}" # list of csc "/reference:" args
      "${unmanaged_dlls}" # list of csc "/linkresource:" args
      "${AVDN_SNKEYFILE}" # strong name signing keyfile
      # Source files:
      ${ALLKITS_CS_SOURCES}
      )

    foreach(kit ${kits})
      add_dependencies(Kitware.VTK.GDCM "vtk${kit}GenerateWrappers")
    endforeach()

    #    add_custom_command(
    #      OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
    #      COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${ACTIVIZ_KITWARE_VTK_LIBRARY}" "/r:${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY}" "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
    #      #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
    #      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #      DEPENDS "${swig_generated_file_fullname}"
    #      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    #      COMMENT "csc *.cs"
    #      )

    install(FILES
      ${GDCM_LIBRARY_DIR}/Kitware.VTK.GDCM.dll
      ${GDCM_LIBRARY_DIR}/Kitware.VTK.GDCM.xml
      DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKCSharpModule
      )
    install(TARGETS Kitware.VTK.vtk${kit}.Unmanaged
      EXPORT ${GDCM_TARGETS_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKLibraries
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKLibraries #${NAMELINK_SKIP}
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKDebugDevel
      )
  else()
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
      @ONLY)

    add_custom_command(
      OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
      COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      DEPENDS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} 
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
      COMMENT "csc *.cs"
      )
    add_custom_target(VTKGDCMCSharp ALL
      DEPENDS
      ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
      #${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll.config
      #${GDCM_EXECUTABLE_DIR}/HelloWorld.exe
      COMMENT "building vtkgdcm-sharp.dll"
      )
    # because vtkgdcm-sharp.dll is constructed with custom commands, it need the install(FILES signature:
    set(GDCM_LIBRARY_DIR2 ${LIBRARY_OUTPUT_PATH}/\${BUILD_TYPE})
    install(FILES
      ${GDCM_LIBRARY_DIR2}/vtkgdcm-sharp.dll
      #${GDCM_LIBRARY_DIR2}/vtkgdcm-sharp.dll.config
      DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKCSharpModule
      )
  endif()

  #add_custom_command(
  #  OUTPUT  ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll.config
  #  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config ${GDCM_LIBRARY_DIR}
  #  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config
  #  COMMENT "Copying vtkgdcm-sharp.dll.config"
  #)

endif()

if(VTK_VERSION VERSION_LESS 8.90)

if( (GDCM_WRAP_JAVA AND VTK_WRAP_JAVA) OR
    (GDCM_WRAP_PYTHON AND VTK_WRAP_PYTHON) )
  if( ${VTK_MAJOR_VERSION} GREATER 7 )
    set(MODULE_HIERARCHY_NAME ${VTKGDCM_NAME}Hierarchy)
    set(${VTKGDCM_NAME}_WRAP_DEPENDS ${vtkgdcm_LIBS})
    include(vtkWrapHierarchy)
    vtk_wrap_hierarchy(${VTKGDCM_NAME} ${CMAKE_CURRENT_BINARY_DIR} "${vtkgdcm_SRCS}")
    set(KIT_HIERARCHY_FILE ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.txt)
    set(LIB_HIERARCHY_STAMP ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.stamp.txt)
  endif()
endif()

if(GDCM_WRAP_JAVA)
  if(VTK_WRAP_JAVA)
    find_package(Java ${GDCM_DEFAULT_JAVA_VERSION} REQUIRED) # javac, jar
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})
    set(VTK_WRAP_JAVA3_INIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    # Lars Matthaus patch (package vtk => imply vtk subdir )
    set(VTK_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/vtk)
    # This is *required* don't ask
    file(MAKE_DIRECTORY ${VTK_JAVA_HOME})
    include(${VTK_CMAKE_DIR}/vtkWrapJava.cmake)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    # libvtk-java is a pain to handle...
    if(EXISTS ${VTK_JAVA_JAR})
      # http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=533193
      set(GDCM_VTK_JAVA_JAR ${VTK_JAVA_JAR})
    else()
      # http://bugs.debian.org/834493
      find_file(VTK_JAVA_JAR NAMES vtk.jar vtk6.jar vtk5.jar
        PATHS ${vtkWrappingJava_RUNTIME_LIBRARY_DIRS} /usr/share/java)
      set(GDCM_VTK_JAVA_JAR ${VTK_JAVA_JAR})
    endif()
    if(EXISTS /usr/lib/jni/libvtkCommonJava.so)
      # http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=533198
      message(STATUS "Implicitly adding debian package layout...")
      link_directories("/usr/lib/jni")
    endif()
    mark_as_advanced(GDCM_VTK_JAVA_JAR)
    if(EXISTS ${GDCM_VTK_JAVA_JAR})
    VTK_WRAP_JAVA3(${VTKGDCM_NAME}Java vtkgdcmJAVA_SRCS "${vtkgdcm_SRCS}")
    add_library(${VTKGDCM_NAME}Java SHARED ${vtkgdcmJAVA_SRCS})
    # special jnilib extension:
    if(APPLE)
      set_target_properties(${VTKGDCM_NAME}Java PROPERTIES SUFFIX ".jnilib")
    endif()
    target_link_libraries(${VTKGDCM_NAME}Java LINK_PRIVATE ${VTKGDCM_NAME})
    set_property(TARGET ${VTKGDCM_NAME}Java PROPERTY NO_SONAME 1)
    # By default link those module since APPLE and WIN32 needs fully resolved
    # shared lib allow advanced users to skip the link step:
    if(NOT GDCM_NO_VTKJAVA_LIBS_LINKING)
      foreach(c ${vtkgdcm_LIBS})
        target_link_libraries(${VTKGDCM_NAME}Java LINK_PRIVATE ${c}Java)
      endforeach()
    endif()
    # Create the jar file:
    # I am pretty sure this *.java thingy will bite me one day, when someone will try
    # to recompile from an existing build tree with invalid generated *.java file...
    set(jflags $ENV{JFLAGS})
    add_custom_command(
      OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      #COMMAND ${Java_JAVAC_EXECUTABLE} ARGS -cp ${GDCM_VTK_JAVA_JAR} "vtk/*.java"
      # No such thing as -cp for javac only java is listed:
      # http://java.sun.com/j2se/1.5.0/docs/tooldocs/windows/classpath.html
      COMMAND ${Java_JAVAC_EXECUTABLE} ARGS ${jflags} -source ${GDCM_JAVA_SOURCE_VERSION} -target ${GDCM_JAVA_TARGET_VERSION} -classpath ${GDCM_VTK_JAVA_JAR} -d . "vtk/*.java"
      COMMAND ${Java_JAR_EXECUTABLE} ARGS -cvfm ${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.jar ${CMAKE_CURRENT_SOURCE_DIR}/manifest.txt vtk/*.class
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/java
      DEPENDS ${VTKGDCM_NAME}Java
      #${VTK_JAVA_DEPENDENCIES}
      #vtkgdcmJavaJavaClasses
      COMMENT   "javac *.java -> jar; jar cvf -> vtkgdcm.jar"
    )
    # Target to execute custom command:
    add_custom_target(VTKGDCMJavaJar ALL
      DEPENDS ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      COMMENT "building vtkgdcm.jar"
    )
    add_dependencies(VTKGDCMJavaJar vtkgdcmJavaJavaClasses)

    # Install rules:
    if(NOT GDCM_INSTALL_NO_LIBRARIES)
      install(TARGETS ${VTKGDCM_NAME}Java
      EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_VTK_INSTALL_JAVAMODULE_DIR} COMPONENT VTKJavaModule
        LIBRARY DESTINATION ${GDCM_VTK_INSTALL_JAVAMODULE_DIR} COMPONENT VTKJavaModule
      )
  #DebugDevel
  #if(NAMELINK_ONLY)
  #  install(TARGETS ${VTKGDCM_NAME}Java
  #    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKJavaModule ${NAMELINK_ONLY}
  #  )
  #endif()

    # because vtkgdcm.jar is constructed with custom commands, it need the
    # install(FILES signature:
    install(FILES ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      DESTINATION ${GDCM_VTK_INSTALL_JARMODULE_DIR} COMPONENT VTKJavaModule
      )
    endif()


    else()
      message(WARNING "Could not find vtk.jar file, VTK_JAVA_JAR is wrong: ${VTK_JAVA_JAR}, please set proper GDCM_VTK_JAVA_JAR: ${GDCM_VTK_JAVA_JAR} replacement var")
    endif()
  else()
    message(STATUS "GDCM_WRAP_JAVA cannot be build without VTK_WRAP_JAVA")
  endif()
endif()

if(GDCM_WRAP_PYTHON)
  if(VTK_WRAP_PYTHON)
      set(DEXTENSION "")
    if( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
        VTK_WRAP_PYTHON2(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS ${vtkgdcm_SRCS})
    else()
    include(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
        include_directories(
          ${PYTHON_INCLUDE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
        VTK_WRAP_PYTHON3(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
      set(DEXTENSION "D")
    endif()
    add_library(${VTKGDCM_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    # this is a library set the version:
    # do not set the version on the Python module:
    set_target_properties(${VTKGDCM_NAME}PythonD PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    add_library(${VTKGDCM_NAME}Python MODULE ${VTKGDCM_NAME}PythonInit.cxx)
    # do not set the version on the Python module:
    #set_target_properties(${VTKGDCM_NAME}Python PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    target_link_libraries(${VTKGDCM_NAME}PythonD LINK_PRIVATE ${VTKGDCM_NAME} ${PYTHON_LIBRARY})
    foreach(c ${vtkgdcm_LIBS})
      target_link_libraries(${VTKGDCM_NAME}PythonD LINK_PRIVATE ${c}Python${DEXTENSION})
    endforeach()
    if(TARGET vtkPythonCore)
      target_link_libraries(${VTKGDCM_NAME}PythonD LINK_PRIVATE vtkPythonCore)
    endif()
    target_link_libraries(${VTKGDCM_NAME}Python LINK_PRIVATE ${VTKGDCM_NAME}PythonD)
    if(NOT GDCM_NO_PYTHON_LIBS_LINKING)
      target_link_libraries(${VTKGDCM_NAME}Python LINK_PRIVATE ${PYTHON_LIBRARY})
    endif()
    set_property(TARGET ${VTKGDCM_NAME}Python PROPERTY NO_SONAME 1)
    #set_property(TARGET ${VTKGDCM_NAME}PythonD PROPERTY NO_SONAME 1)
    # Removing lib prefix if we are at VTK7. Based on a reply by David Gobbi to
    # this Thread
    # http://vtk.1045678.n5.nabble.com/python-wrapping-with-VTK-7-td5737442.html
    if( "${VTK_MAJOR_VERSION}" GREATER 6 )
      set_target_properties(${VTKGDCM_NAME}Python PROPERTIES PREFIX "")
    endif()
    # Python extension modules on Windows must have the extension ".pyd"
    # instead of ".dll" as of Python 2.5.  Older python versions do support
    # this suffix.
    if(WIN32 AND NOT CYGWIN)
      set_target_properties(${VTKGDCM_NAME}Python PROPERTIES SUFFIX ".pyd")
    endif()

    add_custom_command(
      TARGET    ${VTKGDCM_NAME}Python
      POST_BUILD
      COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/
      DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py"
      COMMENT   "Copy vtkgdcm.py into ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/"
    )
    if(NOT GDCM_INSTALL_NO_LIBRARIES)
      install(TARGETS ${VTKGDCM_NAME}Python
        EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_VTK_INSTALL_PYTHONMODULE_DIR} COMPONENT                        VTKPythonModule
        LIBRARY DESTINATION ${GDCM_VTK_INSTALL_PYTHONMODULE_DIR} COMPONENT VTKPythonModule #${NAMELINK_SKIP}
        )
      install(TARGETS ${VTKGDCM_NAME}PythonD
        EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKPythonModule
        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKPythonModule #${NAMELINK_ONLY}
        )
    # the python file is not a dev file, but part of the gdcm module...
      install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py
        DESTINATION ${GDCM_VTK_INSTALL_PYTHONMODULE_DIR} COMPONENT VTKPythonModule
      )
    endif()

  else()
    message(STATUS "GDCM_WRAP_PYTHON cannot be build without VTK_WRAP_PYTHON")
  endif()
endif()

if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

endif() #(VTK_VERSION VERSION_LESS 8.90)

if(BUILD_APPLICATIONS)
  add_subdirectory(Applications)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

if(GDCM_USE_PARAVIEW)
  # http://www.cmake.org/Wiki/Plugin_HowTo#Adding_a_Reader
  find_package(ParaView REQUIRED)
  include(${PARAVIEW_USE_FILE})
  ADD_PARAVIEW_PLUGIN(GDCMImageReader "1.0"
    SERVER_MANAGER_SOURCES vtkGDCMImageReader.cxx
    SERVER_MANAGER_XML GDCMImageReader.xml
    GUI_RESOURCE_FILES GDCMImageGUI.xml)
  target_link_libraries(GDCMImageReader ${VTKGDCM_NAME})
  install(TARGETS GDCMImageReader
    EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT ParaViewModule
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT ParaViewModule
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT ParaViewModule
    )

endif()
