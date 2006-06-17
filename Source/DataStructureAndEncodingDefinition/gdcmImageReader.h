
#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h

#include "gdcmReader.h"
#include "gdcmImageValue.h"

namespace gdcm
{
/**
 * \brief ImageReader
 * \note it's role is to convert the DICOM DataSet into a gdcm::Image
 * representation
 */
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  const Image& GetImage() const;
  //void SetImage(Image const &img);

private:
  ImageValue PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

