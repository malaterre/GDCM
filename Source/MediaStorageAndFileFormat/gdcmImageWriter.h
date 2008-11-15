/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
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
#include "gdcmImage.h"

namespace gdcm
{

class Image;
/**
 * \brief ImageWriter
 */
class GDCM_EXPORT ImageWriter : public Writer
{
public:
  ImageWriter();
  ~ImageWriter();

  /// Set/Get Image to be written
  /// It will overwrite anything Image infos found in DataSet
  /// (see parent class to see how to pass dataset)
  const Image& GetImage() const { return *PixelData; }
  Image& GetImage() { return *PixelData; } // FIXME 
  void SetImage(Image const &img);

  /// Write
  bool Write(); // Execute()

protected:
  void DoIconImage(DataSet & ds, Image const & image);

private:
  SmartPointer<Image> PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageWriter_h
