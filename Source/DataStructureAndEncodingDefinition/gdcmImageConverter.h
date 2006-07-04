
#ifndef __gdcmImageConverter_h
#define __gdcmImageConverter_h

#include "gdcmImage.h"

namespace gdcm
{

/**
 * \brief Image Converter
 * \note
 * This is the class used to convert from on gdcm::Image to another
 * This is typically used to convert let say YBR JPEG compressed 
 * gdcm::Image to a RAW RGB gdcm::Image. So that the buffer can be directly
 * pass to third party application.
 * This filter is application level and not integrated directly in GDCM
 */
class Filter;
class GDCM_EXPORT ImageConverter : public Filter
{
public:
  ImageConverter() {}
  ~ImageConverter() {}

  void SetInput(Image const &input);
  const Image& GetOuput() const;

private:
};

} // end namespace gdcm

#endif //__gdcmImageConverter_h

