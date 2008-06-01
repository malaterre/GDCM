# Documentation
# http://www.stack.nl/~dimitri/doxygen
# http://www.stack.nl/~dimitri/doxygen/commands.html#cmdsa
IF(GDCM_DOCUMENTATION)

  FIND_PACKAGE(Doxygen REQUIRED)

  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/doxyfile.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    )

  FILE(GLOB_RECURSE headerfiles
    "${GDCM_SOURCE_DIR}/Source/*.h"
    "${GDCM_SOURCE_DIR}/Wrapping/*.h"
    "${GDCM_SOURCE_DIR}/Utilities/VTK/*.h"
    "${GDCM_SOURCE_DIR}/Utilities/Insight/*.h"
  )
  #MESSAGE(${headerfiles})
  # We are depending only on header files and README.txt but other files
  # could be needed for complete dependencies
	ADD_CUSTOM_COMMAND(
	  OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
    COMMAND  ${DOXYGEN}
    ARGS     ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    DEPENDS  ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
             ${GDCM_SOURCE_DIR}/README.txt
             ${headerfiles}
    COMMENT  "Creating doxygen doc"
	  #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	  )

  SET(GDCM_DOC_TARBALL
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm-${GDCM_VERSION}-doc.tgz
  )
  # every time doxygen runs, it overwrite index.html so depending only on
  # one single file is ok
  # tar command is executed using relative path, so that tar does not contains 
  # full path
  ADD_CUSTOM_COMMAND(
    OUTPUT   ${GDCM_DOC_TARBALL}
    COMMAND  ${CMAKE_COMMAND}
    ARGS     -E tar cfz ${GDCM_DOC_TARBALL} html
    DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
    COMMENT  "Creating tarball of documentation"
    #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
  ADD_CUSTOM_TARGET(DoxygenDoc
    ALL
    DEPENDS ${GDCM_DOC_TARBALL}
  )


ENDIF(GDCM_DOCUMENTATION)

