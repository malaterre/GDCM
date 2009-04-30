
SET(CSHARP_EXAMPLES
  HelloVTKWorld
  )

SET(DEP)
FOREACH(example ${CSHARP_EXAMPLES})
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs result)
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMImageReader.cs result2)
# WORKING_DIRECTORY is set to the src dir because of a strange issue with CSC compiler on Win32 system:
# http://groups.google.com/group/microsoft.public.dotnet.languages.csharp/browse_thread/thread/9d3ac7eb9f7f56be
  ADD_CUSTOM_COMMAND(
    OUTPUT ${GDCM_EXECUTABLE_DIR}/${example}.exe
    #COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${GDCM_LIBRARY_DIR}/gdcm_csharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
    COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${ACTIVIZ_KITWARE_VTK_LIBRARY}" "/r:${ACTIVIZ_KITWARE_MUMMY_RUNTIME_LIBRARY}" "/r:${GDCM_LIBRARY_DIR}/vtkgdcmswig_csharp.dll" "/out:${GDCM_EXECUTABLE_DIR}/${example}.exe" ${result} ${result2}
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${GDCM_LIBRARY_DIR}/vtkgdcmswig_csharp.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cs
            ${CMAKE_CURRENT_SOURCE_DIR}/vtkGDCMImageReader.cs
    COMMENT "Create ${example}.exe"
  )
  SET(DEP ${DEP} ${GDCM_EXECUTABLE_DIR}/${example}.exe)
ENDFOREACH(example)

ADD_CUSTOM_TARGET(VTKGDCMExampleCSharp ALL
  DEPENDS ${DEP}
  COMMENT "building examples"
)

