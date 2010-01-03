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

IF(CMAKE_HAVE_PTHREAD_H)
  SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
  vtkGDCMThreadedImageReader.cxx
  )
ENDIF(CMAKE_HAVE_PTHREAD_H)

INCLUDE(${VTK_USE_FILE})
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
  vtkRendering
)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageColorViewer.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToWindowLevelColors2.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageYBRToRGB.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageRGBToYBR.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMPolyDataReader.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkLookupTable16.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkImageMapToColors16.cxx
    #${CMAKE_CURRENT_SOURCE_DIR}/vtkImagePlanarComponentsToComponents.cxx
  )
  #IF(CMAKE_HAVE_PTHREAD_H)
    SET(vtkgdcm_SRCS ${vtkgdcm_SRCS}
    vtkGDCMThreadedImageReader2.cxx
    )
  #ENDIF(CMAKE_HAVE_PTHREAD_H)

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
IF(GDCM_USE_ACTIVIZ AND UNIX)
  # the following only works with Activiz VTK 5.4.2. The pure VTK lib are now shipped as separate libs.
  # so one can safely link to them, instead of having to build a VTK by hand, link vtkgdcm to it
  # and hope compiler configuration are compatible.
  # if you use Activiz/VTK 5.2.1 you are on your own (see gdcm 2.0.12 which supports Activiz 5.2.1)
  FIND_PACKAGE(ACTIVIZ REQUIRED)
  #message(${ACTIVIZ_KITWARE_VTK_LIBRARY})
  get_filename_component(bla ${ACTIVIZ_KITWARE_VTK_LIBRARY}
    PATH)

  LINK_DIRECTORIES(${bla})
  TARGET_LINK_LIBRARIES(${VTKGDCM_NAME} gdcmMSFF 
    ${bla}/libvtkCommon.so
    #${bla}/libvtkIO.so
    ${bla}/libvtkImaging.so
    ${bla}/libvtkRendering.so
    )
ELSE(GDCM_USE_ACTIVIZ AND UNIX)
  TARGET_LINK_LIBRARIES(${VTKGDCM_NAME} gdcmMSFF ${vtkgdcm_LIBS})
ENDIF(GDCM_USE_ACTIVIZ AND UNIX)

# this need to be set on the vtkIO lib directly
#  SET_PROPERTY(TARGET ${VTKGDCM_NAME} PROPERTY LINK_INTERFACE_LIBRARIES "")
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${VTKGDCM_NAME}
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

IF(GDCM_WRAP_CSHARP)
  IF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    MESSAGE(FATAL_ERROR "you need a newer VTK version >= 5.0")
  ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
  IF(GDCM_USE_ACTIVIZ)
    FIND_PACKAGE(ACTIVIZ REQUIRED)
  ELSE(GDCM_USE_ACTIVIZ)
    MESSAGE("You are using the SWIG version of VTKGDCM. This is not compatible with Activiz")
  ENDIF(GDCM_USE_ACTIVIZ)
  FIND_PACKAGE(SWIG REQUIRED)
  MARK_AS_ADVANCED(SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION)
  INCLUDE(${SWIG_USE_FILE})
  SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES CPLUSPLUS ON)
  #SET_SOURCE_FILES_PROPERTIES(vtkgdcm.i PROPERTIES COMPILE_FLAGS -DUSEACTIVIZ)
  IF(GDCM_USE_ACTIVIZ)
  SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue -DUSEACTIVIZ")
  ELSE(GDCM_USE_ACTIVIZ)
  SET(CMAKE_SWIG_FLAGS "-namespace vtkgdcm -dllimport vtkgdcmsharpglue")
  ENDIF(GDCM_USE_ACTIVIZ)
  SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
  SWIG_ADD_MODULE(vtkgdcmsharpglue csharp vtkgdcm.i)
  SWIG_LINK_LIBRARIES(vtkgdcmsharpglue vtkgdcm)
  # Stupid cmake-swig module is doing that for us, when not needed
  IF(UNIX)
    SET_TARGET_PROPERTIES(${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME} PROPERTIES PREFIX "lib")
  ENDIF(UNIX)

IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Applications
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Libraries #${NAMELINK_SKIP}
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
#if(NAMELINK_ONLY)
#  INSTALL(TARGETS ${SWIG_MODULE_vtkgdcmsharpglue_REAL_NAME}
#    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development ${NAMELINK_ONLY}
#  )
#  endif(NAMELINK_ONLY)

ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs.in
    ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    @ONLY)
  IF(GDCM_USE_ACTIVIZ)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${ACTIVIZ_KITWARE_VTK_LIBRARY}" "/r:${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY}" "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs" 
    #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs" 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${swig_generated_file_fullname}"
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    COMMENT "csc *.cs"
  )
  ELSE(GDCM_USE_ACTIVIZ)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll
    #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${ACTIVIZ_KITWARE_VTK_LIBRARY}" "/r:${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY}" "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs" 
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/t:library" "/out:${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll" "*.cs" 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${swig_generated_file_fullname}"
      ${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs
    COMMENT "csc *.cs"
  )

  ENDIF(GDCM_USE_ACTIVIZ)

  #ADD_CUSTOM_COMMAND(
  #  OUTPUT  ${GDCM_LIBRARY_DIR}/vtkgdcm-sharp.dll.config
  #  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config ${GDCM_LIBRARY_DIR}
  #  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/vtkgdcm-sharp.dll.config
  #  COMMENT "Copying vtkgdcm-sharp.dll.config"
  #)

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
      message("Implicitely adding debian package layout...")
      link_directories("/usr/lib/jni")
    endif()
    MARK_AS_ADVANCED(GDCM_VTK_JAVA_JAR)
    if(EXISTS ${GDCM_VTK_JAVA_JAR})
    else(EXISTS ${GDCM_VTK_JAVA_JAR})
      message(FATAL_ERROR "Could not find vtk.jar file, VTK_JAVA_JAR is wrong: ${VTK_JAVA_JAR}, please set proper GDCM_VTK_JAVA_JAR replacement var")
    endif(EXISTS ${GDCM_VTK_JAVA_JAR})
    ADD_LIBRARY(${VTKGDCM_NAME}Java SHARED ${vtkgdcmJAVA_SRCS})
    TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${VTKGDCM_NAME})
    FOREACH(c ${vtkgdcm_LIBS})
      TARGET_LINK_LIBRARIES(${VTKGDCM_NAME}Java ${c}Java)
    ENDFOREACH(c)
    # Create the jar file:
    # I am pretty sure this *.java thingy will bite me one day, when someone will try
    # to recompile from an existing build tree with invalid generated *.java file...
    ADD_CUSTOM_COMMAND(
      OUTPUT ${LIBRARY_OUTPUT_PATH}/vtkgdcm.jar
      #COMMAND ${JAVA_COMPILE} ARGS -cp ${GDCM_VTK_JAVA_JAR} "vtk/*.java"
      # No such thing as -cp for javac only java is listed:
      # http://java.sun.com/j2se/1.5.0/docs/tooldocs/windows/classpath.html
      COMMAND ${JAVA_COMPILE} ARGS -classpath ${GDCM_VTK_JAVA_JAR} "vtk/*.java"
      COMMAND ${JAVA_ARCHIVE} ARGS cvf ${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.jar vtk/*.class
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
    MESSAGE("GDCM_WRAP_JAVA canot be build without VTK_WRAP_JAVA")
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
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
        VTK_WRAP_PYTHON3(${VTKGDCM_NAME}Python vtkgdcmPYTHON_SRCS "${vtkgdcm_SRCS}")
      SET(DEXTENSION "D")
    ENDIF( "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 4.5 )
    ADD_LIBRARY(${VTKGDCM_NAME}PythonD ${vtkgdcmPYTHON_SRCS})
    # this is a library set the version:
    SET_TARGET_PROPERTIES(${VTKGDCM_NAME}PythonD PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
    ADD_LIBRARY(${VTKGDCM_NAME}Python MODULE ${VTKGDCM_NAME}PythonInit.cxx)
    # do not set the version on the Python module:
    #SET_TARGET_PROPERTIES(${VTKGDCM_NAME}Python PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
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
          RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT                        VTKPythonModule
          LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKPythonModule #${NAMELINK_SKIP}
          ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT VTKPythonModule
        )
        INSTALL(TARGETS ${VTKGDCM_NAME}PythonD
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
    MESSAGE("GDCM_WRAP_PYTHON canot be build without VTK_WRAP_PYTHON")
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

