#ADD_EXECUTABLE(ManipulateFile ManipulateFile.cs)
#TARGET_LINK_LIBRARIES(ManipulateFile gdcm-sharp)

SET(CSHARP_EXAMPLES
  SimplePrintPatientName
  ExtractOneFrame
  ExtractImageRegion
  ManipulateFile
  RescaleImage
  ExtractEncapsulatedFile
  DecompressImage
  DecompressImageMultiframe
  DecompressJPEGFile
  SimplePrint
  ScanDirectory
  #SortImage2
  GetArray
  NewSequence
  GenerateDICOMDIR
  StandardizeFiles
  ReformatFile
  CompressLossyJPEG
  SendFileSCU
  BasicImageAnonymizer
  )

IF(BUILD_TESTING)
  SET(CSHARP_EXAMPLES
    ${CSHARP_EXAMPLES}
    BasicAnonymizer
    ClinicalTrialIdentificationWorkflow
    )
ENDIF(BUILD_TESTING)

SET(DEP)
# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_add_a_dependency_to_a_source_file_which_is_generated_in_a_subdirectory.3F
# Tell CMake the source won't be available until build time.
SET_SOURCE_FILES_PROPERTIES(${GDCM_LIBRARY_DIR}/gdcm-sharp.dll PROPERTIES GENERATED 1)
# Make sure the source is generated before the executable builds.
FOREACH(example ${CSHARP_EXAMPLES})
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs result)
# WORKING_DIRECTORY is set to the src dir because of a strange issue with CSC compiler on Win32 system:
# http://groups.google.com/group/microsoft.public.dotnet.languages.csharp/browse_thread/thread/9d3ac7eb9f7f56be
  ADD_CUSTOM_COMMAND(
    OUTPUT ${GDCM_EXECUTABLE_DIR}/${example}.exe
    #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${GDCM_LIBRARY_DIR}/gdcm-sharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "${CSC_PLATFORM_FLAG}" "/r:${GDCM_LIBRARY_DIR}/gdcm-sharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${result}
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS #${GDCM_LIBRARY_DIR}/gdcm-sharp.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMENT "Create ${example}.exe"
  )
  ADD_CUSTOM_TARGET(gdcm_sharp_${example} DEPENDS ${GDCM_EXECUTABLE_DIR}/${example}.exe)
  ADD_DEPENDENCIES(gdcm_sharp_${example} GDCMCSharp)

  SET(DEP ${DEP} ${GDCM_EXECUTABLE_DIR}/${example}.exe)
ENDFOREACH(example)

ADD_CUSTOM_TARGET(GDCMExampleCSharp ALL
  DEPENDS ${DEP}
  COMMENT "building examples"
)
ADD_DEPENDENCIES(GDCMExampleCSharp  GDCMCSharp)

IF(BUILD_TESTING)
IF(GDCM_DATA_ROOT)
  ADD_CSHARP_TEST(TestSimplePrintCSharp ${GDCM_EXECUTABLE_DIR}/SimplePrint.exe ${GDCM_DATA_ROOT}/012345.002.050.dcm)
# TODO:
#IF(BUILD_EXAMPLES)
#  ADD_CSHARP_TEST(HelloWorldCSharp ${GDCM_EXECUTABLE_DIR}/HelloWorld.exe ${GDCM_DATA_ROOT}/012345.002.050.dcm)
#ENDIF(BUILD_EXAMPLES)
ENDIF(GDCM_DATA_ROOT)
ENDIF(BUILD_TESTING)
