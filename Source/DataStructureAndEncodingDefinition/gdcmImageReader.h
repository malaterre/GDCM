
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
class StringStream;
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  const Image& GetImage() const;
  //void SetImage(Image const &img);

  bool Read();

protected:
  const char* GetPointerFromElement(Tag const &tag);
  bool ReadImage();
  bool ReadACRNEMAImage();
  
  // ugliest thing ever:
  unsigned short ReadUSFromTag( Tag const & t, StringStream &ss,
    std::string &conversion );

private:
  ImageValue PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

