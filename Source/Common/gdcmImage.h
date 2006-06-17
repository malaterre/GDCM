
#ifndef __gdcmImage_h
#define __gdcmImage_h

#include "gdcmTypes.h"

#include <vector>

namespace gdcm
{

/**
 * \brief Image
 * \note
 * This is the container for an Image in the general sense.
 * From this container you should be able to request information like:
 * - Origin
 * - Dimension
 * - PixelType
 * ...
 * But also to retrieve the image as a raw buffer (char *)
 * Since we have to deal with both RAW data and JPEG stream (which
 * internally encode all the above information) this API might seems 
 * redundant. One way to solve that would be to subclass gdcm::Image
 * with gdcm::JPEGImage which would from the stream extract the header info
 * and fill it to please gdcm::Image...well except origin for instance
 * 
 */
class GDCM_EXPORT Image
{
public:
  Image ():NumberOfDimensions(0),Dimensions() {}
  virtual ~Image() {}

  unsigned int GetNumberOfDimensions() const;
  void SetNumberOfDimensions(unsigned int dim);

  const unsigned int *GetDimensions() const;
  void SetDimensions(unsigned int *dims);

  unsigned int GetSamplesPerPixel() const;
  void SetSamplesPerPixel(unsigned int spp);

  // BitsAllocated
  unsigned int GetBitsAllocated() const;
  void SetBitsAllocated(unsigned int ba);

  // BitsStored
  unsigned int GetBitsStored() const;
  void SetBitsStored(unsigned int bs);

  // HighBit
  unsigned int GetHighBit() const;
  void SetHighBit(unsigned int hb);

  // Acces the raw data
  virtual bool GetBuffer(char *buffer) const;

  // TODO does this really belong here ?
  const double *GetSpacing() const;
  void SetSpacing(double *spacing);

  const double *GetOrigin() const;
  void SetOrigin(double *ori);


//  Image(Image const&);
//  Image &operator= (Image const&);

protected:
  unsigned long GetBufferLength() const;

private:
  unsigned int NumberOfDimensions;
  std::vector<unsigned int> Dimensions;
  std::vector<double> Spacing;
  std::vector<double> Origin;

  unsigned int SamplesPerPixel;
  unsigned int BitsAllocated;
  unsigned int BitsStored;
  unsigned int HighBit;
};

} // end namespace gdcm

#endif //__gdcmImage_h

