# Documentation
# http://www.stack.nl/~dimitri/doxygen
# http://www.stack.nl/~dimitri/doxygen/commands.html#cmdsa
IF(GDCM_DOCUMENTATION)

  FIND_PACKAGE(Doxygen REQUIRED)

  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/doxyfile.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    )

	ADD_CUSTOM_COMMAND(
	  OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
    COMMAND  ${DOXYGEN}
    ARGS     ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    DEPENDS  ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    COMMENT  "Creating doxygen doc"
	  #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	  )

  SET(GDCM_DOC_TARBALL
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm-${GDCM_VERSION}-doc.tgz
  )
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

