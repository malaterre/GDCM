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
#ifndef __gdcmStringFilter_h
#define __gdcmStringFilter_h

#include "gdcmDataElement.h"
#include "gdcmDicts.h"

namespace gdcm
{

class GDCM_EXPORT StringFilter
{
public:
  StringFilter();
  ~StringFilter();

  void UseDictAlways(bool use) {}

  // Allow user to pass in there own dicts
  void SetDicts(const Dicts &dicts);

  const char *ToString(const DataElement& de);

private:
  
};

} // end namespace gdcm

#endif //__gdcmStringFilter_h
