/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMIMAGECHANGEPHOTOMETRICINTERPRETATION_H
#define GDCMIMAGECHANGEPHOTOMETRICINTERPRETATION_H

#include "gdcmImageToImageFilter.h"
#include "gdcmPhotometricInterpretation.h"

namespace gdcm
{

class DataElement;
/**
 * \brief ImageChangePhotometricInterpretation class
 * \details Class to change the Photometric Interpetation of an input DICOM
 */
class GDCM_EXPORT ImageChangePhotometricInterpretation : public ImageToImageFilter
{
public:
  ImageChangePhotometricInterpretation():PI() {}
  ~ImageChangePhotometricInterpretation() {}

  /// Set/Get requested PhotometricInterpretation
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi) { PI = pi; }
  const PhotometricInterpretation &GetPhotometricInterpretation() const { return PI; }

  /// Change
  bool Change();

  /// colorspace converstion (based on CCIR Recommendation 601-2)
  template <typename T>
  static void RGB2YBR(T ybr[3], const T rgb[3]);
  template <typename T>
  static void YBR2RGB(T rgb[3], const T ybr[3]);

protected:
  bool ChangeMonochrome();
  bool ChangeYBR2RGB();
  bool ChangeRGB2YBR();

private:
  PhotometricInterpretation PI;
};

// http://en.wikipedia.org/wiki/YCbCr
template <typename T>
void ImageChangePhotometricInterpretation::RGB2YBR(T ybr[3], const T rgb[3])
{
  const double R = rgb[0];
  const double G = rgb[1];
  const double B = rgb[2];
  const double Y  =   0 + .2990   * R + .5870   * G + .1140   * B;
  const double CB = 128 - .168736 * R - .331264 * G + .5000   * B;
  const double CR = 128 + .5000   * R - .418688 * G - .081312 * B;
  //assert( Y >= 0  && Y <= 255 );
  //assert( CB >= 0 && CB <= 255 );
  //assert( CR >= 0 && CR <= 255 );
  ybr[0] = Y  /*+ 0.5*/;
  ybr[1] = CB /*+ 0.5*/;
  ybr[2] = CR /*+ 0.5*/;
}

template <typename T>
void ImageChangePhotometricInterpretation::YBR2RGB(T rgb[3], const T ybr[3])
{
  // https://en.wikipedia.org/wiki/YCbCr#JPEG_conversion
  const double Y  = ybr[0];
  const double Cb = ybr[1];
  const double Cr = ybr[2];
  const double r = Y                       + 1.402    * (Cr-128);
  const double g = Y - 0.344136 * (Cb-128) - 0.714136 * (Cr-128);
  const double b = Y + 1.772    * (Cb-128);
  double R = r < 0 ? 0 : r;
  R = R > 255 ? 255 : R;
  double G = g < 0 ? 0 : g;
  G = G > 255 ? 255 : G;
  double B = b < 0 ? 0 : b;
  B = B > 255 ? 255 : B;
  //assert( R >= 0 && R <= 255 );
  //assert( G >= 0 && G <= 255 );
  //assert( B >= 0 && B <= 255 );
  rgb[0] = R;
  rgb[1] = G;
  rgb[2] = B;
}

} // end namespace gdcm

#endif //GDCMIMAGECHANGEPHOTOMETRICINTERPRETATION_H
