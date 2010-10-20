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
 * Currently, this class is threadsafe in that it can read a single extent 
 * in a single thread.  Multiple versions can be used for multiple extents/threads.
 *
 * \see Image
 */
class GDCM_EXPORT StreamImageReader : public ImageReader
{

public:
  StreamImageReader();
  ~StreamImageReader();
  
  /// Defines an image extent for the Read function.
  /// DICOM states that an image can have no more than 2^16 pixels per edge (as of 2009)
  /// In this case, the pixel extents ignore the direction cosines entirely, and 
  /// assumes that the origin of the image is at location 0,0 (regardless of the definition
  /// in space per the tags).  So, if the first 100 pixels of the first row are to be read in,
  /// this function should be called with DefinePixelExtent(0, 100, 0, 1), regardless
  /// of pixel size or orientation.
  void DefinePixelExtent(uint16_t inXMin, uint16_t inXMax, uint16_t inYMin, uint16_t inYMax);

  /// Paying attention to the pixel format and so forth, define the proper buffer length for the user.
  /// The return amount is in bytes.  Call this function to determine the size of the char* buffer
  /// that will need to be passed in to ReadImageSubregion().  
  uint32_t DefineProperBufferLength() const;

  /// Sets the buffer that should be the size returned by DefineProperBufferLength.
  /// THIS CLASS IS NOT RESPONSIBLE FOR MANAGING THIS MEMORY.
  /// It is merely a place for read image information to be placed; it is the 
  /// responsibility of the caller to handle this memory.
  void SetBuffer(char* inBuffer) {mReadBuffer = inBuffer;}
  char* GetBuffer() const { return mReadBuffer; }

  /// Read the DICOM image. There are two reason for failure:
  /// 1. The input filename is not DICOM
  /// 2. The input DICOM file does not contains an Image.
  /// This method has been implemented to look similar to the metaimageio in itk
  /// MUST have an extent defined, or else Read will return false.
  /// If no particular extent is required, use ImageReader instead.
  bool Read();

  /** Set the spacing and dimension information for the set filename. */
  virtual void ReadImageInformation();

  // Following methods are valid only after a call to 'Read'

  // Return the read image
  // Right now, uses the base class (ImageReader's) methods
  //const Image& GetImage() const;
  //Image& GetImage();

protected:

  std::streamoff mFileOffset; //the fileoffset for getting header information
  DataSet mHeaderInformation; //all the non-pixel information

  //for thread safety, these should not be stored here, but should be used  
  //for every read subregion operation.
  uint16_t mXMin, mYMin, mXMax, mYMax;

  //the buffer set by SetBuffer.  THIS CLASS DOES NOT MANAGE THIS MEMORY.
  char* mReadBuffer;

  /// Using the min, max, etc set by DefinePixelExtent, this will fill the given buffer
  ///  Make sure to call DefinePixelExtent and to initialize the buffer with the
  /// amount given by DefineProperBufferLength prior to calling this.
  virtual bool ReadImageSubregion();

};

} // end namespace gdcm

#endif //GDCMSTREAMIMAGEREADER_H

