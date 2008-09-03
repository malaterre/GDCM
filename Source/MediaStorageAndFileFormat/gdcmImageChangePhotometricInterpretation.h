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
#ifndef __gdcmImageChangePhotometricInterpretation_h
#define __gdcmImageChangePhotometricInterpretation_h

#include "gdcmImageToImageFilter.h"
#include "gdcmPhotometricInterpretation.h"

namespace gdcm
{

class DataElement;
/**
 * \brief ImageChangePhotometricInterpretation class
 * Class to change the Photometric Interpetation of an input DICOM
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

protected:

private:
  PhotometricInterpretation PI;
};

} // end namespace gdcm

#endif //__gdcmImageChangePhotometricInterpretation_h

