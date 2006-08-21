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
#include "gdcmFragment.h"
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
      // SIEMENS_GBS_III-16-ACR_NEMA_1.acr
      gdcmDebugMacro( "Pixel Length " << bv->GetLength() <<
        " is different from computed value " << len );
      }
    bv->GetBuffer(buffer, len);
    RAWCodec codec;
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetLUT( GetLUT() );
    codec.SetPixelType( GetPixelType() );
    codec.SetNeedByteSwap( GetNeedByteSwap() );
    StringStream is;
    //is.SetSwapCode( GetSwapCode() );
    is.Write(buffer, len);
    StringStream os;
    bool r = codec.Decode(is, os);
    std::string::size_type check = os.Str().size();
    // FIXME
    if ( GetPhotometricInterpretation() == 
      PhotometricInterpretation::PALETTE_COLOR )
      {
      assert( check == 3*len );
      }
    else
      {
      assert( check == len );
      }
    memcpy(buffer, os.Str().c_str(), check);  // FIXME
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
    unsigned long totalLen = sf->ComputeByteLength();
    std::ofstream f("/tmp/debug.jpg");
    f.write(buffer, totalLen);
    f.close();
#endif
    if( GetCompressionType() == Compression::JPEG )
      {
      JPEGCodec codec;
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      codec.SetPixelType( GetPixelType() );
      unsigned long pos = 0;
      for(unsigned int i = 0; i < sf->GetNumberOfFragments(); ++i)
        {
        StringStream is;
        const Fragment &frag = sf->GetFragment(i);
        const ByteValue &bv = dynamic_cast<const ByteValue&>(frag.GetValue());
        char *mybuffer = new char[bv.GetLength()];
        bv.GetBuffer(mybuffer, bv.GetLength());
        is.Write(mybuffer, bv.GetLength());
        delete[] mybuffer;
        StringStream os;
        bool r = codec.Decode(is, os);
        assert( r == true );
        std::streampos p = is.Tellg();
        assert( (bv.GetLength() - p) == 0 );
        std::string::size_type check = os.Str().size();
        memcpy(buffer+pos, os.Str().c_str(), check);
        pos += check;
        }
      assert( pos == len );
      return true;
      }
    else if ( GetCompressionType() == Compression::JPEG2000 )
      {
      JPEG2000Codec codec;
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      StringStream is;
      unsigned long totalLen = sf->ComputeByteLength();
      sf->GetBuffer(buffer, totalLen);
      is.Write(buffer, totalLen);
      StringStream os;
      bool r = codec.Decode(is, os);
      memcpy(buffer, os.Str().c_str(), len);
      return r;
      }
    else if ( GetCompressionType() == Compression::RLE )
      {
      assert( sf->GetNumberOfFragments() == 1 );
      RLECodec codec;
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      codec.SetPixelType( GetPixelType() );
      codec.SetLUT( GetLUT() );
      unsigned long pos = 0;
      for(unsigned int i = 0; i < sf->GetNumberOfFragments(); ++i)
        {
        StringStream is;
        const Fragment &frag = sf->GetFragment(i);
        const ByteValue &bv = dynamic_cast<const ByteValue&>(frag.GetValue());
        char *mybuffer = new char[bv.GetLength()];
        bv.GetBuffer(mybuffer, bv.GetLength());
        is.Write(mybuffer, bv.GetLength());
        delete[] mybuffer;
        StringStream os;
        codec.SetLength( len );
        bool r = codec.Decode(is, os);
        assert( r == true );
        std::streampos p = is.Tellg();
        //assert( (bv.GetLength() - p) == 0 );
        std::string::size_type check = os.Str().size();
        // If the following assert fail expect big troubles:
        if ( GetPhotometricInterpretation() == 
          PhotometricInterpretation::PALETTE_COLOR )
          {
          assert( check == 3*len );
          }
        else
          {
          assert( check == len );
          }
        memcpy(buffer+pos, os.Str().c_str(), check);
        pos += check;
        }
      //unsigned long rle_len = sf->ComputeByteLength();
      //codec.SetLength( len );
      //sf->GetBuffer(buffer, rle_len);
      //is.Write(buffer, rle_len);
      //assert( pos == len );
      return true;
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

