# Try to rebuild wrapping a little more often:
INCLUDE_REGULAR_EXPRESSION("^(gdcm).*$")
# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
)
# Provide some C99 compatilities for all win system...hopefully there won't be no collision
IF(WIN32 AND NOT CYGWIN)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/C99"
  )
ENDIF(WIN32 AND NOT CYGWIN)

FIND_PACKAGE(PythonLibs REQUIRED)
INCLUDE_DIRECTORIES(
  ${PYTHON_INCLUDE_PATH}
  )
SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)

# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}")

#SET(GDCM_PYTHON_IMPLEMENTATION_NAME gdcmpython)
SET(GDCM_PYTHON_IMPLEMENTATION_NAME gdcm)
SET(CMAKE_SWIG_FLAGS "-interface _${GDCM_PYTHON_IMPLEMENTATION_NAME}")
SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)
SWIG_ADD_MODULE(${GDCM_PYTHON_IMPLEMENTATION_NAME} python gdcm.i)
SWIG_LINK_LIBRARIES(${GDCM_PYTHON_IMPLEMENTATION_NAME} gdcmMSFF gdcmIOD ${PYTHON_LIBRARIES})


# Python extension modules on Windows must have the extension ".pyd"
# instead of ".dll" as of Python 2.5.  Older python versions do support
# this suffix.
IF(WIN32 AND NOT CYGWIN)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME} PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32 AND NOT CYGWIN)

# swig generates a _gdcm.so and a gdcm.py, we need to copy gdcm.py to the proper place:
# gdcm.py is the interface name != implementation name, so we need to keep 'gdcm', so that 'import gdcm'
# from a python script alsways work
ADD_CUSTOM_COMMAND(
  TARGET    ${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME}
  POST_BUILD
  COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py ${LIBRARY_OUTPUT_PATH}
  DEPENDS "${swig_generated_file_fullname}"
  COMMENT   "Copy gdcm.py into ${LIBRARY_OUTPUT_PATH}"
)

#Module are always place in the library destination
#but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
# the python file is not a dev file, but part of the gdcm module...
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py 
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

FIND_PACKAGE(PythonInterp REQUIRED)
# Test that will try to load any class in the target langugage: python
# it make sure swig was not broken accidentally
SET_SOURCE_FILES_PROPERTIES(TestWrap.py PROPERTIES PYTHONPATH ${LIBRARY_OUTPUT_PATH})
ADD_PYTHON_TEST(TestWrapPython TestWrap.py ${GDCM_SOURCE_DIR}/Source)

