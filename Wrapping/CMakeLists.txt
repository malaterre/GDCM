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
      COMMAND   cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py ${LIBRARY_OUTPUT_PATH}
      DEPENDS "${swig_generated_file_fullname}"
      COMMENT   "Copy gdcm.py into ${LIBRARY_OUTPUT_PATH}"
    )

#MESSAGE(${SWIG_MODULE_name_REAL_NAME})
#SWIG_GET_EXTRA_OUTPUT_FILES(


#IF(BUILD_TESTING)
#  SUBDIRS(Testing)
#ENDIF(BUILD_TESTING)
