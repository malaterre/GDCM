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
#ifndef __gdcmOrientation_h
#define __gdcmOrientation_h

#include "gdcmTypes.h"

namespace gdcm
{
  
/*
 * \brief class to handle Orientation
 */
class GDCM_EXPORT Orientation
{
public:
  Orientation();
  ~Orientation();

  void Print(std::ostream &) const;

  typedef enum {
    UNKNOWN,
    AXIAL,
    CORONAL,
    SAGITTAL,
    OBLIQUE
  } OrientationType;

  static OrientationType GetType(const double *dircos);
  static const char *GetLabel(OrientationType type);

private:
};

} // end namespace gdcm

#endif //__gdcmOrientation_h
