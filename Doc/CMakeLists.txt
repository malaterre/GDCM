#-----------------------------------------------------------------------------
# Build the documentation

SET(HTML_DIR
  ${GDCM_DATA_DIR}/html
)

SET(TARGET_DIR
  ${HTML_DIR}/${DOC_MODULE}
)

#EXTRA_DIST = \
#  DoxyfileDeveloppers  \
#  DoxyfileUsers        \
#  DoxyPython.txt       \
#  DoxyMainPage.txt

IF(GDCM_DOCUMENTATION)

  # http://www.cmake.org/pipermail/cmake/2003-April/003673.html
  # Too bad CMake doesn't support multiline ""
  SET(GDCM_DOCUMENTATION_INPUT_COMMON
     "${GDCM_SOURCE_DIR}/Source
    #"${GDCM_SOURCE_DIR}/Source ${GDCM_SOURCE_DIR}/Doc/DoxyPython.txt ${GDCM_SOURCE_DIR}/Doc/DoxyVtkGdmReaderExamples.txt"
  )
  SET(GDCM_DOCUMENTATION_EXCLUDE_COMMON
    "${GDCM_SOURCE_DIR}/Source/gdcmJpeg.cxx ${GDCM_SOURCE_DIR}/Source/jdatasrc.cxx ${GDCM_SOURCE_DIR}/src/jdatadst.cxx"
  )
  
  IF(GDCM_VTK)
     SET(GDCM_DOCUMENTATION_INPUT_COMMON
         "${GDCM_DOCUMENTATION_INPUT_COMMON} ${GDCM_SOURCE_DIR}/vtk")
  ENDIF(GDCM_VTK)

  IF(DOT)
     GET_FILENAME_COMPONENT(GDCM_DOCUMENTATION_DOT_PATH ${DOT} PATH)
     SET(GDCM_DOCUMENTATION_HAVE_DOT "YES")
  ELSE(DOT)
     SET(GDCM_DOCUMENTATION_DOT_PATH "")
     SET(GDCM_DOCUMENTATION_HAVE_DOT "NO")
  ENDIF(DOT)

  #Should rewrite this thing with FOREACH:
  #-----------------------------------------------------------------------------
  # Build the documentation for developpers

  SET(GDCM_HTML_OUTPUT
    html.developper
  )
  SET(GDCM_DOCUMENTATION_INPUT
    "${GDCM_DOCUMENTATION_INPUT_COMMON} ${GDCM_SOURCE_DIR}/Doc/DoxyMainPage.txt"
  )
  SET(GDCM_DOCUMENTATION_EXCLUDE
    "${GDCM_DOCUMENTATION_EXCLUDE_COMMON}"
  )
  CONFIGURE_FILE(
      ${GDCM_SOURCE_DIR}/Doc/doxygen.config.in
      ${GDCM_BINARY_DIR}/Doc/DoxyfileDeveloppers
      IMMEDIATE
  )

  ADD_CUSTOM_TARGET(doc-developer
   ALL
   ${DOXYGEN}
   ${GDCM_BINARY_DIR}/Doc/DoxyfileDeveloppers)

  #-----------------------------------------------------------------------------
  # Build the documentation for user

  SET(GDCM_HTML_OUTPUT
    html.user
  )
  SET(GDCM_DOCUMENTATION_INPUT
    "${GDCM_DOCUMENTATION_INPUT_COMMON} ${GDCM_SOURCE_DIR}/Doc/DoxyMainPageUser.txt"
  )
  SET(GDCM_DOCUMENTATION_EXCLUDE
    "${GDCM_DOCUMENTATION_EXCLUDE_COMMON} ${GDCM_SOURCE_DIR}/src/gdcmTS.h ${GDCM_SOURCE_DIR}/src/gdcmTS.cxx"
  )
  CONFIGURE_FILE(
      ${GDCM_SOURCE_DIR}/Doc/doxygen.config.in
      ${GDCM_BINARY_DIR}/Doc/DoxyfileUsers
      IMMEDIATE
  )

  ADD_CUSTOM_TARGET(doc-user
   ALL
   ${DOXYGEN}
   ${GDCM_BINARY_DIR}/Doc/DoxyfileUsers)


  INSTALL_FILES(${HTML_DIR} "\\.css$")
  INSTALL_FILES(${HTML_DIR} "\\.png$")
  INSTALL_FILES(${HTML_DIR} "\\.html$")
  #INSTALL_FILES(${HTML_DIR} "\\.pl$")
  #INSTALL_FILES(${HTML_DIR} "\\.stop$")
ENDIF(GDCM_DOCUMENTATION)

#-----------------------------------------------------------------------------
# m4 that hasn't been translated

#dist-hook:
# rm -rf $(distdir)/html.developper

#.PHONY : html.developper latex man
