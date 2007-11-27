#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

FILE(GLOB GDCM_DATA_IMAGES_GLOB
  "${GDCM_DATA_ROOT}/*.acr"
  "${GDCM_DATA_ROOT}/*.dcm"
  # Those files do not have any extension, special regex:
  "${GDCM_DATA_ROOT}/DICOMDIR*"
  "${GDCM_DATA_ROOT}/dicomdir*"
  )

# List of images that are technically difficult to read
# Hopefully we will soon be able to read them
SET(BLACK_LIST_READER
# Brain dead or no interest:
  EmptyPixelData.dcm # Emtpy pixel, dcmdump returns 0 ... I do not think this is the right thing to do though
  Siemens-leonardo-bugged.dcm # Nearly impossible, waste of time anyway...
# TODO (by priority)
  MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm

# For now not supported (in ReWrite mode):
# We are rewritting image with invalid VR what should we do ?
  gdcm-MR-PHILIPS-16-Multi-Seq.dcm
  PHILIPS_Intera-16-MONO2-Uncompress.dcm
  MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm
# TODO: One cannot write VR::UN in the meta header !
# oh well ... dicom3tools support them
#  THERALYS-12-MONO2-Uncompressed-Even_Length_Tag.dcm
#  GE_DLX-8-MONO2-PrivateSyntax.dcm
)

SET(GDCM_DATA_IMAGES)
SET(GDCM_BLACK_LIST_READER_DATA_IMAGES)
FOREACH(filename ${GDCM_DATA_IMAGES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  #MESSAGE( ${filename_name} )

  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST_READER})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_IMAGES "${GDCM_DATA_IMAGES}\n\"${filename}\",")
    #SET(GDCM_TEST_DCMTK 1)
    IF(GDCM_TEST_DCMTK)
      IF(DCMTK_DCMDUMP)
        ADD_TEST("DCMDUMP-ORI-${filename_name}" "${DCMTK_DCMDUMP}"
          "${filename}")
        ADD_TEST("DCMDUMP-${filename_name}" "${DCMTK_DCMDUMP}"
          "/tmp/debug/${filename_name}")
      ENDIF(DCMTK_DCMDUMP)
    ENDIF(GDCM_TEST_DCMTK)
  ELSE(NOT bad_dicom)
    SET(GDCM_BLACK_LIST_READER_DATA_IMAGES "${GDCM_BLACK_LIST_READER_DATA_IMAGES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)


# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataImages.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataImages.h"
  )

