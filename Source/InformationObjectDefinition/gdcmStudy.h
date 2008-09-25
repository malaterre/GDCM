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
#ifndef __gdcmStudy_h
#define __gdcmStudy_h

#include "gdcmTypes.h"
#include "gdcmSeries.h"

#include <vector>

namespace gdcm
{
/**
 * \brief Study
 */
class GDCM_EXPORT Study
{
public:
  Study() { 
  }
private:
  std::vector<Series> SeriesList;
};

} // end namespace gdcm

#endif //__gdcmStudy_h
