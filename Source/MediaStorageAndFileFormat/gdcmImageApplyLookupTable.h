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
#ifndef __gdcmImageApplyLookupTable_h
#define __gdcmImageApplyLookupTable_h

#include "gdcmImageToImageFilter.h"

namespace gdcm
{

/**
 * \brief ImageApplyLookupTable class
 * It apply the LUT the PixelData (only PALETTE_COLOR images)
 */
class DataElement;
class GDCM_EXPORT ImageApplyLookupTable : public ImageToImageFilter
{
public:
  ImageApplyLookupTable() {}
  ~ImageApplyLookupTable() {}

  bool Apply();

protected:

private:
};

} // end namespace gdcm

#endif //__gdcmImageApplyLookupTable_h

