#include "gdcmImageConverter.h"
#include "gdcmImage.h"

namespace gdcm
{

ImageConverter::ImageConverter()
{
  Output = new Image;
}

ImageConverter::~ImageConverter()
{
  delete Output;
}

void ImageConverter::SetInput(Image const &input)
{
  Input = const_cast<Image*>(&input);
}

const Image& ImageConverter::GetOuput() const
{
  return *Output;
}

void ImageConverter::Convert()
{
}

} // end namespace gdcm
