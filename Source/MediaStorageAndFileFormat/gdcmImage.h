/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmImage_h
#define __gdcmImage_h

#include "gdcmPixmap.h"
#include "gdcmSwapCode.h"
#include "gdcmSmartPointer.h"
#include "gdcmOverlay.h"
#include "gdcmCurve.h"
#include "gdcmIconImage.h"

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
 * - PixelFormat
 * ...
 * But also to retrieve the image as a raw buffer (char *)
 * Since we have to deal with both RAW data and JPEG stream (which
 * internally encode all the above information) this API might seems 
 * redundant. One way to solve that would be to subclass gdcm::Image
 * with gdcm::JPEGImage which would from the stream extract the header info
 * and fill it to please gdcm::Image...well except origin for instance
 * 
 * Basically you can see it as a storage for the PixelData element.
 * However it was also used for MRSpectroscopy object (as proof of concept)
 */
class GDCM_EXPORT Image : public Pixmap
{
public:
  Image ():Pixmap(),Spacing(),SC(),Overlays(),Curves(),Icon(),Intercept(0),Slope(1) {
    //DirectionCosines.resize(6);
  Origin.resize( 3 /*NumberOfDimensions*/ ); // fill with 0
  DirectionCosines.resize( 6 ); // fill with 0
  DirectionCosines[0] = 1;
  DirectionCosines[4] = 1;
  Spacing.resize( 3 /*NumberOfDimensions*/, 1 ); // fill with 1

  }
  ~Image() {}

  /// Return a 3-tuples specifying the spacing
  /// NOTE: 3rd value can be an aribtrary 1 value when the spacing was not specified (ex. 2D image).
  /// WARNING: when the spacing is not specifier, a default value of 1 will be returned
  const double *GetSpacing() const;
  double GetSpacing(unsigned int idx) const;
  void SetSpacing(const double *spacing);
  void SetSpacing(unsigned int idx, double spacing);

  /// Return a 3-tuples specifying the origin
  /// Will return (0,0,0) if the origin was not specified.
  const double *GetOrigin() const;
  double GetOrigin(unsigned int idx) const;
  void SetOrigin(const float *ori);
  void SetOrigin(const double *ori);
  void SetOrigin(unsigned int idx, double ori);

  /// Return a 6-tuples specifying the direction cosines
  /// A default value of (1,0,0,0,1,0) will be return when the direction cosines was not specified.
  const double *GetDirectionCosines() const;
  double GetDirectionCosines(unsigned int idx) const;
  void SetDirectionCosines(const float *dircos);
  void SetDirectionCosines(const double *dircos);
  void SetDirectionCosines(unsigned int idx, double dircos);

  /// print
  void Print(std::ostream &os) const;

  /// DEPRECATED DO NOT USE
  SwapCode GetSwapCode() const
    {
    return SC;
    }
  void SetSwapCode(SwapCode sc)
    {
    SC = sc;
    }

  /// Curve: group 50xx
  Curve& GetCurve(unsigned int i = 0) { 
    assert( i < Curves.size() );
    return Curves[i]; 
  }
  const Curve& GetCurve(unsigned int i = 0) const { 
    assert( i < Curves.size() );
    return Curves[i]; 
  }
  unsigned int GetNumberOfCurves() const { return Curves.size(); }
  void SetNumberOfCurves(unsigned int n) { Curves.resize(n); }

  /// Overlay: group 60xx
  Overlay& GetOverlay(unsigned int i = 0) { 
    assert( i < Overlays.size() );
    return Overlays[i]; 
  }
  const Overlay& GetOverlay(unsigned int i = 0) const { 
    assert( i < Overlays.size() );
    return Overlays[i]; 
  }
  unsigned int GetNumberOfOverlays() const { return Overlays.size(); }
  void SetNumberOfOverlays(unsigned int n) { Overlays.resize(n); }

  /// returns if Overlays are stored in the unused bit of the pixel data:
  bool AreOverlaysInPixelData() const;

  /// Set/Get Icon Image
  const IconImage &GetIconImage() const { return Icon; }
  IconImage &GetIconImage() { return Icon; }

//  Image(Image const&);
//  Image &operator= (Image const&);

  /// intercept
  void SetIntercept(double intercept) { Intercept = intercept; }
  double GetIntercept() const { return Intercept; }

  /// slope
  void SetSlope(double slope) { Slope = slope; }
  double GetSlope() const { return Slope; }

private:
  std::vector<double> Spacing;
  std::vector<double> Origin;
  std::vector<double> DirectionCosines;

  // I believe the following 3 ivars can be derived from TS ...
  SwapCode SC;
  std::vector<Overlay>  Overlays;
  std::vector<Curve>  Curves;
  IconImage Icon;
  double Intercept;
  double Slope;

};

} // end namespace gdcm

#endif //__gdcmImage_h

