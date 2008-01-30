/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
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
 * FIXME:
 * Still missing the Orientation !
 */
class GDCM_EXPORT Image
{
public:
  Image ():NumberOfDimensions(0),PlanarConfiguration(0),Dimensions(),SC(),NeedByteSwap(false),LUT(0) {}
  virtual ~Image() {}

  unsigned int GetNumberOfDimensions() const;
  void SetNumberOfDimensions(unsigned int dim);

  const unsigned int *GetDimensions() const;
  unsigned int GetDimension(unsigned int idx) const;
  void SetDimensions(unsigned int *dims);
  void SetDimension(unsigned int idx, unsigned int dim);

  // Get/Set PixelFormat
  const PixelFormat &GetPixelFormat() const
    {
    return PF;
    }
  void SetPixelFormat(PixelFormat const &pf)
    {
    PF = pf;
    }

  // Acces the raw data
  virtual bool GetBuffer(char *buffer) const;

  // TODO does this really belong here ?
  const double *GetSpacing() const;
  double GetSpacing(unsigned int idx) const;
  void SetSpacing(const double *spacing);
  void SetSpacing(unsigned int idx, double spacing);

  const double *GetOrigin() const;
  double GetOrigin(unsigned int idx) const;
  void SetOrigin(const float *ori);
  void SetOrigin(const double *ori);
  void SetOrigin(unsigned int idx, double ori);

  const double *GetDirectionCosines() const;
  double GetDirectionCosines(unsigned int idx) const;
  void SetDirectionCosines(const float *dircos);
  void SetDirectionCosines(const double *dircos);
  void SetDirectionCosines(unsigned int idx, double dircos);

  void Print(std::ostream &os) const;

  unsigned int GetPlanarConfiguration() const;
  void SetPlanarConfiguration(unsigned int pc);

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

  void SetLUT(LookupTable const &lut)
    {
    LUT = SmartPointer<LookupTable>( const_cast<LookupTable*>(&lut) );
    }
  const LookupTable &GetLUT() const
    {
    return *LUT;
    }

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


//  Image(Image const&);
//  Image &operator= (Image const&);

  // Return the length of the image after decompression
  // It will NOT take into account the Palette Color
  unsigned long GetBufferLength() const;

  // Same as above but takes into account Palette Color
  //unsigned long GetBufferPaletteLength() const;

  void SetTransferSyntax(TransferSyntax const &ts) {
    TS = ts;
  }
  const TransferSyntax &GetTransferSyntax() const {
    return TS;
  }

private:
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
  unsigned int NumberOfDimensions;

  typedef SmartPointer<LookupTable> LUTPtr;
  LUTPtr LUT;
  std::vector<Overlay>  Overlays;
};

} // end namespace gdcm

#endif //__gdcmImage_h

