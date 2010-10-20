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


#include "gdcmStreamImageReader.h"
#include "gdcmImage.h"
#include "gdcmMediaStorage.h"
#include <algorithm>
#include "gdcmImageHelper.h"
#include "gdcmRAWCodec.h"

namespace gdcm
{

StreamImageReader::StreamImageReader(){
  //set these values to be the opposite ends of possible,
  //so that if the extent is not defined, read can fail properly.
  mXMin = mYMin = std::numeric_limits<uint16_t>::max();
  mXMax = mYMax = std::numeric_limits<uint16_t>::min();
  mReadBuffer = NULL;
}
StreamImageReader::~StreamImageReader(){
  //DO NOT DELETE mReadBuffer
  //memory allocated in a library can be notoriously hard to clean up
  //from the main application, especially if that memory is then used
  //by the main app directly.  Let the main app handle.
}


/// Defines an image extent for the Read function.
/// DICOM states that an image can have no more than 2^16 pixels per edge (as of 2009)
/// In this case, the pixel extents ignore the direction cosines entirely, and 
/// assumes that the origin of the image is at location 0,0 (regardless of the definition
/// in space per the tags).  So, if the first 100 pixels of the first row are to be read in,
/// this function should be called with DefinePixelExtent(0, 100, 0, 1), regardless
/// of pixel size or orientation.
void StreamImageReader::DefinePixelExtent(uint16_t inXMin, uint16_t inXMax, uint16_t inYMin, uint16_t inYMax){
  mXMin = inXMin;
  mYMin = inYMin;
  mXMax = inXMax;
  mYMax = inYMax;
}
/// Paying attention to the pixel format and so forth, define the proper buffer length for the user.
/// The return amount is in bytes.
uint32_t StreamImageReader::DefineProperBufferLength() const{
  
  PixelFormat pixelInfo = ImageHelper::GetImagePixelInformation(*F);
  unsigned short samplesPerPixel = pixelInfo.GetSamplesPerPixel();
  int bytesPerPixel = pixelInfo.GetPixelSize();
  return (mYMax - mYMin)*(mXMax - mXMin)*samplesPerPixel*bytesPerPixel;
}

/// Read the DICOM image. There are two reason for failure:
/// 1. The extent is not set
/// 2. The output buffer is not set
/// This method has been implemented to look similar to the metaimageio in itk
bool StreamImageReader::Read(){

  //need to have some kind of extent defined.
  if (mXMin > mXMax || mYMin > mYMax)
    return false; //for now

  if (!mReadBuffer) return false; //not properly initialized the buffer

  return ReadImageSubregion();

}
/** Read a particular subregion, using the stored mFileOffset as the beginning of the stream.
    This class reads uncompressed data; other subclasses will reimplement this function for compression.
    Assumes that the given buffer is the size in bytes returned from DefineProperBufferLength.
    */
bool StreamImageReader::ReadImageSubregion(){
  //assumes that the file is organized in row-major format, with each row rastering across
  int y;
  std::streamoff theOffset;
  if (!mReadBuffer) return false;

  //need to get the pixel size information
  //should that come from the header?
  //most likely  that's a tag in the header
  std::vector<double> extent = ImageHelper::GetPixelExtent(*F);
  PixelFormat pixelInfo = ImageHelper::GetImagePixelInformation(*F);
  unsigned short samplesPerPixel = pixelInfo.GetSamplesPerPixel();
  int bytesPerPixel = pixelInfo.GetPixelSize();
  int SubRowSize = mXMax - mXMin;
  std::istream* theStream = GetStreamPtr();//probably going to need a copy of this
  //to ensure thread safety; if the stream ptr handler gets used simultaneously by different threads,
  //that would be BAD
  uint32_t theProperBufferLength = DefineProperBufferLength();
  char* tmpBuffer = new char[theProperBufferLength];
  try {
    for (y = mYMin; y < mYMax; ++y){
      theOffset = mFileOffset + (y*(int)extent[0] + mXMin)*samplesPerPixel*bytesPerPixel; 
      theStream->seekg(theOffset);
      theStream->read(&(mReadBuffer[((y-mYMin)*SubRowSize)*samplesPerPixel*bytesPerPixel]), 
        SubRowSize*samplesPerPixel*bytesPerPixel);
    }
  }
  catch (std::exception & ex){
    (void)ex;
    gdcmWarningMacro( "Failed to read:" << GetFileName() << " with ex:" << ex.what() );
    delete [] tmpBuffer;
    return false;
  } 
  catch (...){
    gdcmWarningMacro( "Failed to read:" << GetFileName() << " with unknown error." );
    delete [] tmpBuffer;
    return false;
  }
  //now, convert that buffer.
  RAWCodec theCodec;
  if (!theCodec.DecodeBytes(tmpBuffer, theProperBufferLength, 
    mReadBuffer, theProperBufferLength)){
    delete [] tmpBuffer;
    return false;
  }

  delete [] tmpBuffer;
  return true;
}

/// Set the spacing and dimension information for the set filename.
/// returns false if the file is not initialized or not an image, 
/// with the pixel 0x7fe0, 0x0010 tag.
bool StreamImageReader::ReadImageInformation(){
  //read up to the point in the stream where the pixel information tag is
  //store that location and keep the rest of the data as the header information dataset
  std::set<Tag> theSkipTags;
  Tag thePixelDataTag(0x7fe0, 0x0010);
  bool read = false;
  std::istream* theStream = GetStreamPtr();
  if (theStream == NULL){
    gdcmErrorMacro("Filename was not initialized for gdcm stream image reader.");
    return false;
  }
  try
  {
    //ok, need to read up until I know what kind of endianness i'm dealing with?
    if (!ReadUpToTag(thePixelDataTag, theSkipTags)){
      gdcmWarningMacro("Failed to read tags in the gdcm stream image reader.");
      return false;
    }
    //get the file stream position
    mFileOffset = theStream->tellg();//part of the reader functionality, the really
    //super class of this reader
    //when reading past here, can use file pointers and the like
  }
  catch(std::exception & ex)
  {
    (void)ex;
    gdcmWarningMacro( "Failed to read:" << GetFileName() << " with ex:" << ex.what() );
  }
  catch(...)
  {
    gdcmWarningMacro( "Failed to read:" << GetFileName()  << " with unknown error" );
  }

 
}


} // end namespace gdcm


