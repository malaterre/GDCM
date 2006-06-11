#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

FILE(GLOB GDCM_DATA_IMAGES_GLOB
  "${GDCM_DATA_ROOT}/*.acr"
  "${GDCM_DATA_ROOT}/*.dcm"
  )
SET(BLACK_LIST
  "dummy.dcm"
  "diazpost.dcm" # This one is nasty
  #"CT-MONO2-12-lomb-an2.acr" # contains wrong group length !!
  #"MR-MONO2-12-angio-an1.acr" # idem
  "Siemens-leonardo-bugged.dcm"
  "NM_FromJulius_Caesar.dcm"
  "1075235AnouncedAsBigEndianButIsLittleEndian.dcm"
  "deflate_image_dfl.dcm" # Nasty compressed dataset
  "deflate_wave_dfl.dcm"
  "deflate_report_dfl.dcm"
  "ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm"

  # TODO
  "gdcm-MR-PHILIPS-16-Multi-Seq.dcm"
  "PHILIPS_Intera-16-MONO2-Uncompress.dcm"
  "KODAK-12-MONO1-Odd_Terminated_Sequence.dcm"
  "PHILIPS_Gyroscan-8-MONO2-Odd_Sequence.dcm"
  "PICKER-16-MONO2-Nested_icon.dcm"
  "deflate_report.dcm"
  "MR_Philips-Intera_BreaksNOSHADOW.dcm"
  "MR_Philips_Intera_PrivateSequenceImplicitVR.dcm"
  "MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm"
  "MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm"
  # EASY:
  "SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm"
  )

SET(GDCM_DATA_IMAGES)
SET(GDCM_BLACK_LIST_DATA_IMAGES)
FOREACH(filename ${GDCM_DATA_IMAGES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  #MESSAGE( ${filename_name} )
  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_IMAGES "${GDCM_DATA_IMAGES}\n\"${filename}\",")
  ELSE(NOT bad_dicom)
    SET(GDCM_BLACK_LIST_DATA_IMAGES "${GDCM_BLACK_LIST_DATA_IMAGES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataImages.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataImages.h"
  )

