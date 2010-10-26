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
}
StreamImageReader::~StreamImageReader(){
}


/// One of either SetFileName or SetStream must be called prior
/// to any other functions.
void StreamImageReader::SetFileName(const char* inFileName){
  mReader.SetFileName(inFileName);
}
void StreamImageReader::SetStream(std::istream& inStream){
  mReader.SetStream(inStream);
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
uint32_t StreamImageReader::DefineProperBufferLength() const
{
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(mReader.GetFile());
  //unsigned short samplesPerPixel = pixelInfo.GetSamplesPerPixel();
  int bytesPerPixel = pixelInfo.GetPixelSize();
  return (mYMax - mYMin)*(mXMax - mXMin)*bytesPerPixel;
}

/// Read the DICOM image. There are two reason for failure:
/// 1. The extent is not set
/// 2. The output buffer is not set
/// This method has been implemented to look similar to the metaimageio in itk
bool StreamImageReader::Read(void* inReadBuffer, const std::size_t& inBufferLength){

  //need to have some kind of extent defined.
  if (mXMin > mXMax || mYMin > mYMax)
    return false; //for now


  OneShotReadBuf osrb(inReadBuffer, inBufferLength);
  std::ostream ostr(&osrb);

  //put the codec interpretation here

  return ReadImageSubregionRAW(ostr);

}
/** Read a particular subregion, using the stored mFileOffset as the beginning of the stream.
    This class reads uncompressed data; other subclasses will reimplement this function for compression.
    Assumes that the given buffer is the size in bytes returned from DefineProperBufferLength.
    */
bool StreamImageReader::ReadImageSubregionRAW(std::ostream& os) const {
  //assumes that the file is organized in row-major format, with each row rastering across
  int y;
  std::streamoff theOffset;

  //need to get the pixel size information
  //should that come from the header?
  //most likely  that's a tag in the header
  std::vector<unsigned int> extent = ImageHelper::GetDimensionsValue(mReader.GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(mReader.GetFile());
  //unsigned short samplesPerPixel = pixelInfo.GetSamplesPerPixel();
  int bytesPerPixel = pixelInfo.GetPixelSize();
  int SubRowSize = mXMax - mXMin;
  std::istream* theStream = mReader.GetStreamPtr();//probably going to need a copy of this
  //to ensure thread safety; if the stream ptr handler gets used simultaneously by different threads,
  //that would be BAD
  //tmpBuffer is for a single raster
  char* tmpBuffer = new char[SubRowSize*bytesPerPixel];
  char* tmpBuffer2 = new char[SubRowSize*bytesPerPixel];
  try {
    for (y = mYMin; y < mYMax; ++y){
      theOffset = mFileOffset + (y*(int)extent[0] + mXMin)*bytesPerPixel; 
      theStream->seekg(theOffset);
      theStream->read(tmpBuffer, SubRowSize*bytesPerPixel);
  //now, convert that buffer.
      RAWCodec theCodec;
      if (!theCodec.DecodeBytes(tmpBuffer, SubRowSize*bytesPerPixel, 
        tmpBuffer2, SubRowSize*bytesPerPixel)){
        delete [] tmpBuffer;
        delete [] tmpBuffer2;
        return false;
      }
      //this next line may require a bit of finagling...
      std::copy(tmpBuffer2, &(tmpBuffer2[SubRowSize*bytesPerPixel]) + 1, std::ostream_iterator<char>(os));
    }
  }
  catch (std::exception & ex){
    (void)ex;
    gdcmWarningMacro( "Failed to read:" << mReader.GetFileName() << " with ex:" << ex.what() );
    delete [] tmpBuffer;
    delete [] tmpBuffer2;
    return false;
  } 
  catch (...){
    gdcmWarningMacro( "Failed to read:" << mReader.GetFileName() << " with unknown error." );
    delete [] tmpBuffer;
    delete [] tmpBuffer2;
    return false;
  }

  delete [] tmpBuffer;
  delete [] tmpBuffer2;
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
  std::istream* theStream = mReader.GetStreamPtr();
  if (theStream == NULL){
    gdcmErrorMacro("Filename was not initialized for gdcm stream image reader.");
    return false;
  }
  //make a reader object in readimageinformation
  //call read up to tag
  //then create data structures from that dataset that's been read-up-to

  try
  {
    //ok, need to read up until I know what kind of endianness i'm dealing with?
    if (!mReader.ReadUpToTag(thePixelDataTag, theSkipTags)){
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
    gdcmWarningMacro( "Failed to read:" << mReader.GetFileName() << " with ex:" << ex.what() );
  }
  catch(...)
  {
    gdcmWarningMacro( "Failed to read:" << mReader.GetFileName()  << " with unknown error" );
  }

  return true;
}


} // end namespace gdcm


