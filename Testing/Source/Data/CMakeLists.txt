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
  "MR_Philips_Intera_Broken.dcm"
  "IM-0001-0052.dcm"
  "Resultat_015.dcm"
  "001073_Philips_Flair_Breaker_useNOSHADOWSEQ.dcm"
  "001073_Philips_Flair_Breaker.dcm"
  "001064_Philips_Flair_Breaker_useNOSHADOWSEQ.dcm"
  "FFBE146B651B2A44C6ADC12DB614E3ED.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_1.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_2.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_3.dcm"
  "ElemZeroNotGroupLength.dcm"
  "Run11"
  "Bug_Philips_ItemTag_3F3F"

  # ImageReader seg fault on that...
  "MR-MONO2-8-16x-heart.dcm"
  "NM-MONO2-16-13x-heart.dcm"
  "US-PAL-8-10x-echo.dcm"
  "rle16loo.dcm"
  "XA-MONO2-8-12x-catheter.dcm"
  "GE_DLX-8-MONO2-PrivateSyntax.dcm"
  "GE_DLX-8-MONO2-Multiframe.dcm"
  "GE_DLX-8-MONO2-Multiframe-Jpeg_Lossless.dcm"
  "GE_CT_With_Private_compressed-icon.dcm"
  "MR_GE_with_Private_Compressed_Icon_0009_1110.dcm"
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

# Adding extra file without no extension.
# Ok I know this is retarded but I don't want to rename file on cvs too much of a pain

SET(GDCM_NO_EXTENSION_FILES
  # Looks like a hard one:
  #1.3.12.2.1107.5.2.6.14121.30000006030706333268700005266
  DICOMDIR
  dicomdir_Acusson_WithPrivate_WithSR
  DICOMDIR_MR_B_VA12A
  DICOMDIR-Philips-EasyVision-4200-Entries
  # Problem in my code. but very good for timing since so many SQ
  #dicomdir_Pms_With_heavy_embedded_sequence
  dicomdir_Pms_WithVisit_WithPrivate_WithStudyComponents
  dicomdir_With_embedded_icons
  )

FOREACH(filename ${GDCM_NO_EXTENSION_FILES})
  SET(GDCM_DATA_IMAGES "${GDCM_DATA_IMAGES}\n\"${GDCM_DATA_ROOT}/${filename}\",")
ENDFOREACH(filename)

# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataImages.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataImages.h"
  )

