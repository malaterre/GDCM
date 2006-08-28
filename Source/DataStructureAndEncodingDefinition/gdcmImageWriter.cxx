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
#include "gdcmImageWriter.h"
#include "gdcmTrace.h"

namespace gdcm
{

ImageWriter::ImageWriter()
{
}

ImageWriter::~ImageWriter()
{
}

void ImageWriter::SetImage(Image const &img)
{
  (void)img;
}

bool ImageWriter::Write()
{
  if( !Writer::Write() )
    {
    return false;
    }
  return true;
}

bool ImageWriter::WriteImage()
{
  return true;
}

bool ImageWriter::WriteACRNEMAImage()
{
  return true;
}

} // end namespace gdcm
