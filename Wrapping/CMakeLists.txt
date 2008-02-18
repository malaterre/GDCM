# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
)
# Provide some C99 compatilities for all win system...hopefully there won't be no collision
IF(WIN32)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/C99"
  )
ENDIF(WIN32)

FIND_PACKAGE(PythonLibs REQUIRED)
INCLUDE_DIRECTORIES(
  ${PYTHON_INCLUDE_PATH}
  )
SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)

# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}")

SWIG_ADD_MODULE(gdcm python gdcm.i)
SWIG_LINK_LIBRARIES(gdcm gdcmMSFF ${PYTHON_LIBRARIES})

#  MESSAGE(${SWIG_MODULE_gdcm_REAL_NAME})
#  MESSAGE( "${swig_extra_generated_files}" )
#  MESSAGE( "${swig_generated_file_fullname}" )
#  MESSAGE( "${swig_extra_clean_files}" )
# swig generates a _gdcm.so and a gdcm.py, we need to copy gdcm.py to the proper place:
    ADD_CUSTOM_COMMAND(
      TARGET    ${SWIG_MODULE_gdcm_REAL_NAME}
      POST_BUILD
      COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py ${LIBRARY_OUTPUT_PATH}
      DEPENDS "${swig_generated_file_fullname}"
      COMMENT   "Copy gdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )

#MESSAGE(${SWIG_MODULE_gdcm_REAL_NAME})
#SWIG_GET_EXTRA_OUTPUT_FILES(

#Module are always place in the library destination
#but for poot win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_gdcm_REAL_NAME}
    RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Development
  )
# the python file is not a dev file, but part of the gdcm module...
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py 
    DESTINATION ${GDCM_INSTALL_LIB_DIR} COMPONENT Runtime
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)
#IF(BUILD_TESTING)
#  SUBDIRS(Testing)
#ENDIF(BUILD_TESTING)
