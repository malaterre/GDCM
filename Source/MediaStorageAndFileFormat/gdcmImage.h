/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMIMAGE_H
#define GDCMIMAGE_H

#include "gdcmPixmap.h"
#if !defined(GDCM_LEGACY_REMOVE)
#include "gdcmSwapCode.h"
#endif

#include <vector>

namespace gdcm
{

/**
 * \brief Image
 * This is the container for an Image in the general sense.
 * From this container you should be able to request information like:
 * - Origin
 * - Dimension
 * - PixelFormat
 * ...
 * But also to retrieve the image as a raw buffer (char *)
 * Since we have to deal with both RAW data and JPEG stream (which
 * internally encode all the above information) this API might seems
 * redundant. One way to solve that would be to subclass gdcm::Image
 * with gdcm::JPEGImage which would from the stream extract the header info
 * and fill it to please gdcm::Image...well except origin for instance
 *
 * Basically you can see it as a storage for the Pixel Data element (7fe0,0010).
 *
 * \warning This class does some heuristics to guess the Spacing but is not
 * compatible with DICOM CP-586. In case of doubt use PixmapReader instead
 *
 * \see ImageReader PixmapReader
 */
class GDCM_EXPORT Image : public Pixmap
{
public:
  Image ()
    {
    OriginArray.resize(1);
    //OriginArray[0].resize( 3 /*NumberOfDimensions*/ ); // fill with 0
    OriginArray[0][0] = 0;
    OriginArray[0][1] = 0;
    OriginArray[0][2] = 0;
    DirectionCosinesArray.resize(1);
    //DirectionCosinesArray[0].resize( 6 ); // fill with 0
    DirectionCosinesArray[0][0] = 1;
    DirectionCosinesArray[0][1] = 1;
    DirectionCosinesArray[0][2] = 1;
    DirectionCosinesArray[0][3] = 1;
    DirectionCosinesArray[0][4] = 1;
    DirectionCosinesArray[0][5] = 1;
    SpacingArray.resize(1);
    //SpacingArray[0].resize( 3 /*NumberOfDimensions*/, 1 ); // fill with 1
    SpacingArray[0][0] = 1;
    SpacingArray[0][1] = 1;
    SpacingArray[0][2] = 1;
    InterceptSlopeArray.resize(1);
    InterceptSlopeArray[0][0] = 0.; // Intercept
    InterceptSlopeArray[0][1] = 1.; // Slope
    }
  ~Image() {}

  /// Return a 3-tuples specifying the spacing
  /// NOTE: 3rd value can be an aribtrary 1 value when the spacing was not specified (ex. 2D image).
  /// WARNING: when the spacing is not specifier, a default value of 1 will be returned
  const double *GetSpacing() const;
  double GetSpacing(unsigned int idx) const;
  void SetSpacing(const double spacing[3]);
  void SetSpacing(unsigned int idx, double spacing);

  /// Return a 3-tuples specifying the origin
  /// Will return (0,0,0) if the origin was not specified.
  const double *GetOrigin() const;
  double GetOrigin(unsigned int idx) const;
  void SetOrigin(const float ori[3]);
  void SetOrigin(const double ori[3]);
  void SetOrigin(unsigned int idx, double ori);

  /// Return a 6-tuples specifying the direction cosines
  /// A default value of (1,0,0,0,1,0) will be return when the direction cosines was not specified.
  const double *GetDirectionCosines() const;
  double GetDirectionCosines(unsigned int idx) const;
  void SetDirectionCosines(const float dircos[6]);
  void SetDirectionCosines(const double dircos[6]);
  void SetDirectionCosines(unsigned int idx, double dircos);

  /// print
  void Print(std::ostream &os) const;

  /// DEPRECATED DO NOT USE
  GDCM_LEGACY(SwapCode GetSwapCode() const)
  GDCM_LEGACY(void SetSwapCode(SwapCode sc))

  /// intercept
  GDCM_LEGACY(void SetIntercept(double intercept))
  GDCM_LEGACY(double GetIntercept() const)

  void SetIntercept(unsigned int idx, double intercept);
  double GetIntercept(unsigned int idx) const;

  /// slope
  GDCM_LEGACY(void SetSlope(double slope))
  GDCM_LEGACY(double GetSlope() const)

  void SetSlope(unsigned int idx, double slope);
  double GetSlope(unsigned int idx) const;

//  Image(Image const&);
//  Image &operator= (Image const&);

private:
  //typedef double (InterceptSlopeType)[2];
  //typedef double (DirectionCosinesType)[6];
  //typedef double (OriginType)[3];
  //typedef double (SpacingType)[3];
  // std::vector requires copy-constructible and assignable...
  template <size_t N>
  struct FixedArrayType
    { // mimic tr1::array
    double data[N]; 
    double& operator[](size_t idx) {return data[idx];}
    const double& operator[](size_t idx) const {return data[idx];}
    };
  typedef FixedArrayType<2> InterceptSlopeType;
  typedef FixedArrayType<6> DirectionCosinesType;
  typedef FixedArrayType<3> OriginType;
  typedef FixedArrayType<3> SpacingType;
private:
  std::vector< SpacingType > SpacingArray;
  std::vector< OriginType > OriginArray;
  std::vector< DirectionCosinesType > DirectionCosinesArray;
  std::vector< InterceptSlopeType > InterceptSlopeArray;
};

/**
 * \example DecompressImage.cs
 * This is a C# example on how to use gdcm::Image
 */

} // end namespace gdcm

#endif //GDCMIMAGE_H
