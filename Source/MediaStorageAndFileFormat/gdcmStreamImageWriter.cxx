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



#include "gdcmStreamImageWriter.h"
#include "gdcmTag.h"
#include "gdcmMediaStorage.h"
#include <algorithm>
#include "gdcmImageHelper.h"
#include "gdcmRAWCodec.h"

namespace gdcm
{

StreamImageWriter::StreamImageWriter(){
  //set these values to be the opposite ends of possible,
  //so that if the extent is not defined, read can fail properly.
  mXMin = mYMin = mZMin = std::numeric_limits<uint16_t>::max();
  mXMax = mYMax = mZMax = std::numeric_limits<uint16_t>::min();
}
StreamImageWriter::~StreamImageWriter(){
}


/// One of either SetFileName or SetStream must be called prior
/// to any other functions.
void StreamImageWriter::SetFileName(const char* inFileName){
  mWriter.SetFileName(inFileName);
}
void StreamImageWriter::SetStream(std::ostream& inStream){
  mWriter.SetStream(inStream);
}


/// Defines an image extent for the Read function.
/// DICOM states that an image can have no more than 2^16 pixels per edge (as of 2009)
/// In this case, the pixel extents ignore the direction cosines entirely, and
/// assumes that the origin of the image is at location 0,0 (regardless of the definition
/// in space per the tags).  So, if the first 100 pixels of the first row are to be read in,
/// this function should be called with DefinePixelExtent(0, 100, 0, 1), regardless
/// of pixel size or orientation.
void StreamImageWriter::DefinePixelExtent(uint16_t inXMin, uint16_t inXMax,
                                          uint16_t inYMin, uint16_t inYMax,
                                          uint16_t inZMin, uint16_t inZMax){
  mXMin = inXMin;
  mYMin = inYMin;
  mXMax = inXMax;
  mYMax = inYMax;
  mZMin = inZMin;
  mZMax = inZMax;
}

/// Read the DICOM image. There are two reason for failure:
/// 1. The extent is not set
/// 2. The output buffer is not set
/// This method has been implemented to look similar to the metaimageio in itk
bool StreamImageWriter::Write(void* inReadBuffer, const std::size_t& inBufferLength){

  //need to have some kind of extent defined.
  if (mXMin > mXMax || mYMin > mYMax || mZMin > mZMax)
    return false; //for now


//  OneShotReadBuf osrb(inReadBuffer, inBufferLength);
//  std::ostream ostr(&osrb);

  //put the codec interpretation here

//  return ReadImageSubregionRAW(ostr);
  //just do memcpys instead of doing this stream shenanigans
  return WriteImageSubregionRAW((char*)inReadBuffer, inBufferLength);

}
/** Read a particular subregion, using the stored mFileOffset as the beginning of the stream.
    This class reads uncompressed data; other subclasses will reimplement this function for compression.
    Assumes that the given buffer is the size in bytes returned from DefineProperBufferLength.
    */
bool StreamImageWriter::WriteImageSubregionRAW(char* inWriteBuffer, const std::size_t& inBufferLength) {
  //assumes that the file is organized in row-major format, with each row rastering across
  assert( mFileOffset != -1 );
  int y, z;
  std::streamoff theOffset;

  //need to get the pixel size information
  //should that come from the header?
  //most likely  that's a tag in the header
  std::vector<unsigned int> extent = ImageHelper::GetDimensionsValue(mWriter.GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(mWriter.GetFile());
  //unsigned short samplesPerPixel = pixelInfo.GetSamplesPerPixel();
  int bytesPerPixel = pixelInfo.GetPixelSize();
  int SubRowSize = mXMax - mXMin;
  int SubColSize = mYMax - mYMin;

  //set up the codec prior to resetting the file, just in case that affects the way that
  //files are handled by the ImageHelper

  const FileMetaInformation &header = mWriter.GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();
  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE);

  RAWCodec theCodec;
  if( !theCodec.CanDecode(ts) )
    {
    gdcmDebugMacro( "Only RAW for now" );
    return false;
    }

  theCodec.SetNeedByteSwap( needbyteswap );
  theCodec.SetDimensions(ImageHelper::GetDimensionsValue(mWriter.GetFile()));
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(mWriter.GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(mWriter.GetFile()));
  //how do I handle byte swapping here?  where is it set?

  //have to reset the stream to the proper position
  //first, reopen the stream,then the loop should set the right position
  mWriter.SetFileName(mWriter.GetFileName().c_str());
  std::ostream* theStream = mWriter.GetStreamPtr();//probably going to need a copy of this
  //to ensure thread safety; if the stream ptr handler gets used simultaneously by different threads,
  //that would be BAD
  //tmpBuffer is for a single raster
  char* tmpBuffer = new char[SubRowSize*bytesPerPixel];
  char* tmpBuffer2 = new char[SubRowSize*bytesPerPixel];
  try {
    for (z = mZMin; z < mZMax; ++z){
      for (y = mYMin; y < mYMax; ++y){
        //this next line may require a bit of finagling...
        //std::copy(tmpBuffer2, &(tmpBuffer2[SubRowSize*bytesPerPixel]), std::ostream_iterator<char>(os));
        //make sure to have a test that will test different x, y, and z mins and maxes
        memcpy(tmpBuffer, &(inWriteBuffer[((z-mZMin)*SubRowSize*SubColSize +
          (y-mYMin)*SubRowSize)// + mXMin)//shouldn't need mXMin
          *bytesPerPixel]), SubRowSize*bytesPerPixel);


        if (!theCodec.DecodeBytes(tmpBuffer, SubRowSize*bytesPerPixel,
          tmpBuffer2, SubRowSize*bytesPerPixel)){
          delete [] tmpBuffer;
          delete [] tmpBuffer2;
          return false;
        }
        theStream->seekp(std::ios::beg);
        theOffset = mFileOffset + (z * (int)(extent[1]*extent[0]) + y*(int)extent[0] + mXMin)*bytesPerPixel;
        theStream->seekp(theOffset);
        theStream->write(tmpBuffer2, SubRowSize*bytesPerPixel);
      }
    }
  }
  catch (std::exception & ex){
    (void)ex;
    gdcmWarningMacro( "Failed to write:" << mReader.GetFileName() << " with ex:" << ex.what() );
    delete [] tmpBuffer;
    delete [] tmpBuffer2;
    return false;
  }
  catch (...){
    gdcmWarningMacro( "Failed to write:" << mReader.GetFileName() << " with unknown error." );
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
bool StreamImageWriter::WriteImageInformation(){

  //ok, the writer has a file in it, and so we place the dataset that we're given into
  //the file
  mWriter.GetFile().SetDataSet(mNonPixelInformation);
  try
  {
    mWriter.Write();//should write everything BUT the image tag.  right?
    //this is where to start writing zeros for the image.
    //BUT! do we know here if it's compressed for writing out?  If so, shouldn't that require forcing
    //the datasets to be presented sequentially?
    //at this point, we should be at the end of the dataset, and the pointer should be set to eof
    //which is good, because otherwise, we have a problem (write is inherited, and I can't easily
    //do the trick where I return the stream location
    mWriter.SetFileName(mWriter.GetFileName().c_str());
    mFileOffset = mWriter.GetStreamPtr()->tellp();
  }
  catch(std::exception & ex)
  {
    (void)ex;
    gdcmWarningMacro( "Failed to write:" << mReader.GetFileName() << " with ex:" << ex.what() );
  }
  catch(...)
  {
    gdcmWarningMacro( "Failed to write:" << mReader.GetFileName()  << " with unknown error" );
  }

  // eg. ELSCINT1_PMSCT_RLE1.dcm
  if( mFileOffset == -1 ) return false;

  // postcondition
  assert( mFileOffset != -1 );
  return true;
}

  /// Set the image information to be written to disk that is everything but
  /// the pixel information.  Copies the data into a new dataset, except for the pixel element
///This way, writing the image information will just write everything else.
void StreamImageWriter::SetImageNonPixelInformation(const DataSet& inNonPixelInformation){
  mNonPixelInformation.Clear();
  gdcm::DataSet::ConstIterator itor;
  gdcm::Tag thePixelDataTag(0x7fe0, 0x0010);
  for (itor = inNonPixelInformation.Begin(); itor != inNonPixelInformation.End(); ++itor){
    if (itor->GetTag() != thePixelDataTag){
      mNonPixelInformation.Insert(*itor);
    }
  }
}

} // end namespace gdcm