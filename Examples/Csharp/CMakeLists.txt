#ADD_EXECUTABLE(ManipulateFile ManipulateFile.cs)
#TARGET_LINK_LIBRARIES(ManipulateFile gdcm_csharp)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/ManipulateFile.exe
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${LIBRARY_OUTPUT_PATH}/gdcm_csharp.dll" "/out:${EXECUTABLE_OUTPUT_PATH}/ManipulateFile.exe" ${CMAKE_CURRENT_SOURCE_DIR}/ManipulateFile.cs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${LIBRARY_OUTPUT_PATH}/gdcm_csharp.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/ManipulateFile.cs
    COMMENT "Create ManipulateFile.exe"
  )

ADD_CUSTOM_TARGET(GDCMExampleCSharp ALL
  DEPENDS 
    ${EXECUTABLE_OUTPUT_PATH}/ManipulateFile.exe
  COMMENT "building examples"
)

