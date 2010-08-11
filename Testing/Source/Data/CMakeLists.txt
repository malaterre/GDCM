#-----------------------------------------------------------------------------

# We need to test the reading of all dicom images in the gdcmData directory
# First parse this directory and extract all images

SET(GDCM_DATA_IMAGE_FILENAMES_GLOB_EXPR
  "${GDCM_DATA_ROOT}/*.acr"
  "${GDCM_DATA_ROOT}/*.nema"
  "${GDCM_DATA_ROOT}/*.dcm"
  "${GDCM_DATA_ROOT}/001*"
)

SET(GDCM_DATA_DICOMDIR_FILENAMES_GLOB_EXPR
  # Those files do not have any extension, special regex:
  "${GDCM_DATA_ROOT}/dicomdir*"
)

# Case sensitive system:
IF(UNIX)
  SET(GDCM_DATA_IMAGE_FILENAMES_GLOB_EXPR
    ${GDCM_DATA_IMAGE_FILENAMES_GLOB_EXPR}
    "${GDCM_DATA_ROOT}/*.DCM"
  )
  SET(GDCM_DATA_DICOMDIR_FILENAMES_GLOB_EXPR
    ${GDCM_DATA_DICOMDIR_FILENAMES_GLOB_EXPR}
    "${GDCM_DATA_ROOT}/DICOMDIR*"
  )
ENDIF(UNIX)

# GLOB expression !
FILE(GLOB GDCM_DATA_IMAGE_FILENAMES_GLOB
  ${GDCM_DATA_IMAGE_FILENAMES_GLOB_EXPR}
  )

# Same for DICOMDIR:
FILE(GLOB GDCM_DATA_DICOMDIR_FILENAMES_GLOB
  ${GDCM_DATA_DICOMDIR_FILENAMES_GLOB_EXPR}
  )

SET(GDCM_DATA_FILENAMES_GLOB
  ${GDCM_DATA_IMAGE_FILENAMES_GLOB}
  ${GDCM_DATA_DICOMDIR_FILENAMES_GLOB}
)

# List of images that are technically difficult to read
# Hopefully we will soon be able to read them
SET(BLACK_LIST_READER
  EmptyPixelData.dcm # Emtpy pixel, dcmdump returns 0 ... I do not think this is the right thing to do though
  Siemens-leonardo-bugged.dcm # Nearly impossible, waste of time anyway...

# grrrrrr do not handle swapping correctly (implicit dataset are such a pain)
  LIBIDO-16-ACR_NEMA-Volume.dcm
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

# Name says it all
BogusItemStartItemEnd.dcm

# Overlay Data in Unused bit are not passed in TestImageWriter:
#  SIEMENS_GBS_III-16-ACR_NEMA_1.acr
#  SIEMENS_GBS_III-16-ACR_NEMA_1-ULis2Bytes.dcm

# quick fix:
  tst_not.dcm
  BogugsSequenceLengthCorrectItemLength.dcm
  BogugsItemAndSequenceLength.dcm
  BogusACRWithFileMeta.dcm
  CompressedLossy.dcm

# vtkGDCMImageWriter + rescale does not work on the following images:
  LIBIDO-24-ACR_NEMA-Rectangle.dcm

# remove for now
  IM-0001-0066.dcm
  4hd2a332a0je.dcm
  TheralysNoModalityNoObject.dcm
  ImplicitDeclaredAsExplicit.dcm
  TheralysGDCM1.dcm
  #MR_Spectroscopy_SIEMENS_OF.dcm
  #SIEMENS-MR-RGB-16Bits.dcm
# Recent issue with compression/decompression (overlay in pixel data not handled)
  SIEMENS_GBS_III-16-ACR_NEMA_1.acr
  SIEMENS_GBS_III-16-ACR_NEMA_1-ULis2Bytes.dcm
  image.acr
  PHILIPS_Gyroscan-8-MONO2-Odd_Sequence.dcm # ???
  MergeCOM3_330_IM50.dcm
  ImplicitVRInExplicitDataSet2.dcm
  BogugsItemAndSequenceLengthCorrected.dcm
#SC that are well hidden MR Image Storage
#  fffc0000UN.dcm
  MR-SIEMENS-DICOM-WithOverlays-extracted-overlays.dcm
# Private tags is SQ, but SQ is busted, GDCM fails since it tries to parse the SQ (dcmtk does not even try)
  BogusItemLengthImplicitPrivateAtt.dcm

# This image has an unknown Media Storage UID, when looking in Modality 'CR' is found;
# but at the same time, there is no such thing as IPP/IOP in a ComputedRadiographyImageStorage ...
#  gdcm-CR-DCMTK-16-NonSamplePerPix.dcm

# invalid j2k stream:
  PixelDataWithVRUN.dcm
  InvalidYCCForJ2K.dcm

# buggy dcm4che
  kos.dcm

)
IF(NOT GDCM_USE_PVRG)
  SET(BLACK_LIST_READER
    # The following should really fails according to JPEG spec, IJG is failing and even when forcing
    # decompression using IJG output is different from PVRG...
    # Apparently pvrg likes it this way...
    #  PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
    ${BLACK_LIST_READER}
    PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
  )
ENDIF(NOT GDCM_USE_PVRG)
IF(GDCM_WORDS_BIGENDIAN)
  SET(BLACK_LIST_READER
    ${BLACK_LIST_READER}
    MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm
    MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm
    PHILIPS_Intera-16-MONO2-Uncompress.dcm
    SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm
    PICKER-16-MONO2-No_DicomV3_Preamble.dcm
  )
ENDIF(GDCM_WORDS_BIGENDIAN)


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

