# C# MSFF tests
set(DSED_TEST_SRCS
  TestReaderUnicode
  )

set(DEP)
set_source_files_properties(${GDCM_LIBRARY_DIR}/gdcm-sharp.dll PROPERTIES GENERATED 1)
foreach(test ${DSED_TEST_SRCS})
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cs result)
  add_custom_command(
    OUTPUT ${GDCM_EXECUTABLE_DIR}/${test}.exe
    COMMAND ${CMAKE_CSHARP_COMPILER} "${CSC_PLATFORM_FLAG}" "/r:${GDCM_LIBRARY_DIR}/gdcm-sharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${test}.exe" ${result}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cs
    COMMENT "Create ${test}.exe"
    )
  add_custom_target(gdcm_sharp_${test} DEPENDS ${GDCM_EXECUTABLE_DIR}/${test}.exe)
  add_dependencies(gdcm_sharp_${test} GDCMCSharp)
  list(APPEND DEP ${GDCM_EXECUTABLE_DIR}/${test}.exe)

  # add test
  if(GDCM_DATA_ROOT)
    ADD_CSHARP_TEST(Test${test}Csharp ${GDCM_EXECUTABLE_DIR}/${test}.exe)
  endif()
endforeach()

add_custom_target(gdcmDSEDTestsCsharp ALL
  DEPENDS ${DEP}
  COMMENT "building DSED C# tests"
  )
add_dependencies(gdcmDSEDTestsCsharp GDCMCSharp)
