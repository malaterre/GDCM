/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageRegionReader.h"
#include "gdcmImageHelper.h"
#include "gdcmBoxRegion.h"

#include "gdcmRAWCodec.h"
#include "gdcmRLECodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEGLSCodec.h"

namespace gdcm
{

class ImageRegionReaderInternals
{
public:
  ImageRegionReaderInternals()
    {
    TheRegion = NULL;
    Modified = false;
    FileOffset = -1;
    }
  ~ImageRegionReaderInternals()
    {
    delete TheRegion;
    }
  void SetRegion(Region const & r)
    {
    delete TheRegion;
    TheRegion = r.Clone();
    assert( TheRegion );
    Modified = true;
    }
  Region *GetRegion() const
    {
    return TheRegion;
    }
  std::streampos GetFileOffset() const
    {
    return FileOffset;
    }
  void SetFileOffset( std::streampos f )
    {
    FileOffset = f;
    }
private:
  Region *TheRegion;
  bool Modified;
  std::streamoff FileOffset;
};

ImageRegionReader::ImageRegionReader()
{
  Internals = new ImageRegionReaderInternals;
}

ImageRegionReader::~ImageRegionReader()
{
  delete Internals;
}

void ImageRegionReader::SetRegion(Region const & region)
{
  Internals->SetRegion( region );
}

Region const &ImageRegionReader::GetRegion() const
{
  return *Internals->GetRegion();
}

size_t ImageRegionReader::ComputeBufferLength() const
{
  // Is this a legal extent:
  if( Internals->GetRegion() )
    {
    if( !Internals->GetRegion()->IsValid() )
      {
      gdcmDebugMacro( "Sorry not a valid extent. Giving up" );
      return 0;
      }
    }
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());
  size_t bytesPerPixel = pixelInfo.GetPixelSize();
  return this->Internals->GetRegion()->Area()*bytesPerPixel;
}

bool ImageRegionReader::ReadInformation()
{
  std::set<Tag> st;
  Tag tpixeldata(0x7fe0, 0x0010); // never read this one
  st.insert(tpixeldata);
  if (!ReadUpToTag(tpixeldata, st))
    {
    gdcmWarningMacro("Failed ReadUpToTag.");
    return false;
    }
  std::streampos fileoffset = GetStreamPtr()->tellg();

  if( fileoffset == std::streampos(-1) )
    {
    gdcmWarningMacro("Fail fileoffset.");
    return false;
    }
  assert( fileoffset != std::streampos(-1) );
  Internals->SetFileOffset( fileoffset );

  const File &file = GetFile();
  const DataSet &ds = file.GetDataSet();
  (void)ds;

  MediaStorage ms;
  ms.SetFromFile(file);
  assert( ms != MediaStorage::VLWholeSlideMicroscopyImageStorage );

  return true;
}

bool ImageRegionReader::ReadRAWIntoBuffer(char *buffer, size_t buflen)
{
  (void)buflen;
  std::vector<unsigned int> dimensions = ImageHelper::GetDimensionsValue(GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());

  const FileMetaInformation &header = GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
  RAWCodec theCodec;
  if( !theCodec.CanDecode( ts ) ) return false;
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(GetFile()));
  //theCodec.SetLUT( GetLUT() );
  theCodec.SetPixelFormat( ImageHelper::GetPixelFormatValue(GetFile()) );
  theCodec.SetNeedByteSwap( needbyteswap );
  //theCodec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
  theCodec.SetDimensions(ImageHelper::GetDimensionsValue(GetFile()));
  std::istream* theStream = GetStreamPtr();

  const BoxRegion &boundingbox = this->Internals->GetRegion()->ComputeBoundingBox();
  unsigned int xmin = boundingbox.GetXMin();
  unsigned int xmax = boundingbox.GetXMax();
  unsigned int ymin = boundingbox.GetYMin();
  unsigned int ymax = boundingbox.GetYMax();
  unsigned int zmin = boundingbox.GetZMin();
  unsigned int zmax = boundingbox.GetZMax();
  assert( xmax >= xmin );
  assert( ymax >= ymin );
  unsigned int rowsize = xmax - xmin + 1;
  unsigned int colsize = ymax - ymin + 1;
  unsigned int bytesPerPixel = pixelInfo.GetPixelSize();

  std::vector<char> buffer1;
  buffer1.resize( rowsize*bytesPerPixel );
  char *tmpBuffer1 = &buffer1[0];
  std::vector<char> buffer2;
  buffer2.resize( rowsize*bytesPerPixel );
  char *tmpBuffer2 = &buffer2[0];
  unsigned int y, z;
  std::streamoff theOffset;
  for (z = zmin; z <= zmax; ++z)
    {
    for (y = ymin; y <= ymax; ++y)
      {
      theStream->seekg(std::ios::beg);
      theOffset = (size_t)Internals->GetFileOffset() + (z*dimensions[1]*dimensions[0] + y*dimensions[0] + xmin)*bytesPerPixel;
      theStream->seekg(theOffset);
      theStream->read(tmpBuffer1, rowsize*bytesPerPixel);
      if (!theCodec.DecodeBytes(tmpBuffer1, rowsize*bytesPerPixel,
          tmpBuffer2, rowsize*bytesPerPixel))
        {
        return false;
        }
      memcpy(&(buffer[((z-zmin)*rowsize*colsize +
            (y-ymin)*rowsize)*bytesPerPixel]),
        tmpBuffer2, rowsize*bytesPerPixel);
      }
    }
  return true;
}

