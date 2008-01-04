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
#ifndef __gdcmJPEG12Codec_h
#define __gdcmJPEG12Codec_h

#include "gdcmJPEGCodec.h"

namespace gdcm
{
  
class JPEGInternals;
class JPEG12Codec : public JPEGCodec
{
public:
  JPEG12Codec();
  ~JPEG12Codec();

  bool Decode(std::istream &is, std::ostream &os);

private:
  JPEGInternals *Internals;
};

} // end namespace gdcm

#endif //__gdcmJPEG12Codec_h
