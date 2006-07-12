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
#include "gdcmImageIStream.h"
#include "gdcmIStream.h"

namespace gdcm
{
ImageIStream::ImageIStream():Stream(0)
{
}

ImageIStream::~ImageIStream()
{
}

bool ImageIStream::GetBuffer(char *buffer) const
{
  unsigned long len = GetBufferLength();
  if( Stream->Read(buffer, len) )
    {
    return true;
    }

  // Clearly mark buffer as invalid:
  buffer = 0;
  return false;
}

} // end namespace gdcm
