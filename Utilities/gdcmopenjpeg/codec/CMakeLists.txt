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
  ${${OPENJPEG_NAMESPACE}_SOURCE_DIR}/libopenjpeg
  )

# Do the proper thing when building static...if only there was configured
# headers or def files instead
IF(NOT BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DOPJ_STATIC)
ENDIF(NOT BUILD_SHARED_LIBS)

# Loop over all executables:
FOREACH(exe j2k_to_image image_to_j2k)
  ADD_EXECUTABLE(${exe} ${exe}.c ${common_SRCS})
  TARGET_LINK_LIBRARIES(${exe} ${OPENJPEG_LIBRARY_NAME})
  # On unix you need to link to the math library:
  IF(UNIX)
    TARGET_LINK_LIBRARIES(${exe} -lm)
  ENDIF(UNIX)
IF(NOT OPENJPEG_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${exe}
    RUNTIME DESTINATION ${OPENJPEG_INSTALL_BIN_DIR} COMPONENT Applications
    LIBRARY DESTINATION ${OPENJPEG_INSTALL_LIB_DIR} COMPONENT Libraries
    ARCHIVE DESTINATION ${OPENJPEG_INSTALL_LIB_DIR} COMPONENT Development
  ${CPACK_NAMELINK_TYPE}
	)
ENDIF(NOT OPENJPEG_INSTALL_NO_LIBRARIES)
ENDFOREACH(exe)


