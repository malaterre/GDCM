PROJECT(vtkgdcm)
# We need VTK
# Technically we require VTK 5.0 and above
FIND_PACKAGE(VTK REQUIRED)
MARK_AS_ADVANCED(VTK_DIR)

# Define the src for the vtk-gdcm bridge
SET(vtkgdcm_SRCS
  vtkGDCMTesting.cxx
  vtkGDCMImageReader.cxx
  vtkGDCMImageWriter.cxx
  vtkGDCMMedicalImageProperties.cxx
  )

IF(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
  vtkGDCMThreadedImageReader.cxx
  )
ENDIF(GDCM_HAVE_PTHREAD_H AND CMAKE_USE_PTHREADS)

INCLUDE(${VTK_USE_FILE})

INCLUDE(CheckCXXSourceCompiles)
SET(CMAKE_REQUIRED_INCLUDES ${VTK_INCLUDE_DIRS})
#SET(CMAKE_REQUIRED_LIBRARIES vtkVolumeRendering) # can't get it to work
CHECK_CXX_SOURCE_COMPILES(
  "\#include <vtkSmartVolumeMapper.h>\nint main() { vtkSmartVolumeMapper* p; return 0;}"
  VTK_HAS_SMARTVOLUMEMAPPER)
CHECK_CXX_SOURCE_COMPILES(
  "\#include <vtkImageResliceMapper.h>\nint main() { vtkImageResliceMapper* p; return 0;}"
  VTK_HAS_IMAGERESLICEMAPPER)

INCLUDE_DIRECTORIES(
  ${GDCM_BINARY_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/Common
  ${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition
  ${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat
  ${GDCM_SOURCE_DIR}/Source/DataDictionary
  ${GDCM_SOURCE_DIR}/Utilities/VTK
  )

# FIXME: temp fix
#IF(UNIX)
#  LINK_DIRECTORIES(/usr/X11R6/lib)
#ENDIF(UNIX)

# List the kits from VTK that are needed by this project.
SET(vtkgdcm_LIBS
  vtkCommon
  vtkIO
  vtkImaging
)
IF(VTK_USE_RENDERING)
  SET(vtkgdcm_LIBS
    ${vtkgdcm_LIBS}
    vtkRendering
    )
ENDIF(VTK_USE_RENDERING)

# Use wrapping hints for this project.
#SET(VTK_WRAP_HINTS "${PROJECT_SOURCE_DIR}/hints")

SET(VTKGDCM_NAME vtkgdcm CACHE STRING "vtk-gdcm lib name")
MARK_AS_ADVANCED(VTKGDCM_NAME)

# Create the instantiator for these classes.
# FIXME: Are instantiator really needed when only doing python wrapping ?
IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkMedicalImageProperties.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/VTK4/vtkStringArray.cxx
  )
  # Setup vtkInstantiator registration for this library's classes.
  INCLUDE_DIRECTORIES(
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
ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
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
  IF(VTK_USE_RENDERING)
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageColorViewer.cxx
    )
  ENDIF(VTK_USE_RENDERING)

  #IF(GDCM_HAVE_PTHREAD_H)
    SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    vtkGDCMThreadedImageReader2.cxx
    )
  #ENDIF(GDCM_HAVE_PTHREAD_H)

  SET(VTK_USE_INSTANTIATOR_NEW 1)
  VTK_MAKE_INSTANTIATOR3(
    "${VTKGDCM_NAME}Instantiator"
    vtkgdcmInstantiator_SRCS
    "${vtkgdcm_SRCS}"
    "" #"VTK_${VTKGDCM_NAME}_EXPORT"
    ${PROJECT_BINARY_DIR}
    "" #"${VTKGDCM_NAME}Configure.h"
  )
ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )

#Hum... not sure why this is needed.
#IF(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)
#  ADD_LIBRARY(vtkgdcm STATIC ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#ELSE(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)
  ADD_LIBRARY(${VTKGDCM_NAME} ${vtkgdcm_SRCS} ${vtkgdcmInstantiator_SRCS})
