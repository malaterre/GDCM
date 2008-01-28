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

#ifndef __gdcmImageWriter_h
#define __gdcmImageWriter_h

#include "gdcmWriter.h"
#include "gdcmImageValue.h"

namespace gdcm
{
/**
 * \brief ImageWriter
 */
class Image;
class GDCM_EXPORT ImageWriter : public Writer
{
public:
  ImageWriter();
  ~ImageWriter();

  const Image& GetImage() const { return PixelData; }
  Image& GetImage() { return PixelData; } // FIXME 
  void SetImage(Image const &img);

  bool Write(); // Execute()

protected:
  bool WriteImage();
  //bool WriteACRNEMAImage();

private:
  ImageValue PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageWriter_h
