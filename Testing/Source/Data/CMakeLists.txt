#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

FILE(GLOB GDCM_DATA_FILENAMES_GLOB
  "${GDCM_DATA_ROOT}/*.acr"
  "${GDCM_DATA_ROOT}/*.nema"
  "${GDCM_DATA_ROOT}/*.dcm"
  "${GDCM_DATA_ROOT}/*.DCM"
  "${GDCM_DATA_ROOT}/001*"
  # Those files do not have any extension, special regex:
  "${GDCM_DATA_ROOT}/DICOMDIR*"
  "${GDCM_DATA_ROOT}/dicomdir*"
  )

# List of images that are technically difficult to read
# Hopefully we will soon be able to read them
SET(BLACK_LIST_READER
  EmptyPixelData.dcm # Emtpy pixel, dcmdump returns 0 ... I do not think this is the right thing to do though
  Siemens-leonardo-bugged.dcm # Nearly impossible, waste of time anyway...

# grrrrrr do not handle swapping correctly (implicit dataset are such a pain)
  LIBIDO-16-ACR_NEMA-Volume.dcm
# TODO add seg lut support
  gdcm-US-ALOKA-16.dcm
  SegmentedPalette.dcm
# Papyrus:
  PET-cardio-Multiframe-Papyrus.dcm
# No way to read this image:
  ELSCINT1_LOSSLESS_RICE.dcm
# Toshiba US Private Data Storage 1.2.392.200036.9116.7.8.1.1.1
  TOSHIBA_MDW_HEADER.dcm
# TODO, nasty:
  PhilipsLosslessRice.dcm
# TS is skrewed up, and the whole dataset is a pain to read...
# I do not even believe there is a pattern
  WeirdToshibaTS.dcm
# Pixel Data is not were it should be :)
  3DDCM011.dcm 

# 16bits LUT...
  rle16sti.dcm
  rle16loo.dcm

# Overlay Data in Unused bit are not passed in TestImageWriter:
#  SIEMENS_GBS_III-16-ACR_NEMA_1.acr
#  SIEMENS_GBS_III-16-ACR_NEMA_1-ULis2Bytes.dcm

# quick fix:
  tst_not.dcm
  BogugsSequenceLengthCorrectItemLength.dcm
  BogugsItemAndSequenceLength.dcm
  BogusACRWithFileMeta.dcm
  TheralysGDCM120Bug.dcm

# vtkGDCMImageWriter + rescale does not work on the following images:
  LIBIDO-24-ACR_NEMA-Rectangle.dcm
)

SET(GDCM_DATA_FILENAMES)
SET(GDCM_BLACK_LIST_READER_DATA_FILENAMES)
FOREACH(filename ${GDCM_DATA_FILENAMES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST_READER})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_FILENAMES "${GDCM_DATA_FILENAMES}\n\"${filename}\",")
  ELSE(NOT bad_dicom)
    SET(GDCM_BLACK_LIST_READER_DATA_FILENAMES "${GDCM_BLACK_LIST_READER_DATA_FILENAMES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)


# Populate GDCM_DATA_FILENAMES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataFileNames.cxx.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataFileNames.cxx"
  )

