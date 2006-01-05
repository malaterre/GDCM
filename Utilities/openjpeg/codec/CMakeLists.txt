# Build the demo app, small examples

# First thing define the common source:
SET(common_SRCS
  convert.c
  )
# Then check if getopt is present:
INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
SET(DONT_HAVE_GETOPT 1)
IF(UNIX) #I am pretty sure only *nix sys have this anyway
  CHECK_INCLUDE_FILE("getopt.h" CMAKE_HAVE_GETOPT_H)
  # Seems like we need the contrary:
  IF(CMAKE_HAVE_GETOPT_H)
    SET(DONT_HAVE_GETOPT 0)
  ENDIF(CMAKE_HAVE_GETOPT_H)
ENDIF(UNIX)

# If not getopt was found then add it to the lib:
IF(DONT_HAVE_GETOPT)
  ADD_DEFINITIONS(-DDONT_HAVE_GETOPT)
  SET(common_SRCS
    ${common_SRCS}
    compat/getopt.c
  )
ENDIF(DONT_HAVE_GETOPT)


# Headers file are located here:
INCLUDE_DIRECTORIES(
  ${OPENJPEG_SOURCE_DIR}/libopenjpeg
  )

# Loop over all executables:
FOREACH(exe j2k_to_image image_to_j2k)
  ADD_EXECUTABLE(${exe} ${exe}.c ${common_SRCS})
  TARGET_LINK_LIBRARIES(${exe} gdcmopenjpeg)
  IF(UNIX)
    TARGET_LINK_LIBRARIES(${exe} -lm)
  ENDIF(UNIX)
ENDFOREACH(exe)

## $Id$
##
## makefile for OpenJPEG codec
#
#OPENJPEG_DIR = ../libopenjpeg
#
#ifndef DEBUG
#  LDFLAGS = -s -lm
#else
#  LDFLAGS = -lm
#endif
#
#CFLAGS = -Wall -O3 -fno-strength-reduce -fomit-frame-pointer -I$(OPENJPEG_DIR)
#
#OBJ_DIR_W32 = obj.w32
#BIN_DIR_W32 = bin.w32
#LIB_DIR_W32 = $(OPENJPEG_DIR)/lib.w32
#
#ifdef MINGW32
#  CC = i386-mingw32-gcc
#  CFLAGS += -DDONT_HAVE_GETOPT
#  OBJ_DIR = $(OBJ_DIR_W32)
#  BIN_DIR = $(BIN_DIR_W32)
#  LIB_DIR = lib.w32
#  all:   $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR) \
#   $(addprefix $(BIN_DIR)/,j2k_to_image.exe image_to_j2k.exe)
#else
#  CC = gcc
#  OBJ_DIR = obj
#  BIN_DIR = bin
#  LIB_DIR = lib
#  all:   $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR) \
#     $(addprefix $(BIN_DIR)/,j2k_to_image image_to_j2k)
#endif
#
#ifdef DYNAMIC
#  ifdef MINGW32
#    LIB_OPENJPEG = $(LIB_DIR)/libopenjpeg.dll
#    LDFLAGS += -L$(LIB_DIR) -lopenjpeg
#  else
#    LIB_OPENJPEG = $(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.so
#    LDFLAGS += -L$(OPENJPEG_DIR)/$(LIB_DIR) -lopenjpeg
#  endif
#else
#  LIB_OPENJPEG = $(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.a
#  LDFLAGS += $(LIB_OPENJPEG)
#endif
#
#$(BIN_DIR):
#   mkdir $(BIN_DIR)
#
#$(OBJ_DIR):
#   mkdir $(OBJ_DIR)
#
#$(LIB_DIR):   
#   mkdir $(LIB_DIR)
#
#$(LIB_DIR)/libopenjpeg.dll: $(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.dll
#   ln -sf ../$< $@
#$(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.dll:
#   cd $(OPENJPEG_DIR) && \
#   $(MAKE) $(OBJ_DIR) $(LIB_DIR) $(LIB_DIR)/libopenjpeg.dll
#$(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.a:
#   cd $(OPENJPEG_DIR) && \
#   $(MAKE) $(OBJ_DIR) $(LIB_DIR) $(LIB_DIR)/libopenjpeg.a
#$(OPENJPEG_DIR)/$(LIB_DIR)/libopenjpeg.so:
#   cd $(OPENJPEG_DIR) && \
#   $(MAKE) $(LIB_DIR) $(LIB_DIR)/libopenjpeg.so
#
#$(OBJ_DIR)/%.o:
#   $(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
#
#$(OBJ_DIR)/getopt.o:      compat/getopt.c
#$(OBJ_DIR)/convert.o:      convert.c
#$(OBJ_DIR)/j2k_to_image.o:   j2k_to_image.c
#$(OBJ_DIR)/image_to_j2k.o:   image_to_j2k.c convert.h
#
#J2I_OBJS = $(addprefix $(OBJ_DIR)/,j2k_to_image.o)
#I2J_OBJS = $(addprefix $(OBJ_DIR)/,image_to_j2k.o convert.o)
#
#$(BIN_DIR)/j2k_to_image:   $(J2I_OBJS) $(LIB_OPENJPEG)
#   ${CC} -o $@  $(J2I_OBJS) ${LDFLAGS} 
#
#$(BIN_DIR)/image_to_j2k:   $(I2J_OBJS) $(LIB_OPENJPEG)
#   ${CC} -o $@  $(I2J_OBJS) ${LDFLAGS} 
#
#$(BIN_DIR)/j2k_to_image.exe:   $(J2I_OBJS) $(LIB_OPENJPEG)
#   ${CC} -o $@  $(J2I_OBJS) ${LDFLAGS} 
#
#$(BIN_DIR)/image_to_j2k.exe:   $(I2J_OBJS) $(LIB_OPENJPEG) $(OBJ_DIR)/getopt.o
#   ${CC} -o $@  $(I2J_OBJS) ${LDFLAGS} $(OBJ_DIR)/getopt.o
#
#clean:
#   rm -f $(BIN_DIR_W32)/* $(BIN_DIR)/* $(OBJ_DIR_W32)/* $(OBJ_DIR)/*
