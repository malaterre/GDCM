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

#include "gdcmImage.h"
#include "gdcmSmartPointer.h"
#include "gdcmTransferSyntax.h"
#include "gdcmValue.h"

#include <vector>

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
  ImageValue():PixelData(0) {}
  ~ImageValue() {}

  bool GetBuffer(char *buffer) const;

  void SetValue(Value const &v) {
    PixelData = &v;
  }
  const Value& GetValue() const { return *PixelData; }
//  ImageValue &operator=(const ImageValue &iv)
//    {
//    PixelData = iv.PixelData;
//    return *this;
//    }
//  ImageValue(const ImageValue&_val)
//    {
//    if( this != &_val)
//      {
//      *this = _val;
//      }
//    }


protected:
  bool TryRAWCodec(char *buffer) const;
  bool TryJPEGCodec(char *buffer) const;
  bool TryJPEG2000Codec(char *buffer) const;
  bool TryRLECodec(char *buffer) const;

private:
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr PixelData; //copied from 7fe0,0010
};

} // end namespace gdcm

#endif //__gdcmImageValue_h

