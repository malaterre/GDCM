IF(NOT JPEG_NAMESPACE)
  SET(JPEG_NAMESPACE "JPEG")
  STRING(TOLOWER ${JPEG_NAMESPACE} JPEG_LIBRARY_NAME)
  SET(JPEG_STANDALONE 1)
ENDIF(NOT JPEG_NAMESPACE)

PROJECT(${JPEG_NAMESPACE})

# Do full dependency headers.
INCLUDE_REGULAR_EXPRESSION("^.*$")

# memmgr back ends: compile only one of these into a working library
# (For now, let's use the mode that requires the image fit into memory.
# This is the recommended mode for Win32 anyway.)
SET(systemdependent_SRCS jmemnobs.c)

# library object files common to compression and decompression
SET(common_SRCS
jcomapi.c jutils.c jerror.c jmemmgr.c
)

# compression library object files
SET(compression_SRCS
jcapimin.c jcapistd.c jctrans.c jcparam.c  jcinit.c
jcmaster.c jcmarker.c jcmainct.c jcprepct.c jccoefct.c jccolor.c
jcsample.c jchuff.c jcphuff.c jcdctmgr.c jfdctfst.c jfdctflt.c
jdatadst.c
)

# Lossy (DCT) codec:
SET(comp_lossy_SRCS
jfdctint.c
jclossy.c

# lossless
jclossls.c

#jdarith.c
jcodec.c
jcscale.c
jcshuff.c
jclhuff.c
jcpred.c
jcdiffct.c
)

# decompression library object files
SET(decompression_SRCS
jdapimin.c jdapistd.c jdtrans.c  jdmaster.c
jdinput.c jdmarker.c jdhuff.c jdphuff.c jdmainct.c jdcoefct.c
jdpostct.c jddctmgr.c jidctfst.c jidctflt.c jidctint.c jidctred.c
jdsample.c jdcolor.c jquant1.c jquant2.c jdmerge.c
jdatasrc.c
)

SET(decomp_lossy_SRCS
 jdlossls.c jdlossy.c
 #jcarith.c
jdlhuff.c
jddiffct.c
jdpred.c
jdscale.c
jdshuff.c
)

SET(JPEG_HEADER_FILES
  jchuff.h  
  jdct.h  
  jdhuff.h  
  jerror.h  
  jinclude.h  
  jmemsys.h  
#  jmorecfg.h     #this one need to be configured
  jpegint.h  
  jpeglib.h  
  jversion.h
  jlossy.h
  jlossls.h
  )

SET(JPEG_SOURCES)
FOREACH(src
  ${systemdependent_SRCS}
  ${common_SRCS}
  ${compression_SRCS}
  ${decompression_SRCS}
  ${comp_lossy_SRCS}
  ${decomp_lossy_SRCS}
  )
  SET(JPEG_SOURCES ${JPEG_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
ENDFOREACH(src)

IF (WIN32)
  IF (BUILD_SHARED_LIBS)
    SET(JPEGDLL 1)
  ELSE (BUILD_SHARED_LIBS)
    SET(JPEGSTATIC 1)
  ENDIF (BUILD_SHARED_LIBS)
ENDIF (WIN32)


# Generate three libraries: jpeg 8bits, 12bits and 16bits
# using only one source directory

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# Particular case jmorecfg.h needs to be specified either 8, 12 or 16 bits:
FOREACH(bits 8 12 16)
  SET(CMAKE_BITS_IN_JSAMPLE ${bits})
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/jpegcmake.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/${bits}/jpegcmake.h
                 @ONLY IMMEDIATE)
  #ADD_LIBRARY(${JPEG_LIBRARY_NAME}${bits} ${JPEG_SOURCES})
  #INSTALL_TARGETS(/lib/InsightToolkit ${JPEG_NAMESPACE}jpeg${bits})
ENDFOREACH(bits)

SUBDIRS(8 12 16)
