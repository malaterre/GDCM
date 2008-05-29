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

#ifndef __gdcmImageValue_h
#define __gdcmImageValue_h

#error do not use
#include "gdcmImage.h"

namespace gdcm
{

/**
 * \brief Image from a gdcm::Value type
 * \note
 * Can be ByteValue or SequenceOfFragments and nothing else AFAIK
 */
class GDCM_EXPORT ImageValue : public Image
{
public:
  ImageValue():PixelData() {}
  ~ImageValue() {}

  bool GetBuffer(char *buffer) const;

  void SetDataElement(DataElement const &de) {
    PixelData = de;
  }
  const DataElement& GetDataElement() const { return PixelData; }

  ImageValue(Image const &img):Image(img)
    {
    }


private:
};

} // end namespace gdcm

#endif //__gdcmImageValue_h

