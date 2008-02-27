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
  unsigned long NumSegments;
  unsigned long Offset[15];

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
    is.read((char*)(&Header), sizeof(unsigned long)*16);
    //ByteSwap<unsigned long>::SwapRangeFromSwapCodeIntoSystem(
    //  (unsigned long*)&Header, is.GetSwapCode(), 16);
    unsigned long numSegments = Header.NumSegments;
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

bool RLECodec::Decode(DataElement const &is, DataElement &os)
{
    const SequenceOfFragments *sf = is.GetSequenceOfFragments();
    assert( sf );
  unsigned long len; // = GetBufferLength();
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
          assert( (bv.GetLength() - p) == 0 
               || (bv.GetLength() - 1 - p) == 0 );
          }
        else
          {
          // ALOKA_SSD-8-MONO2-RLE-SQ.dcm
          gdcmWarningMacro( "Bad RLE stream" );
          }
        std::string::size_type check = os.str().size();
        // If the following assert fail expect big troubles:
        assert( check == llen 
            || (check == 3*llen && GetPhotometricInterpretation() 
            == PhotometricInterpretation::PALETTE_COLOR) );
        //memcpy(buffer+pos, os.str().c_str(), check);
        pos += check;
        }
      assert( pos == len || pos == 3*len );
      return true;
}

bool RLECodec::Decode(std::istream &is, std::ostream &os)
{
  // FIXME: Do some stupid work:
  //is.Seekg( 0, std::ios::end);
  //std::streampos buf_size = is.Tellg();
  char dummy_buffer[256];
  //is.Seekg(0, std::ios::beg);
  //is.Read( dummy_buffer, buf_size);
  //SwapCode sc = is.GetSwapCode();
  //os.write(dummy_buffer, buf_size);
  //delete[] dummy_buffer;
  //long numOutBytes = 0;
  //while()
  //  {
  //  }
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
  if( GetPhotometricInterpretation() == 
    PhotometricInterpretation::PALETTE_COLOR )
    {
    //length /= 3;
    }
  else if ( GetPhotometricInterpretation() ==
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
      assert( frame.Header.Offset[i] - pos == 1 );
      is.seekg( frame.Header.Offset[i], std::ios::beg );
      }

    unsigned long numOutBytes = 0;
    char byte;
    //std::cerr << "Length: " << Length << "\n";
    //assert( (uint32_t)is.Tellg() == frame.Header.Offset[i] );
    while( numOutBytes < length )
      {
      //std::cerr << "numOutBytes: " << numOutBytes << " / " << length << "\n";
      is.read(&byte, 1);
      numberOfReadBytes++;
      //std::cerr << "Byte: " << int(byte) << "\n";
      if( byte >= 0 /*&& byte <= 127*/ )
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
    //std::cerr << "numOutBytes:" << numOutBytes << " " << length << "\n";
    //std::cerr << "DEBUG: " << numberOfReadBytes << std::endl;
    }

  //std::streampos start = is.Tellg();
  //is.Seekg( 0, std::ios::end );
  //std::streampos end = is.Tellg();
  //if( end - start != 0 )
  //  {
  //  //abort();
  //  }
  //std::streampos start = tmpos.Tellg();
  //tmpos.Seekg( 0, std::ios::end);
  //std::streampos end   = tmpos.Tellg();
  //std::cerr << "DEBUG tmpos: " << end - start << std::endl;
  //tmpos.Seekg( start, std::ios::beg );

  return ImageCodec::Decode(tmpos,os);
}

} // end namespace gdcm
