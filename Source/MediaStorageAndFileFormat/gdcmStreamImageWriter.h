/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef GDCMSTREAMIMAGEWRITER_H
#define GDCMSTREAMIMAGEWRITER_H

#include "gdcmPixmapWriter.h"
#include "gdcmImage.h"
#include "gdcmWriter.h"
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
class GDCM_EXPORT StreamImageWriter
{

public:
  StreamImageWriter();
  ~StreamImageWriter();


  /// One of either SetFileName or SetStream must be called prior
  /// to any other functions.  These initialize an internal Reader class
  /// to be able to get non-pixel image information.
  void SetFileName(const char* inFileName);
  void SetStream(std::ostream& inStream);

  /// Defines an image extent for the Read function.
  /// DICOM states that an image can have no more than 2^16 pixels per edge (as of 2009)
  /// In this case, the pixel extents ignore the direction cosines entirely, and
  /// assumes that the origin of the image is at location 0,0 (regardless of the definition
  /// in space per the tags).  So, if the first 100 pixels of the first row are to be read in,
  /// this function should be called with DefinePixelExtent(0, 100, 0, 1), regardless
  /// of pixel size or orientation.
  /// 15 nov 2010: added z dimension, defaults to being 1 plane large
  void DefinePixelExtent(uint16_t inXMin, uint16_t inXMax,
    uint16_t inYMin, uint16_t inYMax, uint16_t inZMin = 0, uint16_t inZMax = 1);

  /// Read the DICOM image. There are three reasons for failure:
  /// 1. The extent is not set
  /// 2. the conversion from void* to std::ostream (internally) fails
  /// 3. the given buffer isn't large enough to accomodate the desired pixel extent.
  /// This method has been implemented to look similar to the metaimageio in itk
  /// MUST have an extent defined, or else Read will return false.
  /// If no particular extent is required, use ImageReader instead.
  bool Write(void* inWriteBuffer, const std::size_t& inBufferLength);

  /// Write the header information to disk, and a bunch of zeros for the actual pixel information
  /// Of course, if we're doing a non-compressed format, that works
  /// but if it's compressed, we have to force the ordering of chunks that are written.
  virtual bool WriteImageInformation();

  /// Set the image information to be written to disk
  /// This function will make a local copy of the header information.
  void SetImageInformation(const DataSet& inHeaderInformation);


protected:

  //contains a reader for being able to ReadUpToTag
  //however, we don't want the user to be able to call Read
  //either directly or via a parent class call, so we hide the reader in here.
  Writer mWriter;

  std::streamoff mFileOffset; //the fileoffset for getting header information
  DataSet mHeaderInformation; //all the non-pixel information

  //for thread safety, these should not be stored here, but should be used
  //for every read subregion operation.
  uint16_t mXMin, mYMin, mXMax, mYMax, mZMin, mZMax;

  /// Using the min, max, etc set by DefinePixelExtent, this will fill the given buffer
  ///  Make sure to call DefinePixelExtent and to initialize the buffer with the
  /// amount given by DefineProperBufferLength prior to calling this.
  /// reads by the RAW codec; other codecs are added once implemented
  //virtual bool ReadImageSubregionRAW(std::ostream& os);
  virtual bool WriteImageSubregionRAW(char* inWriteBuffer, const std::size_t& inBufferLength);

};


} // end namespace gdcm

#endif //GDCMSTREAMIMAGEWRITER_H