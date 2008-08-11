PROJECT(toto)

FILE(READ ${CMAKE_CURRENT_SOURCE_DIR}/refman.tex refman_file)
STRING(REPLACE "]{hyperref}"
"]{hyperref}\\\\hypersetup{pdftitle={GDCM Reference Guide},pdfkeywords={DICOM},baseurl={http:\\/\\/gdcm.sourceforge.net}}\\\\hyperbaseurl{http:\\/\\/gdcm.sourceforge.net}"
patched_refman_file
${refman_file}
)

FILE(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/patched.tex ${patched_refman_file})
