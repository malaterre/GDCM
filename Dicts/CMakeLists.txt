#-----------------------------------------------------------------------------
# DICOM dictionary stuff
SET(DICT_SRCS
  gdcmPrepDict.cxx
  )

# Add the include paths
INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source"
  "${GDCM_SOURCE_DIR}/Source"
  )

ADD_EXECUTABLE(PrepDict ${DICT_SRCS}
  ${GDCM_SOURCE_DIR}/Source/gdcmVR.cxx
  ${GDCM_SOURCE_DIR}/Source/gdcmVM.cxx
  )
#TARGET_LINK_LIBRARIES(PrepDict gdcm)

  # Build our custom command :
  ADD_CUSTOM_COMMAND(
    OUTPUT    ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
    COMMAND   ${EXECUTABLE_OUTPUT_PATH}/PrepDict
    ARGS      ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
              ${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx
    DEPENDS   ${GDCM_SOURCE_DIR}/Dicts/DataDict.dic
    COMMENT   "Generating gdcmDefaultDicts.cxx based on DataDict.dic"
  )
  # Since the file gdcmDefaultDicts.cxx does not exist, mark it as GENERATED:
  SET_SOURCE_FILES_PROPERTIES(
    "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx" GENERATED)


  ##-----------------------------------------------------------------------------
  ## Generate our own 'DICOM' dictionary, based on the following dictionaries:
  #SET(ALL_DICTS
  #  #DataDict.dic
  #  "${GDCM_BINARY_DIR}/Dicts/gdcm.dic"
  #  )
  #
  ## Better solution
  #SET(TEST_DICT_BODY)
  #FOREACH(dict ${ALL_DICTS})
  #  # Properly set dependencies, therefore `touch Philips-Intera.dic` does not rebuild
  #  # but adding/removing a line in Philips-Intera.dic rebuild as expected
  #  CONFIGURE_FILE("${GDCM_SOURCE_DIR}/Dicts/${dict}"
  #       "${GDCM_BINARY_DIR}/Dicts/${dict}" COPYONLY IMMEDIATE)
  #  FILE(READ "${GDCM_SOURCE_DIR}/Dicts/${dict}" dict_append)
  #  SET(TEST_DICT_BODY "${TEST_DICT_BODY}\n${dict_append}")
  #ENDFOREACH(dict)
  #CONFIGURE_FILE("${GDCM_SOURCE_DIR}/Dicts/gdcm.dic.in"
  #  "${GDCM_BINARY_DIR}/Dicts/gdcm.dic" @ONLY IMMEDIATE)
  #
  ##-----------------------------------------------------------------------------
  ## Nice trick to avoid creating a .h file each time we compile gdcm
  ## Since CONFIGURE_FILE do a 'copy if different'
  ## We have to write the file here since is contains 'DICOM_DICTIONARY'
  ## Which is a variable afterward...
  #
  #FILE(READ "${GDCM_BINARY_DIR}/Dicts/gdcm.dic" ENT)
  #STRING(REGEX REPLACE "\r?\n" ";" ENT "${ENT}")
  #SET(DICOM_DATA_DICTIONARY "")
  #
  #FOREACH(line ${ENT})
  #  STRING(REGEX REPLACE
  #    "^([0-9a-fx][0-9a-fx][0-9a-fx][0-9a-fx]) ([0-9a-fx][0-9a-fx][0-9a-fx][0-9a-fx]) ([A-Zor ]+) ([1-9n-]+) (.*)$"
  #    "   {0x\\1, 0x\\2, \"\\3\" , \"\\4\" , \"\\5\"}, " nline "${line}")
  #  STRING(REGEX MATCH "^[0-9 ]+xx .*$" XX_TAG "${line}")
  #  IF(XX_TAG)
  #    #MESSAGE("${XX_TAG}")
  #    #SET(HEX_VAL "0 1 2 3 4 5 6 7 8 9 a b c d e f")
  #    SET(HEX_EVEN_VAL 0 2 4 6 8 a c e)
  #    FOREACH(I ${HEX_EVEN_VAL})
  #      FOREACH(J ${HEX_EVEN_VAL})
  #        STRING(REGEX REPLACE
  #          "^([0-9]+)xx ([0-9][0-9a-f][0-9a-f][0-9a-f]) ([A-Zor ]+) ([1-9n-]+) (.*)$"
  #          "   {0x\\1${I}${J}, 0x\\2, \"\\3\" , \"\\4\" , \"\\5\"}, " nline "${line}")
  #        #MESSAGE("${nline}")
  #      ENDFOREACH(J)
  #    ENDFOREACH(I)
  #  ELSE(XX_TAG)
  #    SET(DICOM_DATA_DICTIONARY "${DICOM_DATA_DICTIONARY}\n${nline}")
  #  ENDIF(XX_TAG)
  #ENDFOREACH(line)
  #
  #SET(DICOM_DATA_DICTIONARY "${DICOM_DATA_DICTIONARY} \n {0,0,0,0,0}")
  #
  ##-----------------------------------------------------------------------------
  ## ... Set the dictionnary
  #SET(DICOM_DIR_DICTIONARY "${DICOM_DIR_DICTIONARY} \n {0,0,0,0}")
  #
  #CONFIGURE_FILE("${GDCM_SOURCE_DIR}/Source/gdcmDefaultDicts.cxx.in" 
  #  "${GDCM_BINARY_DIR}/Source/gdcmDefaultDicts.cxx" IMMEDIATE)
  #
  ##-----------------------------------------------------------------------------
  #INSTALL_FILES(${GDCM_DATA_DIR} .dic
  #  DataDict
  #)

