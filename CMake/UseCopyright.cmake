# Handy macro to gather all copyright in a single file (to pass to cpack)

MACRO(CREATE_COPYRIGHT_FILE name)
  # Always cleanup the file:
  FILE(WRITE ${name} "")
  SET(COPYRIGHT_MODULE_FILENAME ${name})
ENDMACRO(CREATE_COPYRIGHT_FILE)

# Append copyright file
MACRO(APPEND_COPYRIGHT)
  # need to raise an error if COPYRIGHT_MODULE_FILENAME is not set...
  IF(EXISTS ${COPYRIGHT_MODULE_FILENAME} )
    FOREACH(filename ${ARGN})
      FILE(READ ${filename} content)
      FILE(APPEND ${COPYRIGHT_MODULE_FILENAME} ${content})
    ENDFOREACH(filename)
  ENDIF(EXISTS ${COPYRIGHT_MODULE_FILENAME} )
ENDMACRO(APPEND_COPYRIGHT)