#ENDIF(NOT VTK_BUILD_SHARED_LIBS AND GDCM_BUILD_SHARED_LIBS)

SET_TARGET_PROPERTIES(${VTKGDCM_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
# prevent viral dep of vtkgdcm
SET_PROPERTY(TARGET ${VTKGDCM_NAME} PROPERTY LINK_INTERFACE_LIBRARIES "")
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${VTKGDCM_NAME}
    EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKLibraries
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKLibraries #${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKDevelopment
  )
#if(NAMELINK_ONLY)
#  INSTALL(TARGETS vtkgdcm
#    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
#  )
#  endif(NAMELINK_ONLY)
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

IF(NOT GDCM_INSTALL_NO_DEVELOPMENT)
  SET(header_files_glob "*.h" "*.txx")
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    SET(header_files_glob ${header_files_glob}
      "VTK4/*.h"
    )
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  FILE(GLOB header_files ${header_files_glob})
  INSTALL(FILES ${header_files}
    DESTINATION ${GDCM_INSTALL_INCLUDE_DIR} COMPONENT VTKHeaders
  )
ENDIF(NOT GDCM_INSTALL_NO_DEVELOPMENT)

IF(GDCM_WRAP_PHP)
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    MESSAGE(FATAL_ERROR "you need a newer VTK version >= 5.0")
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )

  FIND_PACKAGE(PHP5 REQUIRED)
  INCLUDE_DIRECTORIES(
    ${PHP5_INCLUDE_PATH}
    )

  FIND_PACKAGE(SWIG REQUIRED)
  MARK_AS_ADVANCED(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
  INCLUDE(${SWIG_USE_FILE})
  SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES CPLUSPLUS ON)
  #SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES COMPILE_FLAGS -DUSEACTIVIZ)
  #IF(GDCM_USE_ACTIVIZ)
  #SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue -DUSEACTIVIZ")
  #ELSE(GDCM_USE_ACTIVIZ)
  #SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue")
  #ENDIF(GDCM_USE_ACTIVIZ)
  #SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)

  SWIG_ADD_MODULE(php_vtkgdcm php vtkgdcm.i)
  SWIG_LINK_LIBRARIES(php_vtkgdcm vtkgdcm)
  IF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTIES OUTPUT_NAME "vtkgdcm")
  ENDIF(UNIX)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTIES PREFIX "")
  SET_TARGET_PROPERTIES(${SWIG_MODULE_php_vtkgdcm_REAL_NAME} PROPERTIES LINK_INTERFACE_LIBRARIES "")

IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_php_vtkgdcm_REAL_NAME}
      EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries #${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
#if(NAMELINK_ONLY)
#  INSTALL(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
#    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
#  )
#  endif(NAMELINK_ONLY)

# See gdcm bug #3175803
add_custom_command(TARGET ${SWIG_MODULE_php_vtkgdcm_REAL_NAME}
  PRE_BUILD
  COMMAND sed -i -e 's/zend_error_noreturn/zend_error/g' "${swig_generated_file_fullname}"
  COMMENT "Patching zend_error_noreturn into zend_error"
  )

# Let's copy vtkgdcm.php into the bin dir:
ADD_CUSTOM_COMMAND(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/vtkgdcm.php ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT "copying vtkgdcm.php"
)
ADD_CUSTOM_TARGET(VTKGDCMPHP ALL
  DEPENDS ${LIBRARY_OUTPUT_PATH}/vtkgdcm.php
  COMMENT "building vtkgdcm.php"
)

ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
ENDIF(GDCM_WRAP_PHP)

