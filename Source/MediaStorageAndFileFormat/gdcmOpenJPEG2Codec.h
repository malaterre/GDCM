/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMOPENJPEG2CODEC_H
#define GDCMOPENJPEG2CODEC_H

#include "gdcmImageCodec.h"

namespace gdcm
{
  
class OpenJPEG2Internals;
/**
 * \brief
 */
class GDCM_EXPORT OpenJPEG2Codec : public ImageCodec
{
  friend class Bitmap;
public:
  OpenJPEG2Codec();
  ~OpenJPEG2Codec();

private:
  OpenJPEG2Internals *Internals;
};

} // end namespace gdcm

#endif //GDCMJPEG2000CODEC_H
