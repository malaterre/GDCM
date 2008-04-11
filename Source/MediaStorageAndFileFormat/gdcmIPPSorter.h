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
#ifndef __gdcmIPPSorter_h
#define __gdcmIPPSorter_h

#include "gdcmSorter.h"

#include <vector>
#include <string>

namespace gdcm
{
/**
 * \brief IPPSorter
 */
class GDCM_EXPORT IPPSorter : public Sorter
{
public:
  IPPSorter();
  ~IPPSorter();

  // FIXME: I do not like public virtual function...
  virtual bool Sort(std::vector<std::string> const & filenames);

  void SetZSpacingTolerance(double tol) { ZTolerance = tol; }
  void SetComputeZSpacing(bool b) { ComputeZSpacing = b; }

  // read-only:
  double GetZSpacing() const { return ZSpacing; }

protected:
  bool ComputeZSpacing;
  double ZSpacing;
  double ZTolerance;
};


} // end namespace gdcm

#endif //__gdcmIPPSorter_h
