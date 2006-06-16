
#ifndef __gdcmImage_h
#define __gdcmImage_h

#include "gdcmTypes.h"

#include <vector>

namespace gdcm
{

/**
 * \brief Image
 * \note bla
 * I think gdcm::Image is not the right approach I would rather see a
 * gdcm::ExtractImageInformation coupled with the gdcm::PixelData
 * ExtractImageInformation would use the SOP class to find out image info (spacing, origin...)
 */

class PixelData;
class GDCM_EXPORT Image
{
public:
  Image ():Dimensions() {}
  ~Image() {}

  unsigned int GetDimension();

  unsigned int *GetSizes();
  double *GetSpacing();
  double *GetOrigin();
  unsigned int GetNumberOfScalarComponents();

private:
  std::vector<int> Dimensions;
  std::vector<double> Spacing;
  std::vector<double> Origin;
  // Pixel Type ??
  PixelData *Buffer;

  Image(Image const&);
  Image &operator= (Image const&);
};

}

#endif //__gdcmImage_h

