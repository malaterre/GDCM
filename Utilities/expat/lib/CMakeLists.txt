
SET(EXPAT_SRCS
  xmlparse.c
  xmltok.c
  xmlrole.c
)

ADD_LIBRARY(${EXPAT_LIBRARY_NAME} ${EXPAT_SRCS})

