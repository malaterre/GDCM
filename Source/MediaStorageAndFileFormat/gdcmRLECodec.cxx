/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRLECodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmTrace.h"
#include "gdcmByteSwap.txx"
#include "gdcmDataElement.h"
#include "gdcmSequenceOfFragments.h"

#include <vector>

namespace gdcm
{

// TODO ideally this code should be in utilities for ease of reuse
class RLEHeader
{
public:
  uint32_t NumSegments;
  uint32_t Offset[15];

  void Print(std::ostream &os)
    {
    os << "NumSegments:" << NumSegments << "\n";
    for(int i=0; i<15; ++i)
      {
      os << i << ":" << Offset[i] << "\n";
      }
    }
};

class RLEFrame
{
public:
  void Read(std::istream &is)
    {
    // read Header (64 bytes)
    is.read((char*)(&Header), sizeof(uint32_t)*16);
    assert( sizeof(uint32_t)*16 == 64 );
    assert( sizeof(RLEHeader) == 64 );
    //ByteSwap<unsigned long>::SwapRangeFromSwapCodeIntoSystem(
    //  (unsigned long*)&Header, is.GetSwapCode(), 16);
    uint32_t numSegments = Header.NumSegments;
    if( numSegments >= 1 )
      {
      assert( Header.Offset[0] == 64 );
      }
    // We just check that we are indeed at the proper position start+64
    //char bytes[256*256];
    }
  void Print(std::ostream &os)
    {
    Header.Print(os);
    }
//private:
  RLEHeader Header;
  std::vector<char> Bytes;
};

class RLEInternals
{
public:
  RLEFrame Frame;
  std::vector<uint32_t> SegmentLength;
};

RLECodec::RLECodec()
{
  Internals = new RLEInternals;
  Length = 0;
  BufferLength = 0;
}

RLECodec::~RLECodec()
{
  delete Internals;
}

bool RLECodec::CanDecode(TransferSyntax const &ts)
{
  return ts == TransferSyntax::RLELossless;
}

// G.3.2 The RLE decoder
// Pseudo code for the RLE decoder is shown below:
// Loop until the number of output bytes equals the uncompressed segment size
// Read the next source byte into n
// If n> =0 and n <= 127 then
// output the next n+1 bytes literally
// Elseif n <= - 1 and n >= -127 then
// output the next byte -n+1 times
// Elseif n = - 128 then
// output nothing
// Endif
// Endloop

bool RLECodec::Decode(DataElement const &in, DataElement &out)
{
  out = in;
  const SequenceOfFragments *sf = in.GetSequenceOfFragments();
  assert( sf );
  unsigned long len = GetBufferLength();
  char *buffer = new char[len];
  unsigned long pos = 0;
  // Each RLE Frame store a 2D frame. len is the 3d length
  unsigned long llen = len / sf->GetNumberOfFragments();
  // assert( GetNumberOfDimensions() == 2
  //      || GetDimension(2) == sf->GetNumberOfFragments() );
  for(unsigned int i = 0; i < sf->GetNumberOfFragments(); ++i)
    {
    std::stringstream is;
    const Fragment &frag = sf->GetFragment(i);
    const ByteValue &bv = dynamic_cast<const ByteValue&>(frag.GetValue());
    char *mybuffer = new char[bv.GetLength()];
    bv.GetBuffer(mybuffer, bv.GetLength());
    is.write(mybuffer, bv.GetLength());
    delete[] mybuffer;
    std::stringstream os;
    SetLength( llen );
    bool r = Decode(is, os);
    assert( r == true );
    std::streampos p = is.tellg();
    // http://groups.google.com/group/microsoft.public.vc.stl/browse_thread/thread/96740930d0e4e6b8
    if( !!is )
      {
      // Indeed the length of the RLE stream has been padded with a \0
      // which is discarded
      uint32_t check = bv.GetLength() - p;
      // check == 2 for gdcmDataExtra/gdcmSampleData/US_DataSet/GE_US/2929J686-breaker
      assert( check == 0 || check == 1 || check == 2 );
      }
    else
      {
      // ALOKA_SSD-8-MONO2-RLE-SQ.dcm
      gdcmWarningMacro( "Bad RLE stream" );
      }
    std::string::size_type check = os.str().size();
    // If the following assert fail expect big troubles:
    assert( check == llen );
    memcpy(buffer+pos, os.str().c_str(), check);
    pos += check;
    }
  assert( pos == len );
  out.SetByteValue( buffer, len );
  delete[] buffer;
  return true;
}

bool RLECodec::Decode(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  char dummy_buffer[256];
  std::stringstream tmpos;
  // DEBUG
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  is.seekg(0, std::ios::beg);
  // END DEBUG

  RLEFrame &frame = Internals->Frame;
  frame.Read(is);
  //frame.Print(std::cout);
  unsigned long numSegments = frame.Header.NumSegments;

  unsigned long numberOfReadBytes = 0;

  unsigned long length = Length;
  // Special case:
  if( GetPixelFormat().GetBitsAllocated() == 16 )
    {
    RequestPaddedCompositePixelCode = true;
    }
  if ( GetPhotometricInterpretation() ==
    PhotometricInterpretation::RGB )
    {
    RequestPlanarConfiguration = true;
    }
  length /= numSegments;
  for(unsigned long i = 0; i<numSegments; ++i)
    {
    numberOfReadBytes = 0;
    std::streampos pos = is.tellg();
    if ( frame.Header.Offset[i] - pos != 0 )
      {
      // ACUSON-24-YBR_FULL-RLE.dcm
      // D_CLUNIE_CT1_RLE.dcm
      // This should be at most the \0 padding
      //gdcmWarningMacro( "RLE Header says: " << frame.Header.Offset[i] <<
      //   " when it should says: " << pos << std::endl );
      uint32_t check = frame.Header.Offset[i] - pos;
      // check == 2 for gdcmDataExtra/gdcmSampleData/US_DataSet/GE_US/2929J686-breaker
      assert( check == 1 || check == 2);
      is.seekg( frame.Header.Offset[i], std::ios::beg );
      }

    unsigned long numOutBytes = 0;
    signed char byte;
    //std::cerr << "Length: " << Length << "\n";
    //assert( (uint32_t)is.Tellg() == frame.Header.Offset[i] );
    while( numOutBytes < length )
      {
      //std::cerr << "numOutBytes: " << numOutBytes << " / " << length << "\n";
      is.read((char*)&byte, 1);
      numberOfReadBytes++;
      if( byte >= 0 /*&& byte <= 127*/ ) /* 2nd is always true */
        {
        is.read( dummy_buffer, byte+1 );
        numberOfReadBytes += byte+1;
        numOutBytes += byte+ 1;
        tmpos.write( dummy_buffer, byte+1 );
        }
      else if( byte <= -1 && byte >= -127 )
        {
        char nextByte;
        is.read( &nextByte, 1);
        numberOfReadBytes += 1;
        for( int c = 0; c < -byte + 1; ++c )
          {
          dummy_buffer[c] = nextByte;
          }
        numOutBytes += -byte + 1;
        tmpos.write( dummy_buffer, -byte+1 );
        }
      else /* byte == -128 */
        {
        assert( byte == -128 );
        }
        assert( is.eof()
        || numberOfReadBytes + frame.Header.Offset[i] - is.tellg() == 0);
      }
    assert( numOutBytes == length );
    }

  return ImageCodec::Decode(tmpos,os);
}

} // end namespace gdcm
