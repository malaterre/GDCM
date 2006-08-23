/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmJPEGcodec_h
#define __gdcmJPEGcodec_h

#include "gdcmImageCodec.h"

namespace gdcm
{

/**
 * \brief Class to do JPEG
 * \note
 */
class JPEGCodec : public ImageCodec
{
public:
  JPEGCodec();
  ~JPEGCodec();
  bool CanDecode(TS const &ts);
  bool Decode(IStream &is, OStream &os);
  void SetPixelType(PixelType const &pt);

protected:
  // Internal method called by SetPixelType
  // Instanciate the right jpeg codec (8, 12 or 16)
  void SetBitSample(int bit);

protected:
  int BitSample;

private:
  JPEGCodec *Internal;
};

} // end namespace gdcm

#endif //__gdcmJPEGcodec_h
