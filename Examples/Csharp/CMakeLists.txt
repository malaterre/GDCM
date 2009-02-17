#ADD_EXECUTABLE(ManipulateFile ManipulateFile.cs)
#TARGET_LINK_LIBRARIES(ManipulateFile gdcm_csharp)

SET(CSHARP_EXAMPLES
  ManipulateFile
  DecompressImage
  DecompressImageMultiframe
  DecompressJPEGFile
  TestCSharpFilter
  ScanDirectory
  #SortImage2
  TestGetArray
  )

SET(DEP)
FOREACH(example ${CSHARP_EXAMPLES})
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs result)
# WORKING_DIRECTORY is set to the src dir because of a strange issue with CSC compiler on Win32 system:
# http://groups.google.com/group/microsoft.public.dotnet.languages.csharp/browse_thread/thread/9d3ac7eb9f7f56be
  ADD_CUSTOM_COMMAND(
    OUTPUT ${GDCM_EXECUTABLE_DIR}/${example}.exe
    #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${GDCM_LIBRARY_DIR}/gdcm_csharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${GDCM_LIBRARY_DIR}/gdcm_csharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${result}
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${GDCM_LIBRARY_DIR}/gdcm_csharp.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMENT "Create ${example}.exe"
  )
  SET(DEP ${DEP} ${GDCM_EXECUTABLE_DIR}/${example}.exe)
ENDFOREACH(example)

ADD_CUSTOM_TARGET(GDCMExampleCSharp ALL
  DEPENDS ${DEP}
  COMMENT "building examples"
)