bool ImageRegionReader::ReadRLEIntoBuffer(char *buffer, size_t buflen)
{
  (void)buflen;
  std::vector<unsigned int> dimensions = ImageHelper::GetDimensionsValue(GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());

  const FileMetaInformation &header = GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
  RLECodec theCodec;
  if( !theCodec.CanDecode( ts ) ) return false;
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(GetFile()));
  //theCodec.SetLUT( GetLUT() );
  theCodec.SetPixelFormat( ImageHelper::GetPixelFormatValue(GetFile()) );
  theCodec.SetNeedByteSwap( needbyteswap );
  //theCodec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
  std::vector<unsigned int> d = ImageHelper::GetDimensionsValue(GetFile());
  theCodec.SetDimensions(d );
  theCodec.SetNumberOfDimensions( 2 );
  if( d[2] > 1 )
    theCodec.SetNumberOfDimensions( 3 );

  std::istream* theStream = GetStreamPtr();
  const BoxRegion &boundingbox = this->Internals->GetRegion()->ComputeBoundingBox();
  unsigned int xmin = boundingbox.GetXMin();
  unsigned int xmax = boundingbox.GetXMax();
  unsigned int ymin = boundingbox.GetYMin();
  unsigned int ymax = boundingbox.GetYMax();
  unsigned int zmin = boundingbox.GetZMin();
  unsigned int zmax = boundingbox.GetZMax();

  assert( xmax >= xmin );
  assert( ymax >= ymin );

  theCodec.DecodeExtent(
    buffer,
    xmin, xmax,
    ymin, ymax,
    zmin, zmax,
    *theStream
  );

  return true;
}

bool ImageRegionReader::ReadJPEG2000IntoBuffer(char *buffer, size_t buflen)
{
  (void)buflen;
  std::vector<unsigned int> dimensions = ImageHelper::GetDimensionsValue(GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());

  const FileMetaInformation &header = GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
  JPEG2000Codec theCodec;
  if( !theCodec.CanDecode( ts ) ) return false;
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(GetFile()));
  //theCodec.SetLUT( GetLUT() );
  theCodec.SetPixelFormat( ImageHelper::GetPixelFormatValue(GetFile()) );
  theCodec.SetNeedByteSwap( needbyteswap );
  //theCodec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
  std::vector<unsigned int> d = ImageHelper::GetDimensionsValue(GetFile());
  theCodec.SetDimensions(d );
  theCodec.SetNumberOfDimensions( 2 );
  if( d[2] > 1 )
    theCodec.SetNumberOfDimensions( 3 );

  std::istream* theStream = GetStreamPtr();
  const BoxRegion &boundingbox = this->Internals->GetRegion()->ComputeBoundingBox();
  unsigned int xmin = boundingbox.GetXMin();
  unsigned int xmax = boundingbox.GetXMax();
  unsigned int ymin = boundingbox.GetYMin();
  unsigned int ymax = boundingbox.GetYMax();
  unsigned int zmin = boundingbox.GetZMin();
  unsigned int zmax = boundingbox.GetZMax();

  assert( xmax >= xmin );
  assert( ymax >= ymin );

  theCodec.DecodeExtent(
    buffer,
    xmin, xmax,
    ymin, ymax,
    zmin, zmax,
    *theStream
  );

  return true;
}

