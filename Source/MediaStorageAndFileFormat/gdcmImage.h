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

#include "gdcmPixelFormat.h"
#include "gdcmSwapCode.h"
#include "gdcmPhotometricInterpretation.h"
#include "gdcmLookupTable.h"
#include "gdcmSmartPointer.h"
#include "gdcmTransferSyntax.h"
#include "gdcmOverlay.h"
#include "gdcmCurve.h"
#include "gdcmIconImage.h"
#include "gdcmDataElement.h"

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
class GDCM_EXPORT Image : public Object
{
public:
  Image ():NumberOfDimensions(0),PlanarConfiguration(0),Dimensions(),Spacing(),SC(),NeedByteSwap(false),LUT(0),Overlays(),Curves(),Icon(),Intercept(0),Slope(1),PixelData() {
    //DirectionCosines.resize(6);
  }
  ~Image() {}

  /// Return the number of dimension of the pixel data bytes; for example 2 for a 2D matrices of values
  unsigned int GetNumberOfDimensions() const;
  void SetNumberOfDimensions(unsigned int dim);

  /// Return the dimension of the pixel data, first dimension (x), then 2nd (y), then 3rd (z)...
  const unsigned int *GetDimensions() const;
  unsigned int GetDimension(unsigned int idx) const;
  void SetDimensions(const unsigned int *dims);
  void SetDimension(unsigned int idx, unsigned int dim);

  /// Get/Set PixelFormat
  const PixelFormat &GetPixelFormat() const
    {
    return PF;
    }
  PixelFormat &GetPixelFormat()
    {
    return PF;
    }
  void SetPixelFormat(PixelFormat const &pf)
    {
    PF = pf;
    if( !PF.Validate() )
      {
      }
    }

  /// Acces the raw data
  bool GetBuffer(char *buffer) const;

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

  /// return the planar configuration
  unsigned int GetPlanarConfiguration() const;
  void SetPlanarConfiguration(unsigned int pc);

  /// return the photometric interpretation
  const PhotometricInterpretation &GetPhotometricInterpretation() const;
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi);

  SwapCode GetSwapCode() const
    {
    return SC;
    }
  void SetSwapCode(SwapCode sc)
    {
    SC = sc;
    }

  bool GetNeedByteSwap() const
    {
    return NeedByteSwap;
    }
  void SetNeedByteSwap(bool b)
    {
    NeedByteSwap = b;
    }

  /// Set/Get LUT
  void SetLUT(LookupTable const &lut)
    {
    LUT = SmartPointer<LookupTable>( const_cast<LookupTable*>(&lut) );
    }
  const LookupTable &GetLUT() const
    {
    return *LUT;
    }
  LookupTable &GetLUT()
    {
    return *LUT;
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

  /// Return the length of the image after decompression
  /// WARNING for palette color: It will NOT take into account the Palette Color
  /// thus you need to multiply this length by 3 if the image is RGB for instance.
  unsigned long GetBufferLength() const;

  /// Transfer syntax
  void SetTransferSyntax(TransferSyntax const &ts) {
    TS = ts;
  }
  const TransferSyntax &GetTransferSyntax() const {
    return TS;
  }

  /// intercept
  void SetIntercept(double intercept) { Intercept = intercept; }
  double GetIntercept() const { return Intercept; }

  /// slope
  void SetSlope(double slope) { Slope = slope; }
  double GetSlope() const { return Slope; }


  void SetDataElement(DataElement const &de) {
    PixelData = de;
  }
  const DataElement& GetDataElement() const { return PixelData; }
  DataElement& GetDataElement() { return PixelData; }

protected:
  bool TryRAWCodec(char *buffer) const;
  bool TryJPEGCodec(char *buffer) const;
  bool TryPVRGCodec(char *buffer) const;
  bool TryJPEGLSCodec(char *buffer) const;
  bool TryJPEG2000Codec(char *buffer) const;
  bool TryRLECodec(char *buffer) const;

  bool TryJPEGCodec2(std::ostream &os) const;
  bool TryJPEG2000Codec2(std::ostream &os) const;

  bool GetBuffer2(std::ostream &os) const;

private:
  unsigned int NumberOfDimensions;
  unsigned int PlanarConfiguration;
  std::vector<unsigned int> Dimensions;
  std::vector<double> Spacing;
  std::vector<double> Origin;
  std::vector<double> DirectionCosines;

  PixelFormat PF;
  PhotometricInterpretation PI;

  TransferSyntax TS;
  // I believe the following 3 ivars can be derived from TS ...
  SwapCode SC;
  bool NeedByteSwap;
  typedef SmartPointer<LookupTable> LUTPtr;
  LUTPtr LUT;
  std::vector<Overlay>  Overlays;
  std::vector<Curve>  Curves;
  IconImage Icon;
  double Intercept;
  double Slope;

  DataElement PixelData; //copied from 7fe0,0010

};

} // end namespace gdcm

#endif //__gdcmImage_h

