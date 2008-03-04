# ...
SUBDIRS(
  Attribute
  Common
  Data
  DataDictionary
  DataStructureAndEncodingDefinition
  InformationObjectDefinition
  MediaStorageAndFileFormat
  MessageExchangeDefinition
  )

# We can only run the dcmtk cross-checking test *only* after all the tests have run
# in particular once the TestWriter are done. This is garantee since SUBDIRS cmake command
# force the inspection of the directory first
FOREACH(filename ${GDCM_DATA_FILENAMES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST_READER})
  IF(NOT bad_dicom)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDUMP)
        ADD_TEST("DCMDUMP-\"${filename_name}\"" "${DCMTK_DCMDUMP}" "-M"
          "${GDCM_TEMP_DIRECTORY}/TestWriter/${filename_name}")
      ENDIF(DCMTK_DCMDUMP)
    ENDIF(GDCM_TEST_DCMTK)
ENDFOREACH(filename)

