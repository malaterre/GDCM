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
#include "gdcmImageValue.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmRAWCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmRLECodec.h"
#include "gdcmStringStream.h"

namespace gdcm
{

bool ImageValue::GetBuffer(char *buffer) const
{
  assert( GetCompressionType() != Compression::UNKNOWN );
  unsigned long len = GetBufferLength();
  Value *p = PixelData;
  const ByteValue *bv = dynamic_cast<ByteValue*>(p);
  if( bv )
    {
    if( len != bv->GetLength() )
      {
      gdcmWarningMacro( "Pixel Length " << bv->GetLength() <<
        " is different from computed value " << len );
      }
    bv->GetBuffer(buffer, len);
    RAWCodec codec;
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    StringStream is;
    is.SetSwapCode( GetSwapCode() );
    is.Write(buffer, len);
    StringStream os;
    bool r = codec.Decode(is, os);
    memcpy(buffer, os.Str().c_str(), len);
    return r;
    }
  else
    {
    // Fragments...
    const SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(p);
    assert( sf );
//#define MDEBUG
#ifdef MDEBUG
    sf->GetBuffer(buffer, len);
    unsigned long totalLen = sf->ComputeLength();
    std::ofstream f("/tmp/debug.jpg");
    f.write(buffer, totalLen);
    f.close();
#endif
    if( GetCompressionType() == Compression::JPEG )
      {
      JPEGCodec codec;
      codec.SetBitSample( GetPixelType().GetBitsAllocated() );
      unsigned long pos = 0;
      for(unsigned int i = 0; i < sf->GetNumberOfFragments(); ++i)
        {
        StringStream is;
        unsigned long flen;
        char mybuffer[90000];
        sf->GetFragBuffer(i, mybuffer, flen);
        assert( flen < 90000 );
        is.Write(mybuffer, flen);
        StringStream os;
        bool r = codec.Decode(is, os);
        //assert( r == true );
        std::streampos p = is.Tellg();
        //assert( (flen - p) == 0 );
        std::string::size_type check = os.Str().size();
        memcpy(buffer+pos, os.Str().c_str(), os.Str().size());
        pos += check;
        }
      assert( pos == len );
      return true;
      }
    else if ( GetCompressionType() == Compression::JPEG2000 )
      {
      JPEG2000Codec codec;
      StringStream is;
      is.Write(buffer, len);
      StringStream os;
      bool r = codec.Decode(is, os);
      memcpy(buffer, os.Str().c_str(), len);
      return r;
      }
    else if ( GetCompressionType() == Compression::RLE )
      {
      RLECodec codec;
      unsigned long rle_len = sf->ComputeLength();
      codec.SetLength( rle_len );
      StringStream is;
      is.Write(buffer, rle_len);
      StringStream os;
      bool r = codec.Decode(is, os);
      memcpy(buffer, os.Str().c_str(), len);
      return r;
      }
    else
      {
      abort();
      }
    }

  buffer = 0;
  return false;
}

} // end namespace gdcm

