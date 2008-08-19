INCLUDE_DIRECTORIES(
  ${itk_gdcm_SOURCE_DIR}
)
ADD_EXECUTABLE(gdcmitk gdcmitk.cxx)
TARGET_LINK_LIBRARIES(gdcmitk itkgdcm2)
