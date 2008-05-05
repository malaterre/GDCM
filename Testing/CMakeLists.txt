
SET(GDCM_CMAKE_DIR "${GDCM_SOURCE_DIR}/CMake" CACHE INTERNAL "")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GDCM_CMAKE_DIR}")

FIND_PACKAGE(DCMTK)
FIND_PACKAGE(DICOM3TOOLS)

SUBDIRS(
  Source
  )

MACRO(PROCESSONEDIR DIRNAME SRCS TESTS)
  FILE(GLOB files
    ${DIRNAME}/*
  )
  FOREACH(file ${files})
    IF(IS_DIRECTORY ${file})
      IF("${file}" MATCHES ".svn")
        MESSAGE("${file} is svn dir")
        SET(SRCS ${SRCS} ${file})
      ELSE("${file}" MATCHES ".svn")
        #MESSAGE("${file} is dir")
        PROCESSONEDIR( ${file} "${SRCS}" "${TESTS}" )
      ENDIF("${file}" MATCHES ".svn")
    ELSE(IS_DIRECTORY ${file})
      #MESSAGE("${file} is file")
      GET_FILENAME_COMPONENT(filename ${file} NAME)
      IF("${filename}" MATCHES "Test" AND ${filename} MATCHES ".cxx")
        STRING(LENGTH ${filename} filename_length)
        #MESSAGE("${filename} is test, ${filename_length}")
        MATH(EXPR fileend "${filename_length} - 4 - 4") # Need to remove 'Test' and '.cxx'
        STRING(SUBSTRING ${filename} 4 ${fileend} classname)
        #MESSAGE("${classname} is tested")
        SET(TESTS ${TESTS} ${classname})
      #ENDIF("${filename}" MATCHES "Test")
      ENDIF("${filename}" MATCHES "Test" AND ${filename} MATCHES ".cxx")
    ENDIF(IS_DIRECTORY ${file})
  ENDFOREACH(file)
ENDMACRO(PROCESSONEDIR)

#SET(gdcm_src)
#SET(gdcm_tests)
#PROCESSONEDIR(
#    ${CMAKE_CURRENT_SOURCE_DIR}/Source
#    "${gdcm_src}"
#    "${gdcm_tests}"
#)
#
#MESSAGE("${gdcm_src}")
#MESSAGE("${gdcm_tests}")

