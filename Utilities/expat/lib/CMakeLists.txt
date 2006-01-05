PROJECT(GDCMEXPAT)
INCLUDE_REGULAR_EXPRESSION("^(expat|xml|ascii|utf|name|iascii|latin|gdcm).*$")

SET(expat_SRCS
  xmlparse.c
  xmltok.c
  xmlrole.c
)

INCLUDE_DIRECTORIES(
  ${GDCMEXPAT_SOURCE_DIR}
  ${GDCMEXPAT_BINARY_DIR}
)

IF(WIN32)
  IF(NOT BUILD_SHARED_LIBS)
    SET (GDCM_EXPAT_STATIC 1)
  ENDIF(NOT BUILD_SHARED_LIBS)
ENDIF(WIN32)

CONFIGURE_FILE(${GDCMEXPAT_SOURCE_DIR}/expatConfig.h.in
               ${GDCMEXPAT_BINARY_DIR}/expatConfig.h)

ADD_LIBRARY(gdcmexpat ${expat_SRCS})

