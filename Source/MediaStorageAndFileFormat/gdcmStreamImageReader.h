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
#ifndef GDCMSTREAMIMAGEREADER_H
#define GDCMSTREAMIMAGEREADER_H

#include "gdcmPixmapReader.h"
#include "gdcmImage.h"
#include "gdcmImageReader.h"
#include <iostream>
#include "gdcmDataSet.h"

namespace gdcm
{

class MediaStorage;
/**
 * \brief StreamImageReader
 * \note its role is to convert the DICOM DataSet into a gdcm::Image
 * representation via an ITK streaming (ie, multithreaded) interface
 * Image is different from Pixmap has it has a position and a direction in
 * Space.
 *
 * \see Image
 */
class GDCM_EXPORT StreamImageReader : public ImageReader
{
  std::streamoff mFileOffset; //the fileoffset for getting header information
  DataSet mHeaderInformation; //all the non-pixel information
public:
  StreamImageReader();
  ~StreamImageReader();
  
  /// Read the DICOM image. There are two reason for failure:
  /// 1. The input filename is not DICOM
  /// 2. The input DICOM file does not contains an Image.
  /// This method has been implemented to look similar to the metaimageio in itk
  bool Read();

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadImageInformation();

  // Following methods are valid only after a call to 'Read'

  // Return the read image
  // Right now, uses the base class (ImageReader's) methods
  //const Image& GetImage() const;
  //Image& GetImage();

protected:
};

} // end namespace gdcm

#endif //GDCMSTREAMIMAGEREADER_H

