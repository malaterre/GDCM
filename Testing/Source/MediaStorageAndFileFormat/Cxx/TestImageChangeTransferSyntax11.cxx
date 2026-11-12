/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImage.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSmartPointer.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

// How the bits above BitsStored are filled in the input container.
enum UpperBits { SignExtended, Zero, Garbage };

// Pixel values with fewer stored bits than allocated bits must survive a
// JPEG 2000 lossless round trip whatever the bits above BitsStored hold.
// The decoder sizes its output from the stream precision, so a 32-bit
// container reads back in the smallest container holding BitsStored bits.
static int TestJ2KStoredBits(unsigned short bitsallocated, unsigned short bitsstored,
  unsigned short pixelrepresentation, UpperBits upper, unsigned short expectedallocated)
{
  const unsigned int dims[2] = { 32, 16 };
  const size_t npixels = dims[0] * dims[1];
  const size_t pixelsize = bitsallocated / 8;
  const uint32_t storedmask = bitsstored == 32 ? 0xffffffffu : ( 1u << bitsstored ) - 1;
  gdcm::PixelFormat pf;
  pf.SetSamplesPerPixel( 1 );
  pf.SetBitsAllocated( bitsallocated );
  pf.SetBitsStored( bitsstored );
  pf.SetHighBit( (unsigned short)(bitsstored - 1) );
  pf.SetPixelRepresentation( pixelrepresentation );

  gdcm::SmartPointer<gdcm::Image> image = new gdcm::Image;
  image->SetNumberOfDimensions( 2 );
  image->SetDimensions( dims );
  image->SetPixelFormat( pf );
  image->SetPhotometricInterpretation( gdcm::PhotometricInterpretation::MONOCHROME2 );
  image->SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );

  // values[i] holds the stored value sign-extended to 32 bits
  std::vector<uint32_t> values( npixels );
  std::vector<char> pixels( npixels * pixelsize );
  for( size_t i = 0; i < npixels; ++i )
    {
    uint32_t v = (uint32_t)( i * 37 ) & storedmask;
    if( pixelrepresentation && ( v >> ( bitsstored - 1 ) ) & 1u )
      {
      v |= ~storedmask;
      }
    values[i] = v;
    uint32_t raw = v;
    if( upper == Zero )
      {
      raw = v & storedmask;
      }
    else if( upper == Garbage )
      {
      raw = ( v & storedmask ) | ( 0xa5c3e18fu & ~storedmask );
      }
    for( size_t b = 0; b < pixelsize; ++b )
      {
      pixels[i * pixelsize + b] = (char)( raw >> ( 8 * b ) );
      }
    }
  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetByteValue( pixels.data(), (uint32_t)pixels.size() );
  image->SetDataElement( pixeldata );

  gdcm::ImageChangeTransferSyntax change;
  change.SetTransferSyntax( gdcm::TransferSyntax::JPEG2000Lossless );
  change.SetInput( *image );
  if( !change.Change() )
    {
    std::cerr << "Could not compress" << std::endl;
    return 1;
    }
  const gdcm::DataElement &compressed = change.GetOutput().GetDataElement();
  const gdcm::SequenceOfFragments *sqf = compressed.GetSequenceOfFragments();
  if( !sqf || sqf->GetNumberOfFragments() != 1 || !sqf->GetFragment(0).GetByteValue() )
    {
    std::cerr << "Expected a single fragment" << std::endl;
    return 1;
    }
  const gdcm::ByteValue *codestream = sqf->GetFragment(0).GetByteValue();
  std::stringstream ss;
  ss.write( codestream->GetPointer(), codestream->GetLength() );
  gdcm::JPEG2000Codec codec;
  gdcm::TransferSyntax ts;
  if( !codec.GetHeaderInfo( ss, ts ) )
    {
    std::cerr << "Could not parse the code stream" << std::endl;
    return 1;
    }
  const gdcm::PixelFormat decodedpf = codec.GetPixelFormat();
  if( decodedpf.GetBitsAllocated() != expectedallocated )
    {
    std::cerr << "BitsAllocated is " << decodedpf.GetBitsAllocated()
      << ", expected " << expectedallocated << std::endl;
    return 1;
    }

  codec.SetNumberOfDimensions( 2 );
  codec.SetDimensions( dims );
  gdcm::DataElement decoded;
  if( !codec.Decode( compressed, decoded ) || !decoded.GetByteValue() )
    {
    std::cerr << "Could not decompress" << std::endl;
    return 1;
    }
  const size_t decodedsize = expectedallocated / 8;
  const uint32_t decodedmask = decodedsize == 4 ? 0xffffffffu : ( 1u << ( 8 * decodedsize ) ) - 1;
  const gdcm::ByteValue *bv = decoded.GetByteValue();
  if( bv->GetLength() != npixels * decodedsize )
    {
    std::cerr << "Unexpected decompressed length " << bv->GetLength() << std::endl;
    return 1;
    }
  const unsigned char *p = (const unsigned char*)bv->GetPointer();
  for( size_t i = 0; i < npixels; ++i )
    {
    uint32_t v = 0;
    for( size_t b = 0; b < decodedsize; ++b )
      {
      v |= (uint32_t)p[i * decodedsize + b] << ( 8 * b );
      }
    if( v != ( values[i] & decodedmask ) )
      {
      std::cerr << "Pixel " << i << " is " << v << ", expected "
        << ( values[i] & decodedmask ) << std::endl;
      return 1;
      }
    }
  return 0;
}

int TestImageChangeTransferSyntax11(int , char *[])
{
  struct Case
    {
    unsigned short allocated;
    unsigned short stored;
    unsigned short sign;
    UpperBits upper;
    unsigned short decodedallocated;
    };
  static const Case cases[] = {
    { 8, 8, 0, Zero, 8 }, { 8, 7, 0, Zero, 8 },
    { 16, 8, 0, Zero, 16 }, { 16, 5, 0, Zero, 16 },
    { 16, 12, 0, Zero, 16 }, { 16, 16, 0, Zero, 16 },
    { 32, 8, 0, Zero, 8 }, { 32, 12, 0, Zero, 16 }, { 32, 20, 0, Zero, 32 },
    { 32, 8, 0, Garbage, 8 }, { 32, 12, 0, Garbage, 16 }, { 32, 20, 0, Garbage, 32 },
    { 32, 8, 1, SignExtended, 8 }, { 32, 12, 1, SignExtended, 16 },
    { 32, 20, 1, SignExtended, 32 },
    { 32, 8, 1, Zero, 8 }, { 32, 12, 1, Zero, 16 }, { 32, 20, 1, Zero, 32 },
    { 32, 8, 1, Garbage, 8 }, { 32, 12, 1, Garbage, 16 }, { 32, 20, 1, Garbage, 32 }
  };
  int r = 0;
  for( size_t i = 0; i < sizeof( cases ) / sizeof( *cases ); ++i )
    {
    const Case &c = cases[i];
    if( TestJ2KStoredBits( c.allocated, c.stored, c.sign, c.upper, c.decodedallocated ) )
      {
      std::cerr << "Failed for BitsAllocated=" << c.allocated
        << " BitsStored=" << c.stored << " PixelRepresentation=" << c.sign
        << " UpperBits=" << c.upper << std::endl;
      ++r;
      }
    }
  return r;
}
