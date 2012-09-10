#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# Macro to centralize all the plateform specific
# tests.
macro(GDCM_PLATFORM_CXX_TEST var description invert)
  if("${var}_COMPILED" MATCHES "^${var}_COMPILED$")
    message(STATUS "${description}")
    try_compile(${var}_COMPILED
      ${CMAKE_CURRENT_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/CMake/gdcmPlatformCxxTests.cxx
      COMPILE_DEFINITIONS -DTEST_${var} ${GDCM_PLATFORM_CXX_TEST_DEFINES}
      OUTPUT_VARIABLE OUTPUT)
    if(${var}_COMPILED)
      file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CMakeOutput.log
        "${description} compiled with the following output:\n${OUTPUT}\n\n")
    else(${var}_COMPILED)
      file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CMakeError.log
        "${description} failed to compile with the following output:\n${OUTPUT}\n\n")
    endif(${var}_COMPILED)
    if(${invert} MATCHES INVERT)
      if(${var}_COMPILED)
        message(STATUS "${description} - no")
      else(${var}_COMPILED)
        message(STATUS "${description} - yes")
      endif(${var}_COMPILED)
    else(${invert} MATCHES INVERT)
      if(${var}_COMPILED)
        message(STATUS "${description} - yes")
      else(${var}_COMPILED)
        message(STATUS "${description} - no")
      endif(${var}_COMPILED)
    endif(${invert} MATCHES INVERT)
  endif("${var}_COMPILED" MATCHES "^${var}_COMPILED$")
  if(${invert} MATCHES INVERT)
    if(${var}_COMPILED)
      set(${var} 0)
    else(${var}_COMPILED)
      set(${var} 1)
    endif(${var}_COMPILED)
  else(${invert} MATCHES INVERT)
    if(${var}_COMPILED)
      set(${var} 1)
    else(${var}_COMPILED)
      set(${var} 0)
    endif(${var}_COMPILED)
  endif(${invert} MATCHES INVERT)
endmacro(GDCM_PLATFORM_CXX_TEST)
