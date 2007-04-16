# find md5sum

SET(Md5sum_FOUND FALSE)
FIND_PROGRAM(Md5sum_EXECUTABLE md5sum)

IF (Md5sum_EXECUTABLE)
   SET(Md5sum_FOUND TRUE)
ENDIF (Md5sum_EXECUTABLE)

# Report the results.
IF(NOT Md5sum_FOUND)
  SET(Md5sum_DIR_MESSAGE
    "Md5sum was not found. Make sure the entries Md5sum_* are set.")
  IF(NOT Md5sum_FIND_QUIETLY)
    MESSAGE(STATUS "${Md5sum_DIR_MESSAGE}")
  ELSE(NOT Md5sum_FIND_QUIETLY)
    IF(Md5sum_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "${Md5sum_DIR_MESSAGE}")
    ENDIF(Md5sum_FIND_REQUIRED)
  ENDIF(NOT Md5sum_FIND_QUIETLY)
ENDIF(NOT Md5sum_FOUND)

