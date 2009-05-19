#
## Also see "include/polarssl/config.h"
#
#CFLAGS  = -I../include -D_FILE_OFFSET_BITS=64
#OFLAGS  = -O
#
## MicroBlaze specific options:
## CFLAGS += -mno-xl-soft-mul -mxl-barrel-shift
#
## To compile on Plan9:
## CFLAGS += -D_BSD_EXTENSION
#
## To compile as a shared library:
## CFLAGS += -fPIC
#
#DLEXT=so
## OSX shared library extension:
## DLEXT=dylib
#
SET(SRCS
  aes.c arc4.c base64.c
  bignum.c  certs.c    debug.c    
  des.c    dhm.c    havege.c  
  md2.c    md4.c    md5.c    
  net.c    padlock.c  rsa.c    
  sha1.c    sha2.c    sha4.c    
  ssl_cli.c  ssl_srv.c  ssl_tls.c  
  timing.c  x509parse.c  xtea.c    
  camellia.c
)
ADD_LIBRARY(${POLARSSL_LIBRARY_NAME} ${SRCS})

SET_TARGET_PROPERTIES(${POLARSSL_LIBRARY_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})
set_target_properties(${POLARSSL_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)

IF(NOT POLARSSL_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${POLARSSL_LIBRARY_NAME}
    RUNTIME DESTINATION ${POLARSSL_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${POLARSSL_INSTALL_LIB_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${POLARSSL_INSTALL_LIB_DIR} COMPONENT Development
  ${CPACK_NAMELINK_TYPE}
  )
ENDIF(NOT POLARSSL_INSTALL_NO_LIBRARIES)
#OBJS=  aes.o    arc4.o    base64.o  \
#  bignum.o  certs.o    debug.o    \
#  des.o    dhm.o    havege.o  \
#  md2.o    md4.o    md5.o    \
#  net.o    padlock.o  rsa.o    \
#  sha1.o    sha2.o    sha4.o    \
#  ssl_cli.o  ssl_srv.o  ssl_tls.o  \
#  timing.o  x509parse.o  xtea.o    \
#  camellia.o
#
#.SILENT:
#
#all: static
#
#static: libpolarssl.a
#
#shared: libpolarssl.$(DLEXT)
#
#libpolarssl.a: $(OBJS)
#  echo "  AR    $@"
#  ar r $@ $(OBJS)
#  echo "  RL    $@"
#  ranlib $@
#
#libpolarssl.so: libpolarssl.a
#  echo "  LD    $@"
#  $(CC) -shared -Wl,-soname,$@ -o $@ $(OBJS)
#
#libpolarssl.dylib: libpolarssl.a
#  echo "  LD    $@"
#  $(CC) -dynamiclib -o $@ $(OBJS)
#
#.c.o:
#  echo "  CC    $<"
#  $(CC) $(CFLAGS) $(OFLAGS) -c $<
#
#clean:
#  rm -f *.o libpolarssl.*
#
