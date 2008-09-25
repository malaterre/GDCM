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
#ifndef __gdcmOrientation_h
#define __gdcmOrientation_h

#include "gdcmTypes.h"

namespace gdcm
{
  
/**
 * \brief class to handle Orientation
 */
class GDCM_EXPORT Orientation
{
public:
  Orientation();
  ~Orientation();

  /// Print
  void Print(std::ostream &) const;

  typedef enum {
    UNKNOWN,
    AXIAL,
    CORONAL,
    SAGITTAL,
    OBLIQUE
  } OrientationType;

  /// Return the type of orientation from a direction cosines
  /// Input is an array of 6 double
  static OrientationType GetType(const double dircos[6]);

  /// Return the label of an Orientation
  static const char *GetLabel(OrientationType type);

protected:
  static char GetMajorAxisFromPatientRelativeDirectionCosine(double x, double y, double z);

private:
  static const double obliquityThresholdCosineValue;
};

} // end namespace gdcm

#endif //__gdcmOrientation_h
