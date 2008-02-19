INCLUDE_DIRECTORIES(
  ${itkgdcm_SOURCE_DIR}
)
ADD_EXECUTABLE(gdcmitk gdcmitk.cxx)
TARGET_LINK_LIBRARIES(gdcmitk itkgdcm)
