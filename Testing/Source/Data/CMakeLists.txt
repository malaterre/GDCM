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

# Intersting images:
# Implicit with defined length SQ:
#  MR_SIEMENS_forceLoad29-1010_29-1020.dcm # 0008,1140
#  MR_forceLoad29-1010_29-1020.dcm
#  eclipse_dose.dcm # 300c,0002
#  GE_DLX-8-MONO2-PrivateSyntax.dcm # 0028,6100; (0050,0010)
#  PET-cardio-Multiframe-Papyrus.dcm # (0041,1010); (0041,1050)
#  gdcm-US-ALOKA-16.dcm #(0018,6011)
#  spine.dcm # (0008,1140)
#  gdcm-CT-GE-16-GantryTilt.dcm #(0008,1140)
#  abdominal.dcm # (0008,1140)
#  MR_Philips_Intera_Kosher.dcm #(0008,1111) , (0008,1140)
#  #Tag: (0008,1111) is a defined length SQ of 248
#  #Tag: (0008,1140) is a defined length SQ of 408
#  #Tag: (0029,200f) is a defined length SQ of 244
#  #Tag: (0029,201b) is a defined length SQ of 216
#  #Tag: (0029,2021) is a defined length SQ of 114
#  #Tag: (0029,204c) is a defined length SQ of 140
#  #Tag: (2001,105f) is a defined length SQ of 338
#  #Tag: (2005,1080) is a defined length SQ of 778
#  #Tag: (2005,1084) is a defined length SQ of 172
#  MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
#  eclipse_plan.dcm
#  # Tag: (0008,1140) is a defined length SQ of 324
#  # Tag: (2001,fc5f) is a defined length SQ of 322
#  # Tag: (2005,fb80) is a defined length SQ of 444
#  brain.dcm
#  SYNGORTImage.dcm
#  GE_DLX-8-MONO2-Multiframe.dcm
#  PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm

# List of images that are technically difficult to read
# Hopefully we will soon be able to read them
SET(BLACK_LIST_READER
  "dummy.dcm"
  "diazpost.dcm" # This one is nasty
  "Siemens-leonardo-bugged.dcm"
  "NM_FromJulius_Caesar.dcm"
  "1075235AnouncedAsBigEndianButIsLittleEndian.dcm"
  "deflate_image_dfl.dcm" # Nasty compressed dataset
  "deflate_wave_dfl.dcm"
  "deflate_report_dfl.dcm"
  "ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm"
  "1.3.12.2.1107.5.2.6.14121.30000006030706333268700005266.dcm"

  # TODO
  "gdcm-MR-PHILIPS-16-Multi-Seq.dcm"
  "PHILIPS_Intera-16-MONO2-Uncompress.dcm"
  "deflate_report.dcm"
  "MR_Philips_Intera_PrivateSequenceImplicitVR.dcm"
  "MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm"
  "MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm"
  "MR_Philips_Intera_Broken.dcm"
  "Resultat_015.dcm"
  "001073_Philips_Flair_Breaker_useNOSHADOWSEQ.dcm"
  "001073_Philips_Flair_Breaker.dcm"
  "001064_Philips_Flair_Breaker_useNOSHADOWSEQ.dcm"
  "FFBE146B651B2A44C6ADC12DB614E3ED.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_1.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_2.dcm"
  "Philips-Intera_Unexpected_Sequence_Terminator_3.dcm"
  "Run11"
  "Bug_Philips_ItemTag_3F3F"

  # TODO
  "MR-MONO2-12-angio-an1.acr" # 12 bits
  # Do not detect 4D:
  "IM-0001-0052.dcm"

  # TODO: TestWriter cannot rewrite those:
  MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
  # Ok I need to read the std Samples Per Pixel is 1 but there are lookup 
  # tables that are not implemented...delay this image for now
  ETIAM_video_002.dcm
  rle16loo.dcm
  US-GE-4AICL142.dcm
  D_CLUNIE_RG3_JPLY.dcm  # even dcmtk is producing garbage...
  SIEMENS_GBS_III-16-ACR_NEMA_1.acr # same as above

  # TODO...simply segfault
  US-PAL-8-10x-echo.dcm
  gdcm-US-ALOKA-16.dcm
  PET-cardio-Multiframe-Papyrus.dcm
  10200901_8b_Palette_RLE_blinker.dcm
  10200900_8b_Palette_RLE_blinker.dcm
  10200905_8b_Palette_RLE_blinker.dcm
  rle16loop_16b_Palette_RLE.dcm
  bla.dcm
  )

# List of files that are impossible to rewrite
# basically they contains something like a wrong length
# therefore it does not make any sense to try to rewrite them identically
# Necessary condition they should break toolkit like dcmtk -for instance-
SET(BLACK_LIST_WRITER
  # Length is set to 13 instead of 10
  GE_GENESIS-16-MONO2-WrongLengthItem.dcm
  # Contains: b00c 0eb6 d150 0e02
  # instead of the regular SQ termination element: fffe e0dd 0000 0000
  gdcm-JPEG-LossLess3a.dcm
  # Length for (0009,1113) & (0009,1114) is set to 6 instead of 4
  SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm
  # Elements are not ordered...GDCM2 is not able to produce a warning
  # for that...TODO FIXME
  # In SQ: 0004|1220, Elements are: (00a9,0020), (0010,0030), (0010,0040)
  # instead of (0010,0030), (0010,0040), (00a9,0020)
  dicomdir_Pms_WithVisit_WithPrivate_WithStudyComponents
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

  # Files that cannot be rewritten
  STRING(REGEX MATCH ${filename_name} no_rewrite ${BLACK_LIST_WRITER})
  IF(no_rewrite)
    SET(GDCM_BLACK_LIST_WRITER_DATA_IMAGES "${GDCM_BLACK_LIST_WRITER_DATA_IMAGES}\n\"${filename}\",")
  ENDIF(no_rewrite)
ENDFOREACH(filename)


# Populate GDCM_DATA_IMAGES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataImages.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataImages.h"
  )

