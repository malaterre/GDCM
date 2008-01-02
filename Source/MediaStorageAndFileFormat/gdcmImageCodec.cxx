/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageCodec.h"
#include "gdcmByteSwap.txx"
#include "gdcmTrace.h"


namespace gdcm
{

class ImageInternals
{
public:
};

ImageCodec::ImageCodec()
{
  PlanarConfiguration = 2;
  RequestPlanarConfiguration = false;
  RequestPaddedCompositePixelCode = false;
  PI = PhotometricInterpretation::UNKNOW;
  //LUT = LookupTable(LookupTable::UNKNOWN);
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

bool ImageCodec::DoByteSwap(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg); // reset
  //SwapCode sc = is.GetSwapCode();

  assert( !(buf_size % 2) );
#ifdef GDCM_WORDS_BIGENDIAN
  if( PT.GetBitsAllocated() == 16 )
    {
    ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
      dummy_buffer, SwapCode::LittleEndian, buf_size/2);
    }
  else
    {
    gdcmDebugMacro( "Why would I byte swap ?" );
    }
#else
  assert( PT.GetBitsAllocated() == 16 );
  ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
    dummy_buffer, SwapCode::BigEndian, buf_size/2);
#endif
  os.write(dummy_buffer, buf_size);
  return true;
}

bool ImageCodec::DoYBR(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg); // reset
  //SwapCode sc = is.GetSwapCode();

  // Code is coming from:
  // http://lestourtereaux.free.fr/papers/data/yuvrgb.pdf
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

  os.write(dummy_buffer, buf_size);
  return true;
}

bool ImageCodec::DoPlanarConfiguration(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg); // reset
  //SwapCode sc = is.GetSwapCode();

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

  os.write(dummy_buffer, buf_size);
  return true;
}

bool ImageCodec::DoSimpleCopy(std::istream &is, std::ostream &os)
{
#if 1
  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg); // reset
  os.write( dummy_buffer, buf_size);
  delete[] dummy_buffer ;
#else
  os.rdbuf( is.rdbuf() );
#endif

  return true;
}

bool ImageCodec::DoPaddedCompositePixelCode(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg); // reset
  //SwapCode sc = is.GetSwapCode();

  assert( !(buf_size % 2) );
  for(unsigned long i = 0; i < buf_size/2; ++i)
    {
#ifdef GDCM_WORDS_BIGENDIAN
    os.write( dummy_buffer+i, 1 );
    os.write( dummy_buffer+i+buf_size/2, 1 );
#else
    os.write( dummy_buffer+i+buf_size/2, 1 );
    os.write( dummy_buffer+i, 1 );
#endif
    }
  return true;
}

bool ImageCodec::DoInvertMonochrome(std::istream &is, std::ostream &os)
{
  if ( PT.GetPixelRepresentation() )
    {
    if ( PT.GetBitsAllocated() == 8 )
      {
      uint8_t c;
      while( is.read((char*)&c,1) )
        {
        c = 255 - c;
        os.write((char*)&c, 1 );
        }
      }
    else if ( PT.GetBitsAllocated() == 16 )
      {
      uint16_t smask16 = 65535;
      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        c = smask16 - c;
        os.write((char*)&c, 2);
        }
      }
    }
  else
    {
    if ( PT.GetBitsAllocated() == 8 )
      {
      uint8_t c;
      while( is.read((char*)&c,1) )
        {
        c = 255 - c;
        os.write((char*)&c, 1);
        }
      }
    else if ( PT.GetBitsAllocated() == 16 )
      {
      uint16_t mask = 1;
      for (int j=0; j<PT.GetBitsStored()-1; ++j)
        {
        mask = (mask << 1) + 1; // will be 0x0fff when BitsStored = 12
        }

      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        //assert( c <= mask );
        c = mask - c;
        //assert( c <= mask ); // FIXME does not work for D_CLUNIE_RG3_JPLY.dcm
        os.write((char*)&c, 2);
        }
      }

    }
  return true;
}