IF(GDCM_WRAP_CSHARP)
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    MESSAGE(FATAL_ERROR "you need a newer VTK version >= 5.0")
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  IF(GDCM_USE_ACTIVIZ)
    FIND_PACKAGE(ACTIVIZ REQUIRED)
  ELSE(GDCM_USE_ACTIVIZ)
    MESSAGE(STATUS "You are using the SWIG version of VTKGDCM. This is not compatible with Activiz")
    FIND_PACKAGE(SWIG REQUIRED)
    MARK_AS_ADVANCED(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
    INCLUDE(${SWIG_USE_FILE})
    SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES CPLUSPLUS ON)
    #SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES COMPILE_FLAGS -DUSEACTIVIZ)
  ENDIF(GDCM_USE_ACTIVIZ)
  IF(GDCM_USE_ACTIVIZ)
    #SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue -DUSEACTIVIZ")
  ELSE(GDCM_USE_ACTIVIZ)
    SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue")
    SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
    SWIG_ADD_MODULE(vtkgdcmsharpglue csharp vtkgdcm.i)
    SWIG_LINK_LIBRARIES(vtkgdcmsharpglue vtkgdcm)
    # Stupid cmake-swig module is doing that for us, when not needed
    IF(UNIX)
      SET_TARGET_PROPERTIES(${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} PROPERTIES PREFIX "lib")
    ENDIF(UNIX)
    IF(NOT GDCM_INSTALL_NO_LIBRARIES)
      INSTALL(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
        EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries #${NAMELINK_SKIP}
        ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
        )
    ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
  ENDIF(GDCM_USE_ACTIVIZ)

  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Wrapping/Csharp/key.snk
    ${CMAKE_CURRENT_BINARY_DIR}/key.snk
    COPYONLY)

  IF(GDCM_USE_ACTIVIZ)
    FIND_PACKAGE(Mummy REQUIRED)
    MARK_AS_ADVANCED(Mummy_DIR)
    IF(NOT Mummy_BASE_DIR)
      MESSAGE(FATAL_ERROR "error: Mummy_BASE_DIR not defined. Please set Mummy_DIR to the directory containing MummyConfig.cmake")
    ENDIF(NOT Mummy_BASE_DIR)
    INCLUDE("${Mummy_DIR}/MummyCMakeMacros.cmake")
    IF(NOT mummy_EXECUTABLE)
      FIND_PROGRAM(mummy_EXECUTABLE mummy)
    ENDIF(NOT mummy_EXECUTABLE)
    MARK_AS_ADVANCED(mummy_EXECUTABLE)
    IF(NOT mummy_EXECUTABLE)
      MESSAGE(FATAL_ERROR "error: mummy not found. mummy_EXECUTABLE='${mummy_EXECUTABLE}'")
    ENDIF(NOT mummy_EXECUTABLE)

    IF(NOT gccxml_EXECUTABLE)
      FIND_PROGRAM(gccxml_EXECUTABLE gccxml)
    ENDIF(NOT gccxml_EXECUTABLE)
    MARK_AS_ADVANCED(gccxml_EXECUTABLE)
    IF(NOT gccxml_EXECUTABLE)
      MESSAGE(FATAL_ERROR "error: gccxml not found. gccxml_EXECUTABLE='${gccxml_EXECUTABLE}'")
    ENDIF(NOT gccxml_EXECUTABLE)
    SET(gccxml_compiler "${CMAKE_CXX_COMPILER}")
    IF(MSVC80)
      SET(gccxml_compiler "msvc8")
    ENDIF(MSVC80)
    IF(MSVC90)
      SET(gccxml_compiler "msvc9")
    ENDIF(MSVC90)
    #MESSAGE(STATUS "gccxml_compiler='${gccxml_compiler}'...")
    SET(gccxml_include_args "")
    FOREACH(dir ${Mummy_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})
      SET(gccxml_include_args ${gccxml_include_args} "-I${dir}")
    ENDFOREACH(dir)
    CONFIGURE_FILE(
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
    SET(kits gdcm)
    # foreach kit
    set(kit gdcm)
    FOREACH(class ${theclasslist})
      IF(NOT VTK_CLASS_WRAP_EXCLUDE_${class})
        #SET(header "${VTK_${ukit}_HEADER_DIR}/${class}.h")
        SET(header "${CMAKE_CURRENT_SOURCE_DIR}/${class}.h")
        SET(cxxclass "${class}")

        # handle full paths
        IF("${class}" MATCHES "^(\\/|.\\/|.\\\\|.:\\/|.:\\\\)")
          SET(header "${class}.h")
          STRING(REGEX MATCH "[^/]*$" cxxclass "${class}")

          GET_FILENAME_COMPONENT(dir "${header}" PATH)
          INCLUDE_DIRECTORIES("${dir}")
        ENDIF("${class}" MATCHES "^(\\/|.\\/|.\\\\|.:\\/|.:\\\\)")

        SET(abstract 0)
        IF(VTK_CLASS_ABSTRACT_${class})
          SET(abstract 1)
          SET_SOURCE_FILES_PROPERTIES(${header} PROPERTIES ABSTRACT 1)
        ENDIF(VTK_CLASS_ABSTRACT_${class})

        # Build one master in-memory table so that we don't have to re-do all the
        # logic in this nested FOREACH loop later on... Instead we'll simply iterate
        # the in-memory table built here:
        #
        SET(WRAPPED_CLASS_TABLE ${WRAPPED_CLASS_TABLE} "${cxxclass} ${kit} ${abstract} ${header}")


        SET(include_source_text "")
        STRING(REGEX REPLACE "(.*).h" "\\1.cxx" source "${header}")
        IF(EXISTS "${source}")
          SET(include_source_text "#include \"${source}\"")
        ELSE(EXISTS "${source}")
          #MESSAGE(FATAL_ERROR "error: Source file '${source}' does not exist...")
        ENDIF(EXISTS "${source}")

        CONFIGURE_FILE(
          "${CMAKE_CURRENT_SOURCE_DIR}/gccxml.cxx.in"
          "${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx"
          @ONLY
        )

        ADD_CUSTOM_COMMAND(
          OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
          COMMAND ${gccxml_EXECUTABLE}
          ARGS
            -fxml=${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}.xml
            -fxml-start=_cable_
            ${gccxml_include_args} -DCABLE_CONFIGURATION
            --gccxml-compiler ${gccxml_compiler}
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx
          DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/xml/${cxxclass}_gccxml.cxx
            ${header}
            ${gccxml_EXECUTABLE}
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
        ADD_CUSTOM_COMMAND(
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

        SET(${kit}_EL_SOURCES ${${kit}_EL_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx")
        SET(ALLKITS_EL_SOURCES ${ALLKITS_EL_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/export-layer/${cxxclass}EL.cxx")

        SET(${kit}_CS_SOURCES ${${kit}_CS_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs")
        SET(ALLKITS_CS_SOURCES ${ALLKITS_CS_SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}.cs")

        SET(${kit}_SENTINELS ${${kit}_SENTINELS} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt")
        SET(ALLKITS_SENTINELS ${ALLKITS_SENTINELS} "${CMAKE_CURRENT_BINARY_DIR}/csharp/${cxxclass}-sentinel.txt")
      ENDIF(NOT VTK_CLASS_WRAP_EXCLUDE_${class})
    ENDFOREACH(class)

    ADD_CUSTOM_TARGET(
      "vtk${kit}GenerateWrappers" ALL
      DEPENDS ${${kit}_SENTINELS}
      )
    SET_SOURCE_FILES_PROPERTIES(
      ${ALLKITS_EL_SOURCES}
      ${ALLKITS_CS_SOURCES}
      PROPERTIES GENERATED 1)

    IF(VTK_BUILD_SHARED_LIBS)
      SET(MV_ONE_EXPORT_LAYER_DLL 0)
    ELSE(VTK_BUILD_SHARED_LIBS)
      SET(MV_ONE_EXPORT_LAYER_DLL 1)
    ENDIF(VTK_BUILD_SHARED_LIBS)

    IF(MV_ONE_EXPORT_LAYER_DLL)
      message(FATAL_ERROR "Unimplemented")
      #SET(AVDN_INSTALL_TARGETS ${AVDN_INSTALL_TARGETS} "Kitware.VTK.Unmanaged")
      #ADD_LIBRARY(Kitware.VTK.Unmanaged SHARED ${ALLKITS_EL_SOURCES})
      #SET(unmanaged_targets ${unmanaged_targets} "Kitware.VTK.Unmanaged")
      #SET(unmanaged_dlls ${unmanaged_dlls} "${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
      #IF(WIN32)
      #  TARGET_LINK_LIBRARIES(Kitware.VTK.Unmanaged "${exe_dir}/Kitware.mummy.Runtime.Unmanaged.lib")
      #ELSE(WIN32)
      #  TARGET_LINK_LIBRARIES(Kitware.VTK.Unmanaged "${exe_dir}/${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.mummy.Runtime.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
      #ENDIF(WIN32)
      ## TODO -- rename this CopyLibraries here too...
      #ADD_DEPENDENCIES(Kitware.VTK.Unmanaged Kitware.mummy.CopyLibraries2)
      #FOREACH(kit ${kits})
      #  TARGET_LINK_LIBRARIES(Kitware.VTK.Unmanaged vtk${kit})
      #  ADD_DEPENDENCIES(Kitware.VTK.Unmanaged "vtk${kit}GenerateWrappers")
      #ENDFOREACH(kit)
    ELSE(MV_ONE_EXPORT_LAYER_DLL)
      INCLUDE_DIRECTORIES(${Mummy_INCLUDE_DIRS})
      FOREACH(kit ${kits})
        SET(AVDN_INSTALL_TARGETS ${AVDN_INSTALL_TARGETS} "Kitware.VTK.vtk${kit}.Unmanaged")
        ADD_LIBRARY(Kitware.VTK.vtk${kit}.Unmanaged SHARED ${${kit}_EL_SOURCES})
        SET(unmanaged_targets ${unmanaged_targets} "Kitware.VTK.vtk${kit}.Unmanaged")
        SET(unmanaged_dlls ${unmanaged_dlls} "${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.vtk${kit}.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}")
        IF(WIN32)
          TARGET_LINK_LIBRARIES(Kitware.VTK.vtk${kit}.Unmanaged "${exe_dir}/Kitware.mummy.Runtime.Unmanaged.lib")
        ELSE(WIN32)
          TARGET_LINK_LIBRARIES(Kitware.VTK.vtk${kit}.Unmanaged ${Mummy_RUNTIME_LINK_LIBRARIES})
        ENDIF(WIN32)
        TARGET_LINK_LIBRARIES(Kitware.VTK.vtk${kit}.Unmanaged vtk${kit})
        # TODO -- rename this CopyLibraries here too...
        ADD_DEPENDENCIES(Kitware.VTK.vtk${kit}.Unmanaged Kitware.mummy.CopyLibraries2)
        ADD_DEPENDENCIES(Kitware.VTK.vtk${kit}.Unmanaged "vtk${kit}GenerateWrappers")
      ENDFOREACH(kit)
    ENDIF(MV_ONE_EXPORT_LAYER_DLL)

    set(csc_EXECUTABLE ${CMAKE_CSHARP_COMPILER})
    # Set list of export-layer dlls in C# syntax as CMake variable
    # MV_EXPORTLAYER_DLL_VARIABLES. This gets configured into
    # WrappedObject.cs below.
    #
    SET(MV_EXPORTLAYER_DLL_VARIABLES "")
    FOREACH(kit ${kits})
      SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// <summary>\n")
      SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// Export layer functions for 'vtk${kit}' are exported from\n")
      SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// the DLL named by the value of this variable.\n")
      SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    /// </summary>\n")

      IF(MV_ONE_EXPORT_LAYER_DLL)
        SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    public const string vtk${kit}EL_dll = \"${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}\";\n")
      ELSE(MV_ONE_EXPORT_LAYER_DLL)
        SET(MV_EXPORTLAYER_DLL_VARIABLES "${MV_EXPORTLAYER_DLL_VARIABLES}    public const string vtk${kit}EL_dll = \"${CMAKE_SHARED_LIBRARY_PREFIX}Kitware.VTK.vtk${kit}.Unmanaged${CMAKE_SHARED_LIBRARY_SUFFIX}\";\n")
      ENDIF(MV_ONE_EXPORT_LAYER_DLL)
    ENDFOREACH(kit)

    SET(csharp_namespace "Kitware.VTK.GDCM")
    CONFIGURE_FILE(
      "${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in"
      "${CMAKE_CURRENT_BINARY_DIR}/csharp/AssemblyInfo.cs"
      @ONLY
      )

    SET(ALLKITS_CS_SOURCES
      ${ALLKITS_CS_SOURCES}
      "${CMAKE_CURRENT_BINARY_DIR}/csharp/AssemblyInfo.cs"
      )

    SET(AVDN_VTK_CSC_REFS ${ACTIVIZ_KITWARE_VTK_LIBRARY} ${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY})
    ADD_CSHARP_LIBRARY(
      "Kitware.VTK.GDCM" # name of library
      "${unmanaged_targets}" # list of CMake targets that need to build first
      "${AVDN_VTK_CSC_REFS}" # list of csc "/reference:" args
      "${unmanaged_dlls}" # list of csc "/linkresource:" args
      "${AVDN_SNKEYFILE}" # strong name signing keyfile
      # Source files:
      ${ALLKITS_CS_SOURCES}
      )

    FOREACH(kit ${kits})
      ADD_DEPENDENCIES(Kitware.VTK.GDCM "vtk${kit}GenerateWrappers")
    ENDFOREACH(kit)

    #    ADD_CUSTOM_COMMAND(
    #      OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
    #      COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${ACTIVIZ_KITWARE_VTK_LIBRARY}" "/r:${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY}" "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
    #      #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
    #      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #      DEPENDS "${swig_generated_file_fullname}"
    #      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    #      COMMENT "csc *.cs"
    #      )

    INSTALL(FILES
      ${GDCM_LIBRARY_DIR}/Kitware.VTK.GDCM.dll
      ${GDCM_LIBRARY_DIR}/Kitware.VTK.GDCM.xml
      DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKCSharpModule
      )
    INSTALL(TARGETS Kitware.VTK.vtk${kit}.Unmanaged
      EXPORT ${GDCM_TARGETS_NAME}
      RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKLibraries
      LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKLibraries #${NAMELINK_SKIP}
      ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKDevelopment
      )
  ELSE(GDCM_USE_ACTIVIZ)
    CONFIGURE_FILE(
      ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
      @ONLY)

    ADD_CUSTOM_COMMAND(
      OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
      COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      DEPENDS "${swig_generated_file_fullname}"
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
      COMMENT "csc *.cs"
      )
    ADD_CUSTOM_TARGET(VTKGDCMCSharp ALL
      DEPENDS
      ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
      #${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll.config
      #${GDCM_EXECUTABLE_DIR}/HelloWorld.exe
      COMMENT "building vtkgdcm-sharp.dll"
      )
    # because vtkgdcm-sharp.dll is constructed with custom commands, it need the INSTALL(FILES signature:
    SET(GDCM_LIBRARY_DIR2 ${LIBRARY_OUTPUT_PATH}/\${BUILD_TYPE})
    INSTALL(FILES
      ${GDCM_LIBRARY_DIR2}/vtkgdcm-sharp.dll
      #${GDCM_LIBRARY_DIR2}/vtkgdcm-sharp.dll.config
      DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKCSharpModule
      )
  ENDIF(GDCM_USE_ACTIVIZ)

  #ADD_CUSTOM_COMMAND(
  #  OUTPUT  ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll.config
  #  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config ${GDCM_LIBRARY_DIR}
  #  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config
  #  COMMENT "Copying vtkgdcm-sharp.dll.config"
  #)

ENDIF(GDCM_WRAP_CSHARP)

IF(GDCM_WRAP_JAVA)
  IF(VTK_WRAP_JAVA)
    FIND_PACKAGE(Java 1.5 REQUIRED) # javac, jar
    FIND_PACKAGE(JNI REQUIRED)
    INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS})
    SET(VTK_WRAP_JAVA3_INIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    # Lars Matthäus patch (package vtk => imply vtk subdir )
    SET(VTK_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/vtk)
    # This is *required* don't ask
    MAKE_DIRECTORY(${VTK_JAVA_HOME})
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapJava.cmake)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

    VTK_WRAP_JAVA3(${VTKGDCM_NAME}Java vtkgdcmJAVA_SRCS "${vtkgdcm_SRCS}")
    # libvtk-java is a pain to handle...
    if(EXISTS ${VTK_JAVA_JAR})
      # http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=533193
      set(GDCM_VTK_JAVA_JAR ${VTK_JAVA_JAR})
    endif(EXISTS ${VTK_JAVA_JAR})
    if(EXISTS /usr/lib/jni/libvtkCommonJava.so)
      # http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=533198
      message(STATUS "Implicitely adding debian package layout...")
      link_directories("/usr/lib/jni")
    endif()
    MARK_AS_ADVANCED(GDCM_VTK_JAVA_JAR)
    if(EXISTS ${GDCM_VTK_JAVA_JAR})
    else(EXISTS ${GDCM_VTK_JAVA_JAR})
      message(FATAL_ERROR "Could not find vtk.jar file, VTK_JAVA_JAR is wrong: ${VTK_JAVA_JAR}, please set proper GDCM_VTK_JAVA_JAR: ${GDCM_VTK_JAVA_JAR} replacement var")
    endif(EXISTS ${GDCM_VTK_JAVA_JAR})
    ADD_LIBRARY(${VTKGDCM_NAME}Java SHARED ${vtkgdcmJAVA_SRCS})
    # special jnilib extension:
    IF(APPLE)
      SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Java PROPERTIES SUFFIX ".jnilib")
    ENDIF(APPLE)
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${VTKGDCM_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${c}Java)
    ENDFOREACH(c)
    # Create the jar file:
    # I am pretty sure this *.java thingy will bite me one day, when someone will try
    # to recompile from an existing build tree with invalid generated *.java file...
    ADD_CUSTOM_COMMAND(
      OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      #COMMAND ${Java_JAVAC_EXECUTABLE} ARGS -cp ${GDCM_VTK_JAVA_JAR} "vtk/*.java"
      # No such thing as -cp for javac only java is listed:
      # http://java.sun.com/j2se/1.5.0/docs/tooldocs/windows/classpath.html
      COMMAND ${Java_JAVAC_EXECUTABLE} ARGS -classpath ${GDCM_VTK_JAVA_JAR} "vtk/*.java"
      COMMAND ${Java_JAR_EXECUTABLE} ARGS -cvfm ${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.jar ${CMAKE_CURRENT_SOURCE_DIR}/manifest.txt vtk/*.class
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/java
      DEPENDS ${VTKGDCM_NAME}Java
      #${VTK_JAVA_DEPENDENCIES}
      #vtkgdcmJavaJavaClasses
      COMMENT   "javac *.java -> jar; jar cvf -> vtkgdcm.jar"
    )
    # Target to execute custom command:
    ADD_CUSTOM_TARGET(VTKGDCMJavaJar ALL
      DEPENDS ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      COMMENT "building vtkgdcm.jar"
    )
    ADD_DEPENDENCIES(VTKGDCMJavaJar vtkgdcmJavaJavaClasses)

    # Install rules:
    IF(NOT GDCM_INSTALL_NO_LIBRARIES)
      INSTALL(TARGETS ${VTKGDCM_NAME}Java
      EXPORT ${GDCM_TARGETS_NAME}
        RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKJavaModule
        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKJavaModule #${NAMELINK_SKIP}
        ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKJavaModule
      )
  #Development
  #if(NAMELINK_ONLY)
  #  INSTALL(TARGETS ${VTKGDCM_NAME}Java
  #    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKJavaModule ${NAMELINK_ONLY}
  #  )
  #endif(NAMELINK_ONLY)

    # because vtkgdcm.jar is constructed with custom commands, it need the INSTALL(FILES signature:
    INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKJavaModule
      )
    ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

  ELSE(VTK_WRAP_JAVA)
    MESSAGE(STATUS "GDCM_WRAP_JAVA canot be build without VTK_WRAP_JAVA")
  ENDIF(VTK_WRAP_JAVA)
ENDIF(GDCM_WRAP_JAVA)

IF(GDCM_WRAP_PYTHON)
  IF(VTK_WRAP_PYTHON)
      SET(DEXTENSION "")
    IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
        VTK_WRAP_PYTHON2(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS ${vtkgdcm_SRCS})
    ELSE( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    INCLUDE(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
        INCLUDE_DIRECTORIES(
          ${PYTHON_INCLUDE_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
        VTK_WRAP_PYTHON3(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
      SET(DEXTENSION "D")
    ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    ADD_LIBRARY(${VTKGDCM_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    # this is a library set the version:
    # do not set the version on the Python module:
    #SET_TARGET_PROPERTIES(${VTKGDCM_NAME}PythonD PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    ADD_LIBRARY(${VTKGDCM_NAME}Python MODULE ${VTKGDCM_NAME}PythonInit.cxx)
    # do not set the version on the PythonD module:
    SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Python PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}PythonD ${VTKGDCM_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}PythonD ${c}Python${DEXTENSION})
    ENDFOREACH(c)
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Python ${VTKGDCM_NAME}PythonD)
    # Python extension modules on Windows must have the extension ".pyd"
    # instead of ".dll" as of Python 2.5.  Older python versions do support
    # this suffix.
    IF(WIN32 AND NOT CYGWIN)
      SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Python PROPERTIES SUFFIX ".pyd")
    ENDIF(WIN32 AND NOT CYGWIN)

    ADD_CUSTOM_COMMAND(
      TARGET    ${VTKGDCM_NAME}Python
      POST_BUILD
      COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
      DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py"
      COMMENT   "Copy vtkgdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )
    IF(NOT GDCM_INSTALL_NO_LIBRARIES)
        INSTALL(TARGETS ${VTKGDCM_NAME}Python
      EXPORT ${GDCM_TARGETS_NAME}
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT                        VTKPythonModule
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKPythonModule #${NAMELINK_SKIP}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKPythonModule
        )
        INSTALL(TARGETS ${VTKGDCM_NAME}PythonD
      EXPORT ${GDCM_TARGETS_NAME}
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT VTKPythonModule
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKPythonModule #${NAMELINK_ONLY}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT VTKPythonModule
        )
      #  if(NAMELINK_ONLY)
      #      INSTALL(TARGETS ${VTKGDCM_NAME}PythonD ${VTKGDCM_NAME}Python
      #        LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKDevelopment ${NAMELINK_ONLY}
      #        )
      #  endif(NAMELINK_ONLY)
    # the python file is not a dev file, but part of the gdcm module...
      INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm.py
        DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKPythonModule
      )
    ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

  ELSE(VTK_WRAP_PYTHON)
    MESSAGE(STATUS "GDCM_WRAP_PYTHON canot be build without VTK_WRAP_PYTHON")
  ENDIF(VTK_WRAP_PYTHON)
ENDIF(GDCM_WRAP_PYTHON)

IF(BUILD_TESTING)
  SUBDIRS(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_APPLICATIONS)
  SUBDIRS(Applications)
ENDIF(BUILD_APPLICATIONS)

IF(BUILD_EXAMPLES)
  SUBDIRS(Examples)
ENDIF(BUILD_EXAMPLES)

IF(GDCM_USE_PARAVIEW)
  # http://www.cmake.org/Wiki/Plugin_HowTo#Adding_a_Reader
  FIND_PACKAGE(ParaView REQUIRED)
  INCLUDE(${PARAVIEW_USE_FILE})
  ADD_PARAVIEW_PLUGIN(GDCMImageReader "1.0"
    SERVER_MANAGER_SOURCES vtkGDCMImageReader.cxx
    SERVER_MANAGER_XML GDCMImageReader.xml
    GUI_RESOURCE_FILES GDCMImageGUI.xml)
  TARGET_LINK_LIBRARIES(GDCMImageReader ${VTKGDCM_NAME})
  INSTALL(TARGETS GDCMImageReader
    EXPORT ${GDCM_TARGETS_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT ParaViewModule
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT ParaViewModule
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT ParaViewModule
    )

ENDIF(GDCM_USE_PARAVIEW)
