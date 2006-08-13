# Documentation
IF(GDCM_DOCUMENTATION)

  FIND_PACKAGE(Doxygen REQUIRED)

  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/doxyfile.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    )

  ADD_CUSTOM_TARGET(doc-developer
    ALL
    ${DOXYGEN}
    ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    )

ENDIF(GDCM_DOCUMENTATION)