bool ImageCodec::DoPixelType(std::istream &is, std::ostream &os)
{
  assert( PT.GetBitsAllocated() > 8 );
  if( PT.GetBitsAllocated() == 16 )
    {
    // pmask : to mask the 'unused bits' (may contain overlays)
    uint16_t pmask = 0xffff;
    pmask = pmask >> ( PT.GetBitsAllocated() - PT.GetBitsStored() );

    if( PT.GetPixelRepresentation() )
      {
      // smask : to check the 'sign' when BitsStored != BitsAllocated
      uint16_t smask = 0x0001;
      smask =
        smask << ( 16 - (PT.GetBitsAllocated() - PT.GetBitsStored() + 1) );
      // nmask : to propagate sign bit on negative values
      int16_t nmask = 0x8000;  
      nmask = nmask >> ( PT.GetBitsAllocated() - PT.GetBitsStored() - 1 );

      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        c = c >> (PT.GetBitsStored() - PT.GetHighBit() - 1);
        if ( c & smask )
          {
          c = c | nmask;
          }
        else
          {
          c = c & pmask;
          }
        os.write((char*)&c, 2 );
        }
      }
    else // Pixel are unsigned
      {
      uint16_t c;
      while( is.read((char*)&c,2) )
        {
        c =
          (c >> (PT.GetBitsStored() - PT.GetHighBit() - 1)) & pmask;
        os.write((char*)&c, 2 );
        }
      }
    }
  else
    {
    abort(); // TODO
    }
  return true;
}

bool ImageCodec::Decode(std::istream &is, std::ostream &os)
{
  assert( PlanarConfiguration == 0 || PlanarConfiguration == 1);
  assert( PI != PhotometricInterpretation::UNKNOW );
  std::stringstream bs_os; // ByteSwap
  std::stringstream pcpc_os; // Padeed Composite Pixel Code
  std::stringstream pi_os; // PhotometricInterpretation
  std::stringstream pl_os; // PlanarConf
  std::istream *cur_is = &is;

  // First thing do the byte swap:
  if( NeedByteSwap )
    {
    //MR_GE_with_Private_Compressed_Icon_0009_1110.dcm
    DoByteSwap(*cur_is,bs_os);
    cur_is = &bs_os;
    }
  if ( RequestPaddedCompositePixelCode )
    {
    // D_CLUNIE_CT2_RLE.dcm
    DoPaddedCompositePixelCode(*cur_is,pcpc_os);
    cur_is = &pcpc_os;
    }

  // Second thing do palette color.
  // This way PALETTE COLOR will be applied before we do
  // Planar Configuration
  if (PI == PhotometricInterpretation::MONOCHROME2
   || PI == PhotometricInterpretation::RGB )
    {
    }
  else if (PI == PhotometricInterpretation::MONOCHROME1)
    {
    // CR-MONO1-10-chest.dcm
    DoInvertMonochrome(*cur_is, pi_os);
    cur_is = &pi_os;
    }
  else if ( PI == PhotometricInterpretation::YBR_FULL )
    {
    DoYBR(*cur_is,pi_os);
    cur_is = &pi_os;
    }
  else if ( PI == PhotometricInterpretation::PALETTE_COLOR )
    {
    assert( LUT );
    LUT->Decode(*cur_is, pi_os);
    cur_is = &pi_os;
    }
  else if ( PI == PhotometricInterpretation::YBR_FULL_422 )
    {
    // TODO
    abort();
    }
  else
    {
    abort();
    }

  if( PlanarConfiguration || RequestPlanarConfiguration )
    {
    if ( PI == PhotometricInterpretation::YBR_FULL )
      {
      // ACUSON-24-YBR_FULL-RLE.dcm declare PlanarConfiguration=1
      // but it's only pure YBR...
      gdcmWarningMacro( "Not sure what to do" );
      }
    else
      {
      DoPlanarConfiguration(*cur_is,pl_os);
      cur_is = &pl_os;
      }
    }

  // Do the pixel type (cleanup the unused bits)
  // must be the last operation (duh!)
  if ( PT.GetBitsAllocated() != PT.GetBitsStored()
    && PT.GetBitsAllocated() != 8 )
    {
    DoPixelType(*cur_is,os);
    }
  else
    {
    DoSimpleCopy(*cur_is,os);
    }

  return true;
}

} // end namespace gdcm
