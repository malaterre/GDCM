#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

FILE(GLOB GDCM_DATA_FILENAMES_GLOB
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
  image.acr

# grrrrrr do not handle swapping correctly:
  GE_CT_With_Private_compressed-icon.dcm
  MR_GE_with_Private_Compressed_Icon_0009_1110.dcm
  US-RGB-8-epicard.dcm
  LIBIDO-16-ACR_NEMA-Volume.dcm
  PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm
# TODO add seg lut support
  gdcm-US-ALOKA-16.dcm
  SegmentedPalette.dcm
# Add YBR_FULL_422
  US-GE-4AICL142.dcm
# Add 12 bits support:
  MR-MONO2-12-angio-an1.acr
# Papyrus:
  PET-cardio-Multiframe-Papyrus.dcm
# No way to read this image:
  ELSCINT1_LOSSLESS_RICE.dcm
# Toshiba US Private Data Storage 1.2.392.200036.9116.7.8.1.1.1
  TOSHIBA_MDW_HEADER.dcm
# TODO, nasty:
  PhilipsLosslessRice.dcm


# Temp fix
  rle16loo.dcm
  SIEMENS_GBS_III-16-ACR_NEMA_1.acr  # private elements are a pain
  SIEMENS_SOMATOM-12-ACR_NEMA-ZeroLengthUs.acr # private ...
  gdcm-MR-SIEMENS-16-2.acr # private...
  SIEMENS_MAGNETOM-12-ACR_NEMA_2-Modern.dcm # private...
  SIEMENS_MAGNETOM-12-MONO2-FileSeq0.dcm
  SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm
  SIEMENS_MAGNETOM-12-MONO2-FileSeq2.dcm
  SIEMENS_MAGNETOM-12-MONO2-FileSeq3.dcm
  SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm
  SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm
  SIEMENS_MAGNETOM-12-MONO2-VRUN.dcm
  Compress_16bit_noPVRG.dcm
  db318_MR_STN_stimulator_T2_TSE_TRA__20071005161618048_4.dcm
)

SET(GDCM_DATA_FILENAMES)
SET(GDCM_BLACK_LIST_READER_DATA_FILENAMES)
FOREACH(filename ${GDCM_DATA_FILENAMES_GLOB})
  GET_FILENAME_COMPONENT(filename_name ${filename} NAME)
  #MESSAGE( ${filename_name} )

  STRING(REGEX MATCH ${filename_name} bad_dicom ${BLACK_LIST_READER})
  IF(NOT bad_dicom)
    SET(GDCM_DATA_FILENAMES "${GDCM_DATA_FILENAMES}\n\"${filename}\",")
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
    SET(GDCM_BLACK_LIST_READER_DATA_FILENAMES "${GDCM_BLACK_LIST_READER_DATA_FILENAMES}\n\"${filename}\",")
  ENDIF(NOT bad_dicom)
ENDFOREACH(filename)


# Populate GDCM_DATA_FILENAMES:
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/gdcmDataFileNames.cxx.in"
  "${CMAKE_CURRENT_BINARY_DIR}/gdcmDataFileNames.cxx"
  )

