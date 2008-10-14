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
#ifndef __gdcmPixmap_h
#define __gdcmPixmap_h

#include "gdcmObject.h"
#include "gdcmDataElement.h"
#include "gdcmPhotometricInterpretation.h"
#include "gdcmPixelFormat.h"
#include "gdcmTransferSyntax.h"
#include "gdcmLookupTable.h"

#include <vector>

namespace gdcm
{
  
/**
 * \brief Pixmap class
 * A bitmap based image. Used as parent for both IconImage and the main Pixel Data Image
 * It does not contains any World Space information (IPP, IOP)
 */
class GDCM_EXPORT Pixmap : public Object
{
public:
  Pixmap();
  ~Pixmap();
  void Print(std::ostream &) const {}

  /// Return the number of dimension of the pixel data bytes; for example 2 for a 2D matrices of values
  unsigned int GetNumberOfDimensions() const;
  void SetNumberOfDimensions(unsigned int dim);

  /// return the planar configuration
  unsigned int GetPlanarConfiguration() const;
  void SetPlanarConfiguration(unsigned int pc);

  bool GetNeedByteSwap() const
    {
    return NeedByteSwap;
    }
  void SetNeedByteSwap(bool b)
    {
    NeedByteSwap = b;
    }


  /// Transfer syntax
  void SetTransferSyntax(TransferSyntax const &ts) {
    TS = ts;
  }
  const TransferSyntax &GetTransferSyntax() const {
    return TS;
  }
  void SetDataElement(DataElement const &de) {
    PixelData = de;
  }
  const DataElement& GetDataElement() const { return PixelData; }
  DataElement& GetDataElement() { return PixelData; }

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


  /// Return the dimension of the pixel data, first dimension (x), then 2nd (y), then 3rd (z)...
  const unsigned int *GetDimensions() const;
  unsigned int GetDimension(unsigned int idx) const;

  void SetColumns(unsigned int col) { SetDimension(0,col); }
  unsigned int GetColumns() const { return GetDimension(0); }
  void SetRows(unsigned int rows) { SetDimension(1,rows); }
  unsigned int GetRows() const { return GetDimension(1); }
  void SetDimensions(const unsigned int *dims);
  void SetDimension(unsigned int idx, unsigned int dim);
  // Get/Set PixelFormat
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
    PF.Validate();
    }

  /// return the photometric interpretation
  const PhotometricInterpretation &GetPhotometricInterpretation() const;
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi);

  bool IsEmpty() const { return Dimensions.size() == 0; }
  void Clear();

  /// Return the length of the image after decompression
  /// WARNING for palette color: It will NOT take into account the Palette Color
  /// thus you need to multiply this length by 3 if the image is RGB for instance.
  unsigned long GetBufferLength() const;

  /// Acces the raw data
  bool GetBuffer(char *buffer) const;

  virtual bool AreOverlaysInPixelData() const { return false; }

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

//private:
protected:
  unsigned int PlanarConfiguration;
  unsigned int NumberOfDimensions;
  TransferSyntax TS;
  PixelFormat PF; // SamplesPerPixel, BitsAllocated, BitsStored, HighBit, PixelRepresentation
  PhotometricInterpretation PI;
  // Mind dump: unsigned int is required here, since we are reading (0028,0008) Number Of Frames
  // which is VR::IS, so I cannot simply assumed that unsigned short is enough... :(
  std::vector<unsigned int> Dimensions; // Col/Row
  DataElement PixelData; // copied from 7fe0,0010

  typedef SmartPointer<LookupTable> LUTPtr;
  LUTPtr LUT;
  // I believe the following 3 ivars can be derived from TS ...
  bool NeedByteSwap;
};

} // end namespace gdcm

#endif //__gdcmPixmap_h
