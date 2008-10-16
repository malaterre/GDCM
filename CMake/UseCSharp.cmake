IF(WIN32)
  INCLUDE(${DotNETFrameworkSDK_USE_FILE})
  # remap
  SET(CMAKE_CSHARP1_COMPILER ${CSC_v1_EXECUTABLE})
  SET(CMAKE_CSHARP2_COMPILER ${CSC_v2_EXECUTABLE})
  SET(CMAKE_CSHARP3_COMPILER ${CSC_v3_EXECUTABLE})

  #SET(CMAKE_CSHARP3_INTERPRETER ${MONO_EXECUTABLE})
ELSE(WIN32)
  INCLUDE(${MONO_USE_FILE})
  SET(CMAKE_CSHARP1_COMPILER ${MCS_EXECUTABLE})
  SET(CMAKE_CSHARP2_COMPILER ${GMCS_EXECUTABLE})
  SET(CMAKE_CSHARP3_COMPILER ${SMCS_EXECUTABLE})

  SET(CMAKE_CSHARP3_INTERPRETER ${MONO_EXECUTABLE})
ENDIF(WIN32)

# default to v1:
SET(CMAKE_CSHARP_COMPILER ${CMAKE_CSHARP1_COMPILER})

MACRO(CSHARP_ADD_LIBRARY name)
  SET(csharp_cs_sources)
  FOREACH(it ${ARGN})
    IF(EXISTS ${it})
      SET(csharp_cs_sources ${csharp_cs_sources} "${it}")
    ELSE(EXISTS ${it})
      MESSAGE("Could not find: ${it}")
    ENDIF(EXISTS ${it})
  ENDFOREACH(it)

  #SET(SHARP #)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.dll
    COMMAND ${CMAKE_CSHARP_COMPILER}
    ARGS "/t:library" "/out:${name}.dll" ${csharp_cs_sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${csharp_cs_sources}"
    COMMENT "Creating Csharp library ${name}.cs"
  )
  ADD_CUSTOM_TARGET(CSharp_${name} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}.dll
  )
ENDMACRO(CSHARP_ADD_LIBRARY)

MACRO(CSHARP_ADD_EXECUTABLE name)
  SET(csharp_cs_sources)
  FOREACH(it ${ARGN})
    IF(EXISTS ${it})
      SET(csharp_cs_sources ${csharp_cs_sources} "${it}")
    ELSE(EXISTS ${it})
      IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it})
        SET(csharp_cs_sources ${csharp_cs_sources} "${CMAKE_CURRENT_SOURCE_DIR}/${it}")
      ELSE(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it})
        MESSAGE("Could not find: ${it}")
      ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it})
    ENDIF(EXISTS ${it})
  ENDFOREACH(it)

  SET(CSHARP_EXECUTABLE_${name}_ARGS
    #"/out:${name}.dll" ${csharp_cs_sources}
    #"/r:gdcm_csharp.dll" 
    "/out:${name}.exe ${csharp_cs_sources}"
  )
  SEPARATE_ARGUMENTS(CSHARP_EXECUTABLE_${name}_ARGS)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.exe
    COMMAND ${CMAKE_CSHARP_COMPILER}
    #ARGS "/r:gdcm_csharp.dll" "/out:${name}.exe" ${csharp_cs_sources}
    ARGS ${CSHARP_EXECUTABLE_${name}_ARGS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${csharp_cs_sources}
    COMMENT "Create HelloWorld.exe"
  )


  ADD_CUSTOM_TARGET(CSHARP_EXECUTABLE_${name} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}.exe
  )

ENDMACRO(CSHARP_ADD_EXECUTABLE)

MACRO(CSHARP_LINK_LIBRARIES name)
  SET(csharp_libraries)
  FOREACH(it ${ARGN})
    #IF(EXISTS ${it})
      SET(csharp_libraries "${csharp_libraries} /r:${it}")
    #ELSE(EXISTS ${it})
    #  MESSAGE("Could not find: ${it}")
    #ENDIF(EXISTS ${it})
  ENDFOREACH(it)
  SET(CSHARP_EXECUTABLE_${name}_ARGS "${CSHARP_EXECUTABLE_${name}_ARGS} ${csharp_libraries}")
  MESSAGE( "DEBUG: ${CSHARP_EXECUTABLE_${name}_ARGS}" )
ENDMACRO(CSHARP_LINK_LIBRARIES)

