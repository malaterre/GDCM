# Documentation
# http://www.stack.nl/~dimitri/doxygen
# http://www.stack.nl/~dimitri/doxygen/commands.html#cmdsa
IF(GDCM_DOCUMENTATION)

  FIND_PACKAGE(Doxygen REQUIRED)

  IF(GDCM_DOXYGEN_NO_FOOTER)
    SET(GDCM_HTML_FOOTER)
  ELSE(GDCM_DOXYGEN_NO_FOOTER)
    # Otherwise use gdcm/piwik/sf.net footer:
    SET(GDCM_HTML_FOOTER ${GDCM_SOURCE_DIR}/Utilities/doxygen/footer.html)
  ENDIF(GDCM_DOXYGEN_NO_FOOTER)
  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/doxyfile.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    )

  FILE(GLOB_RECURSE headerfiles
    "${GDCM_SOURCE_DIR}/Source/*.h"
    "${GDCM_SOURCE_DIR}/Wrapping/*.h"
    "${GDCM_SOURCE_DIR}/Utilities/VTK/*.h"
    "${GDCM_SOURCE_DIR}/Utilities/Insight/*.h"
    "${GDCM_SOURCE_DIR}/Utilities/doxygen/man/*.man"
  )
  #MESSAGE(${headerfiles})
  # We are depending only on header files and README.txt but other files
  # could be needed for complete dependencies
  FILE(GLOB_RECURSE examplefiles
    "${GDCM_SOURCE_DIR}/Examples/*.cxx"
    "${GDCM_SOURCE_DIR}/Examples/*.cs"
    "${GDCM_SOURCE_DIR}/Examples/*.java"
    "${GDCM_SOURCE_DIR}/Examples/*.py"
    )
  FILE(GLOB_RECURSE vtkexamplefiles
    "${GDCM_SOURCE_DIR}/Utilities/VTK/Examples/*.cxx"
    "${GDCM_SOURCE_DIR}/Utilities/VTK/Examples/*.cs"
    "${GDCM_SOURCE_DIR}/Utilities/VTK/Examples/*.java"
    "${GDCM_SOURCE_DIR}/Utilities/VTK/Examples/*.py"
    )
  SET(DOXYFILE_EXAMPLES)
  foreach(file ${examplefiles} ${vtkexamplefiles})
    get_filename_component(f ${file} NAME)
    set(DOXYFILE_EXAMPLES "${DOXYFILE_EXAMPLES}\n\\example ${f}")
  endforeach(file)
  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/TestsList.txt.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/TestsList.txt
    @ONLY
  )
  IF(GDCM_MINOR_VERSION MATCHES "[02468]$")
    SET(GDCM_DOC_PDF_LINK
      "http://gdcm.sourceforge.net/${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}/gdcm-${GDCM_VERSION}.pdf"
    )
    SET(GDCM_DOC_TARBALL_LINK
      "http://gdcm.sourceforge.net/${GDCM_MAJOR_VERSION}.${GDCM_MINOR_VERSION}/gdcm-${GDCM_VERSION}-doc.tar.gz"
    )
  ELSE(GDCM_MINOR_VERSION MATCHES "[02468]$")
    SET(GDCM_DOC_PDF_LINK
      "http://gdcm.sourceforge.net/gdcm-${GDCM_VERSION}.pdf"
    )
    SET(GDCM_DOC_TARBALL_LINK
      "http://gdcm.sourceforge.net/gdcm-${GDCM_VERSION}-doc.tar.gz"
    )
  ENDIF(GDCM_MINOR_VERSION MATCHES "[02468]$")
  CONFIGURE_FILE(
    ${GDCM_SOURCE_DIR}/Utilities/doxygen/README.txt.in
    ${GDCM_BINARY_DIR}/Utilities/doxygen/README.txt
    @ONLY
  )
  SET(GDCM_DOC_TARBALL
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm-${GDCM_VERSION}-doc.tar.gz
  )
  # epstopdf is needed: sudo apt-get install texlive-extra-utils
  # pdflatex is needed: sudo apt-get install texlive-latex-extra
  ADD_CUSTOM_COMMAND(
    OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
             ${CMAKE_CURRENT_BINARY_DIR}/latex/Makefile
    # let's create the tarball within the same custom command to avoid complex dep. rules.
             ${GDCM_DOC_TARBALL}
             ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex # output #1 (fake)
    # 1. first thing first let's run doxygen
    COMMAND  ${DOXYGEN}
    ARGS     ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
    # 2. tarball gen.
    COMMAND  ${CMAKE_COMMAND}
    ARGS     -E tar cfz ${GDCM_DOC_TARBALL} html
    DEPENDS  ${GDCM_BINARY_DIR}/Utilities/doxygen/Doxyfile
             ${GDCM_BINARY_DIR}/Utilities/doxygen/README.txt
             ${GDCM_BINARY_DIR}/Utilities/doxygen/TestsList.txt
             ${headerfiles}
    COMMENT  "GDCM: Creating doxygen doc + tarball"
    #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
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
      ARGS     -i.tmp -e "'s/]{hyperref}/]{hyperref}\\\\hypersetup{pdftitle={GDCM ${GDCM_VERSION} Reference Manual},pdfauthor={Mathieu Malaterre and co.},pdfsubject={Grassroots DICOM API reference},pdfkeywords={GDCM,DICOM,Network,Query\\/Retrieve,JPEG,Lossless JPEG,JPEG-LS,J2K,JPEG 2000,RLE},pdfpagemode={UseOutlines},bookmarks,bookmarksopen,pdfstartview={FitH},backref,colorlinks,linkcolor={black},citecolor={black},urlcolor={black},baseurl={http:\\/\\/gdcm.sourceforge.net}}\\\\hyperbaseurl{http:\\/\\/gdcm.sourceforge.net}/g'" ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex
      # Command #2
      COMMAND  ${SED_EXECUTABLE}
      ARGS     -i.tmp -e "'s/${sed_gdcm_source_dir}/gdcm/g'" ${CMAKE_CURRENT_BINARY_DIR}/latex/*.tex
      # Command #3
      COMMAND  ${CMAKE_MAKE_PROGRAM}
      DEPENDS  #${CMAKE_CURRENT_BINARY_DIR}/latex/refman.tex
${CMAKE_CURRENT_BINARY_DIR}/latex/Makefile
    #${GDCM_DOC_TARBALL}
      COMMENT  "GDCM: Creating (patched) pdf of documentation"
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    )
    if(PDFOPT_EXECUTABLE)
      add_custom_command(
        OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
        COMMAND  ${PDFOPT_EXECUTABLE}
        ARGS     ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
                 ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
        DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
        COMMENT  "GDCM: Creating optimized pdf version of documentation"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
        )
    else()
      add_custom_command(
        OUTPUT   ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
        COMMAND  ${CMAKE_COMMAND} -E copy
        ARGS     ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
                 ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
        DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
        COMMENT  "GDCM: Creating unoptimized pdf version of documentation"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
        )
    endif()
    # add target to 'ALL'
    ADD_CUSTOM_TARGET(GDCMDoxygenPDF
      ALL
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
      COMMENT  "GDCM: Executing GDCMDoxygenPDF"
    )
    INSTALL(FILES
      ${CMAKE_CURRENT_BINARY_DIR}/latex/gdcm-${GDCM_VERSION}.pdf
      DESTINATION ${GDCM_INSTALL_DOC_DIR}
    )
  ELSE(UNIX AND GDCM_PDF_DOCUMENTATION)
    # make DoxygenDoc depends on the final tarball thus all file are garantee to be generated
    ADD_CUSTOM_TARGET(GDCMDoxygenDoc
      ALL
      DEPENDS ${GDCM_DOC_TARBALL}
      COMMENT  "GDCM: Executing GDCMDoxygenDoc"
    )
  ENDIF(UNIX AND GDCM_PDF_DOCUMENTATION)

  # Install html pages:
  #INSTALL(FILES
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcm2vtk.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmconv.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmanon.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmgendir.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmdump.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmimg.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcminfo.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmpdf.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmraw.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmscanner.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmtar.html
  #  ${CMAKE_CURRENT_BINARY_DIR}/html/gdcmviewer.html
  #  DESTINATION ${GDCM_INSTALL_DOC_DIR} COMPONENT DebugDevel
  #)
  INSTALL(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcm2vtk.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcm2pnm.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmconv.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmanon.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmgendir.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmdump.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmdiff.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmimg.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcminfo.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmpdf.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmraw.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmscu.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmscanner.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmtar.1
    ${CMAKE_CURRENT_BINARY_DIR}/man/man1/gdcmviewer.1
    DESTINATION ${GDCM_INSTALL_MAN_DIR}/man1 COMPONENT DebugDevel
  )
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION ${GDCM_INSTALL_DOC_DIR}
    PATTERN "*.md5" EXCLUDE
    PATTERN "*.dot" EXCLUDE
  )

  # http://lists.debian.org/debian-italian/2006/12/msg00878.html
  # man2txt : man man | col -b | less

  IF(GDCM_USE_VTK)
    # Make this option a hidden option as vtkgdcm/doxygen stuff is a mess (copy/paste
    # from paraview). It always rerun -sigh-
    IF(GDCM_VTK_DOCUMENTATION)
      SET(BUILD_DOCUMENTATION 1)
    ENDIF(GDCM_VTK_DOCUMENTATION)
    SUBDIRS(vtk)
  ENDIF(GDCM_USE_VTK)

ENDIF(GDCM_DOCUMENTATION)
