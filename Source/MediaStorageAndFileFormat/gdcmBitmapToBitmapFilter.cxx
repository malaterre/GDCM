/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmBitmapToBitmapFilter.h"

#include <limits>
#include <stdlib.h> // abort
#include <string.h> // memcpy

namespace gdcm
{

BitmapToBitmapFilter::BitmapToBitmapFilter()
{
  if(!Input) Input = new Bitmap;
  if(!Output) Output = new Bitmap;
}

void BitmapToBitmapFilter::SetInput(const Bitmap& image)
{
  Input = image;
}


} // end namespace gdcm