bool ImageRegionReader::ReadJPEGIntoBuffer(char *buffer, size_t buflen)
{
  (void)buflen;
  std::vector<unsigned int> dimensions = ImageHelper::GetDimensionsValue(GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());

  const FileMetaInformation &header = GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
  JPEGCodec theCodec;
  if( !theCodec.CanDecode( ts ) ) return false;
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(GetFile()));
  //theCodec.SetLUT( GetLUT() );
  theCodec.SetPixelFormat( ImageHelper::GetPixelFormatValue(GetFile()) );
  theCodec.SetNeedByteSwap( needbyteswap );
  //theCodec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
  std::vector<unsigned int> d = ImageHelper::GetDimensionsValue(GetFile());
  theCodec.SetDimensions(d );
  theCodec.SetNumberOfDimensions( 2 );
  if( d[2] > 1 )
    theCodec.SetNumberOfDimensions( 3 );

  std::istream* theStream = GetStreamPtr();
  const BoxRegion &boundingbox = this->Internals->GetRegion()->ComputeBoundingBox();
  unsigned int xmin = boundingbox.GetXMin();
  unsigned int xmax = boundingbox.GetXMax();
  unsigned int ymin = boundingbox.GetYMin();
  unsigned int ymax = boundingbox.GetYMax();
  unsigned int zmin = boundingbox.GetZMin();
  unsigned int zmax = boundingbox.GetZMax();

  assert( xmax >= xmin );
  assert( ymax >= ymin );

  theCodec.DecodeExtent(
    buffer,
    xmin, xmax,
    ymin, ymax,
    zmin, zmax,
    *theStream
  );

  return true;
}

bool ImageRegionReader::ReadJPEGLSIntoBuffer(char *buffer, size_t buflen)
{
  (void)buflen;
  std::vector<unsigned int> dimensions = ImageHelper::GetDimensionsValue(GetFile());
  PixelFormat pixelInfo = ImageHelper::GetPixelFormatValue(GetFile());

  const FileMetaInformation &header = GetFile().GetHeader();
  const TransferSyntax &ts = header.GetDataSetTransferSyntax();

  bool needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
  JPEGLSCodec theCodec;
  if( !theCodec.CanDecode( ts ) ) return false;
  theCodec.SetPlanarConfiguration(
    ImageHelper::GetPlanarConfigurationValue(GetFile()));
  theCodec.SetPhotometricInterpretation(
    ImageHelper::GetPhotometricInterpretationValue(GetFile()));
  //theCodec.SetLUT( GetLUT() );
  theCodec.SetPixelFormat( ImageHelper::GetPixelFormatValue(GetFile()) );
  theCodec.SetNeedByteSwap( needbyteswap );
  //theCodec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
  std::vector<unsigned int> d = ImageHelper::GetDimensionsValue(GetFile());
  theCodec.SetDimensions(d );
  theCodec.SetNumberOfDimensions( 2 );
  if( d[2] > 1 )
    theCodec.SetNumberOfDimensions( 3 );

  std::istream* theStream = GetStreamPtr();
  const BoxRegion &boundingbox = this->Internals->GetRegion()->ComputeBoundingBox();
  unsigned int xmin = boundingbox.GetXMin();
  unsigned int xmax = boundingbox.GetXMax();
  unsigned int ymin = boundingbox.GetYMin();
  unsigned int ymax = boundingbox.GetYMax();
  unsigned int zmin = boundingbox.GetZMin();
  unsigned int zmax = boundingbox.GetZMax();

  assert( xmax >= xmin );
  assert( ymax >= ymin );

  theCodec.DecodeExtent(
    buffer,
    xmin, xmax,
    ymin, ymax,
    zmin, zmax,
    *theStream
  );

  return true;
}
bool ImageRegionReader::ReadIntoBuffer(char *buffer, size_t buflen)
{
  size_t thelen = ComputeBufferLength();
  if( buflen < thelen )
    {
    gdcmDebugMacro( "buffer cannot be smaller than computed buffer length" );
    return false;
    }
  assert( Internals->GetFileOffset() != std::streampos(-1) );
  gdcmDebugMacro( "Using FileOffset: " << Internals->GetFileOffset() );
  std::istream* theStream = GetStreamPtr();
  theStream->seekg( Internals->GetFileOffset() );

  bool success = false;
  if( !success ) success = ReadRAWIntoBuffer(buffer, buflen);
  if( !success ) success = ReadRLEIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEGIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEGLSIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEG2000IntoBuffer(buffer, buflen);

  return success;
}

bool ImageRegionReader::Read()
{
  return false;
}

} // end namespace gdcm
