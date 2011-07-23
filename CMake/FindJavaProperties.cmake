#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# I can't get FindJNI.cmake to work, so instead re-write one more robust
# which only requires javac and java being in the PATH

#add_custom_command(
#    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/${example}.class
#    COMMAND ${JAVA_COMPILE} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/GetSystemProperty.java
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/GetSystemProperty.java
#    COMMENT "javac GetSystemProperty.java"
#  )
GET_FILENAME_COMPONENT(current_list_path ${CMAKE_CURRENT_LIST_FILE} PATH)
find_package(Java 1.5 REQUIRED)

# For some reason I have to use two execute_process instead of a chained one...
if(${current_list_path}/GetSystemProperty.java IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/GetSystemProperty.java)
execute_process(
  COMMAND ${Java_JAVAC_EXECUTABLE} ${current_list_path}/GetSystemProperty.java -d ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
endif()

set(JAVA_PROPERTY_LIST
  java.library.path
  os.arch
  os.name
  java.home
  sun.boot.library.path
  )
foreach(property ${JAVA_PROPERTY_LIST})
  string(TOUPPER ${property} property_upper)
  string(REPLACE "." "_" property_cmake_name ${property_upper})
  execute_process(
    COMMAND ${Java_JAVA_EXECUTABLE} GetSystemProperty ${property}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    OUTPUT_VARIABLE ${property_cmake_name}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  #message("${property} : ${property_cmake_name} : ${${property_cmake_name}}")
endforeach(property)
