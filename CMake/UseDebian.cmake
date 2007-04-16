# create .deb file
# You need to setup CPack first !
# UGLY: I reuse CPACK_NSIS_CONTACT to get the contact name for the debian package...
# TODO: How do I transmit the 'Depends' line ?

# Thanks:
# Eric Noulard for initial UseRpmTools used as template

IF(UNIX)
  IF(NOT CMAKE_AR)
    MESSAGE(FATAL_ERROR "No ar")
  ENDIF(NOT CMAKE_AR)

    # Detect if CPack was included or not
  IF (NOT DEFINED "CPACK_PACKAGE_NAME") 
    MESSAGE(FATAL_ERROR "CPack was not included, you should include CPack before Using UseDebian")
  ENDIF (NOT DEFINED "CPACK_PACKAGE_NAME")

  MACRO(ADD_DEBIAN_TARGETS)
# $ ar tv cmake_2.4.5-1_i386.deb
# rw-r--r-- 0/0      4 Dec  4 22:58 2006 debian-binary
# rw-r--r-- 0/0   8981 Dec  4 22:58 2006 control.tar.gz
# rw-r--r-- 0/0 4893146 Dec  4 22:58 2006 data.tar.gz

# Need a newline:
# dpkg-deb: archive has no newlines in header
    FILE(WRITE ${CMAKE_BINARY_DIR}/debian-binary "2.0
" )

# debian policy enforce lower case for package name
    STRING(TOLOWER
      ${CPACK_PACKAGE_NAME}
      DEBIAN_PACKAGE_NAME
    )

    FILE(WRITE ${CMAKE_BINARY_DIR}/control
"Package: ${DEBIAN_PACKAGE_NAME}
Version: ${CPACK_PACKAGE_VERSION}
Section: devel
Priority: optional
Architecture: i386
Depends: libc6 (>= 2.3.6-6), libgcc1 (>= 1:4.1.1-12), libncurses5 (>= 5.4-5), libstdc++6 (>= 4.1.1-12)
Maintainer: ${CPACK_NSIS_CONTACT}
Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}
 .
 ${DEBIAN_PACKAGE_NAME} was packaged by UseDebian and CPack
 .
")


# TODO: No dependencies is done for now:
FIND_PACKAGE(Md5sum REQUIRED)

# BUG: md5sum are computed everytime
EXECUTE_PROCESS(
  COMMAND ${Md5sum_EXECUTABLE} ${CMAKE_BINARY_DIR}/CPackConfig.cmake
  OUTPUT_VARIABLE md5sum_VAR
#  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE md5sum_RES
)
FILE(WRITE ${CMAKE_BINARY_DIR}/md5sums ${md5sum_VAR})

ADD_CUSTOM_COMMAND(
  OUTPUT    ${CMAKE_BINARY_DIR}/control.tar.gz
  COMMAND   cmake -E tar
  ARGS      cfvz ${CMAKE_BINARY_DIR}/control.tar.gz control ${CMAKE_BINARY_DIR}/md5sums
  DEPENDS   ${CMAKE_BINARY_DIR}/control ${CMAKE_BINARY_DIR}/md5sums
  COMMENT   "Generating control.tar.gz"
  )


INCLUDE(${CMAKE_BINARY_DIR}/CPackConfig.cmake)
ADD_CUSTOM_TARGET(data_tgz
  COMMAND cpack -G TGZ --config CPackConfig.cmake
# TODO: How to get the cpack package name ?
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_FILE_NAME}.tar.gz ${CMAKE_BINARY_DIR}/data.tar.gz
)  

# Warning order is important:
# ar -r your-package-name.deb debian-binary control.tar.gz data.tar.gz
# eg: cmake_2.4.5-1_i386.deb
ADD_CUSTOM_COMMAND(
  OUTPUT    ${CMAKE_BINARY_DIR}/${DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-1_i386.deb
  COMMAND   ${CMAKE_AR}
  ARGS      -r ${CMAKE_BINARY_DIR}/${DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-1_i386.deb ${CMAKE_BINARY_DIR}/debian-binary
               ${CMAKE_BINARY_DIR}/control.tar.gz ${CMAKE_BINARY_DIR}/data.tar.gz
  DEPENDS   ${CMAKE_BINARY_DIR}/debian-binary ${CMAKE_BINARY_DIR}/control.tar.gz ${CMAKE_BINARY_DIR}/data.tar.gz
  COMMENT   "Generating deb package"
  )

ADD_CUSTOM_TARGET(debpackage
  DEPENDS ${CMAKE_BINARY_DIR}/${DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-1_i386.deb
  )
ADD_DEPENDENCIES(debpackage data_tgz)

  ENDMACRO(ADD_DEBIAN_TARGETS DEBNAME)


ENDIF(UNIX)

