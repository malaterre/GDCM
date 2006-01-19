
#ifndef __gdcmPixelData_h
#define __gdcmPixelData_h


#include "gdcmType.h"

namespace gdcm
{
/**
 * \brief Class to represent the Pixel Data
 * Graphical data (e.g., images or overlays) of variable pixel-depth encoded
 * in the Pixel Data Element, with Value Representation OW or OB. 
 * Additional descriptor Data Elements are often used to describe the 
 * contents of the Pixel Data element, such as:
 * - Bits Allocated (28,100)
 * - Bits Stored (28,101)
 * - High Bit (28,102)
 * - Pixel Representation (28,103)
 * - Pixel Data Element (7fe0,10)
 */
class GDCM_EXPORT PixelData
{
public:
  PixelData() { }
  ~PixelData() { }

private:
};

} // end namespace gdcm

#endif //__gdcmPixelData_h
