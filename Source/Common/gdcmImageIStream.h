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
#ifndef __gdcmImageIStream_h
#define __gdcmImageIStream_h

#include "gdcmImage.h"

namespace gdcm
{

/**
 * \brief ImageIStream
 * \note
 * Image constructed from a IStream
 */
class IStream;
class GDCM_EXPORT ImageIStream : public Image
{
public:
  ImageIStream();
  ~ImageIStream();

  // Acces the raw data
  bool GetBuffer(char *buffer) const;

private:
  IStream *Stream;
};

} // end namespace gdcm

#endif //__gdcmImageIStream_h

