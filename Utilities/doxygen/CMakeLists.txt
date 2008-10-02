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
  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/README.txt.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/README.txt
    @ONLY
  )
  ADD_CUSTOM_COMMAND(
    OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
             ${CMAKE_CURRENT_BINARY_DIR}/latex/Makefile
    COMMAND  ${DOXYGEN}
    ARGS     ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    DEPENDS  ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
             ${GDCM_BINARY_DIR}/Utilities/doxygen/README.txt
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

  # PDF building part:
  # When building latex, we have to run a custom command to produce the pdf file:
  IF(UNIX AND GDCM_PDF_DOCUMENTATION)
    FIND_PROGRAM(PDFOPT_EXECUTABLE pdfopt)
    FIND_PROGRAM(SED_EXECUTABLE sed)
    FIND_PACKAGE(LATEX REQUIRED)
    MARK_AS_ADVANCED(PDFOPT_EXECUTABLE SED_EXECUTABLE)
    # Let's customize the pdf tags a little usind sed:
    # Apparently egrep is also needed...
    # BAD: there is a circular dependency where refman.tex depend on refman.tex in the sed steps... 
    # hack our way in anyway by simply removing the dep...
    #ADD_CUSTOM_COMMAND(
    #  ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/patchtex.cmake 
    #) 
    # TODO, FOREACH(*.tex)
    # sed -i -e "/home/mmalaterre/Projects/" ...
    STRING(REPLACE "/" "\\/" sed_gdcm_source_dir ${GDCM_SOURCE_DIR})
    #MESSAGE(${sed_gdcm_source_dir})
    ADD_CUSTOM_COMMAND(
      OUTPUT   #${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex # output #1 (fake)
               ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf # output #2
      # Command #1
      COMMAND  ${SED_EXECUTABLE}
      ARGS     -i.tmp -e "'s/]{hyperref}/]{hyperref}\\\\hypersetup{pdftitle={GDCM Reference Manual},pdfauthor={Mathieu Malaterre and co.},pdfsubject={Grassroots DICOM API reference},pdfkeywords={GDCM,DICOM,JPEG,Lossless JPEG,JPEG-LS,J2K,JPEG 2000,RLE},pdfpagemode={UseOutlines},bookmarks,bookmarksopen,pdfstartview={FitH},backref,colorlinks,linkcolor={black},citecolor={black},urlcolor={black},baseurl={http:\\/\\/gdcm.sourceforge.net}}\\\\hyperbaseurl{http:\\/\\/gdcm.sourceforge.net}/g'" ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex
      # Command #2
      COMMAND  ${SED_EXECUTABLE}
      ARGS     -i.tmp -e "'s/${sed_gdcm_source_dir}/gdcm/g'" ${CMAKE_CURRENT_BINARY_DIR}/latex/*.tex
      # Command #3
      COMMAND  ${CMAKE_MAKE_PROGRAM}
      DEPENDS  #${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex 
${CMAKE_CURRENT_BINARY_DIR}/latex/Makefile
      COMMENT  "Creating (patched) pdf of documentation"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    )
    #ADD_CUSTOM_COMMAND(
    #  OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
    #  DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/latex/Makefile ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex
    #  COMMENT  "Creating pdf of documentation"
    #  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    #)
    #  MESSAGE(${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf)
    ADD_CUSTOM_COMMAND(
      OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
      COMMAND  ${PDFOPT_EXECUTABLE}
      ARGS     ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf 
               ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
      DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
      COMMENT  "Creating optimized pdf version of documentation"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    )
    # add target to 'ALL'
    ADD_CUSTOM_TARGET(DoxygenPDF
      ALL
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
    )
  ENDIF(UNIX AND GDCM_PDF_DOCUMENTATION)

ENDIF(GDCM_DOCUMENTATION)

