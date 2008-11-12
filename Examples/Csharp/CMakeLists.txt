#ADD_EXECUTABLE(ManipulateFile ManipulateFile.cs)
#TARGET_LINK_LIBRARIES(ManipulateFile gdcm_csharp)

SET(CSHARP_EXAMPLES
  ManipulateFile
#  DecompressImage
  )

SET(DEP)
FOREACH(example ${CSHARP_EXAMPLES})
  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.exe
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${LIBRARY_OUTPUT_PATH}/gdcm_csharp.dll" "/out:${EXECUTABLE_OUTPUT_PATH}/${example}.exe" ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm_csharp.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMENT "Create ${example}.exe"
  )
  SET(DEP ${DEP} ${EXECUTABLE_OUTPUT_PATH}/${example}.exe)
ENDFOREACH(example)

ADD_CUSTOM_TARGET(GDCMExampleCSharp ALL
  DEPENDS ${DEP}
  COMMENT "building examples"
)

