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
#ifndef __gdcmDirectionCosines_h
#define __gdcmDirectionCosines_h

#include "gdcmTypes.h"

namespace gdcm
{
  
/**
 * \brief class to handle DirectionCosines
 */
class GDCM_EXPORT DirectionCosines
{
public:
  //DirectionCosines();
  DirectionCosines(const double *dircos = 0);
  ~DirectionCosines();

  void Print(std::ostream &) const;

  void Cross(double z[3]) const;
  double Dot() const;

  // Normalize in-place
  void Normalize();

  operator const double* () const { return Values; }

  bool IsValid() const;

private:
  double Values[6];
};

} // end namespace gdcm

#endif //__gdcmDirectionCosines_h
