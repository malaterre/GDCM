/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageCodec.h"
#include "gdcmTS.h"
#include "gdcmOStream.h"
#include "gdcmIStream.h"
#include "gdcmByteSwap.txx"


namespace gdcm
{

class ImageInternals
{
public:
};

ImageCodec::ImageCodec()
{
  PlanarConfiguration = 0;
  PI = PhotometricInterpretation::UNKNOW;
  NeedByteSwap = false;
}

ImageCodec::~ImageCodec()
{
}

const PhotometricInterpretation &ImageCodec::GetPhotometricInterpretation() const
{
  return PI;
}

void ImageCodec::SetPhotometricInterpretation(
  PhotometricInterpretation const &pi)
{
  PI = pi;
}

bool ImageCodec::Decode(IStream &is, OStream &os)
{
  assert( PlanarConfiguration == 0 || PlanarConfiguration == 1);
  assert( PI != PhotometricInterpretation::UNKNOW );
  // FIXME: Do some stupid work:
  is.Seekg( 0, std::ios::end);
  std::streampos buf_size = is.Tellg();
  char *dummy_buffer = new char[buf_size];
  is.Seekg(0, std::ios::beg);
  is.Read( dummy_buffer, buf_size);
  SwapCode sc = is.GetSwapCode();
  //if( sc == SwapCode::BigEndian )
  if( NeedByteSwap )
    {
    //MR_GE_with_Private_Compressed_Icon_0009_1110.dcm
    assert( !(buf_size % 2) );
    ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
      dummy_buffer, SwapCode::BigEndian, buf_size/2);
    }
  // ACUSON-24-YBR_FULL-RLE.dcm declare PlanarConfiguration=1
  // but it's only pure YBR...
  if( PlanarConfiguration && PI != PhotometricInterpretation::YBR_FULL )
    {
    // US-RGB-8-epicard.dcm
    //assert( image.GetNumberOfDimensions() == 3 );
    assert( !(buf_size % 3) );
    unsigned long size = buf_size/3;
    char *copy = new char[ buf_size ];
    memmove( copy, dummy_buffer, buf_size);

    const char *r = copy;
    const char *g = copy + size;
    const char *b = copy + size + size;

    char *p = dummy_buffer;
    for (unsigned long j = 0; j < size; ++j)
      {
      *(p++) = *(r++);
      *(p++) = *(g++);
      *(p++) = *(b++);
      }
    delete[] copy;
    }
  if (PI == PhotometricInterpretation::MONOCHROME2
   || PI == PhotometricInterpretation::RGB )
    {
    }
  else if (PI == PhotometricInterpretation::MONOCHROME1)
    {
    // TODO
    }
  else if ( PI == PhotometricInterpretation::YBR_FULL )
    {
    assert( !(buf_size % 3) );
    unsigned long size = buf_size/3;
    unsigned char *copy = new unsigned char[ buf_size ];
    memmove( copy, dummy_buffer, buf_size);

    const unsigned char *a = copy + 0;
    const unsigned char *b = copy + size;
    const unsigned char *c = copy + size + size;
    int R, G, B;

    unsigned char *p = (unsigned char*)dummy_buffer;
    for (unsigned long j = 0; j < size; ++j)
      {
      R = 38142 *(*a-16) + 52298 *(*c -128);
      G = 38142 *(*a-16) - 26640 *(*c -128) - 12845 *(*b -128);
      B = 38142 *(*a-16) + 66093 *(*b -128);

      R = (R+16384)>>15;
      G = (G+16384)>>15;
      B = (B+16384)>>15;

      if (R < 0)   R = 0;
      if (G < 0)   G = 0;
      if (B < 0)   B = 0;
      if (R > 255) R = 255;
      if (G > 255) G = 255;
      if (B > 255) B = 255;

      *(p++) = (unsigned char)R;
      *(p++) = (unsigned char)G;
      *(p++) = (unsigned char)B;
      a++;
      b++;
      c++;
      }
    delete[] copy;
    }
  else
    {
    abort();
    }
  os.Write(dummy_buffer, buf_size);
  delete[] dummy_buffer;
  return true;
}

} // end namespace gdcm
