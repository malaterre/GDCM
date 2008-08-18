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
#ifndef __gdcmIconImage_h
#define __gdcmIconImage_h

#include "gdcmObject.h"
#include "gdcmDataElement.h"
#include "gdcmPhotometricInterpretation.h"
#include "gdcmPixelFormat.h"

#include <vector>

namespace gdcm
{
  
/**
 * \brief IconImage class
 */
class GDCM_EXPORT IconImage : public Object
{
public:
  IconImage();
  ~IconImage();
  void Print(std::ostream &) const {}

  void SetDataElement(DataElement const &de) {
    PixelData = de;
  }
  const DataElement& GetDataElement() const { return PixelData; }

  void SetColumns(unsigned int col) { SetDimension(0,col); }
  void SetRows(unsigned int rows) { SetDimension(1,rows); }
  void SetDimension(unsigned int idx, unsigned int dim);
  int GetColumns() const { return Dimensions[0]; }
  int GetRows() const { return Dimensions[1]; }
  // Get/Set PixelFormat
  const PixelFormat &GetPixelFormat() const
    {
    return PF;
    }
  void SetPixelFormat(PixelFormat const &pf)
    {
    PF = pf;
    }

  const PhotometricInterpretation &GetPhotometricInterpretation() const;
  void SetPhotometricInterpretation(PhotometricInterpretation const &pi);

  bool IsEmpty() const { return Dimensions.size() == 0; }
  void Clear();

  bool GetBuffer(char *buffer) const;

private:
  PixelFormat PF; // SamplesPerPixel, BitsAllocated, BitsStored, HighBit, PixelRepresentation
  PhotometricInterpretation PI;
  std::vector<unsigned int> Dimensions; // Col/Row
  std::vector<double> Spacing; // PixelAspectRatio ?
  DataElement PixelData; // copied from 7fe0,0010
  static const unsigned int NumberOfDimensions = 2;
};

} // end namespace gdcm

#endif //__gdcmIconImage_h
