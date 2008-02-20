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

namespace gdcm
{

bool ImageValue::TryRAWCodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();
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
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedByteSwap( GetNeedByteSwap() );
    std::stringstream is;
    is.write(buffer, len);
    std::stringstream os;
    bool r = codec.Decode(is, os);
    std::string::size_type check = os.str().size();
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
    memcpy(buffer, os.str().c_str(), check);  // FIXME
    return r;
    }
  return false;
}

bool ImageValue::TryJPEGCodec(char *buffer) const
    {
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();
  Value *p = PixelData;

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
    JPEGCodec codec;
    if( codec.CanDecode( ts ) )
      {
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      codec.SetPixelFormat( GetPixelFormat() );
      unsigned long pos = 0;
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
        bool r = codec.Decode(is, os);
        assert( r == true );
        std::streampos p = is.tellg();
        assert( (bv.GetLength() - p) == 0 );
        std::string::size_type check = os.str().size();
        memcpy(buffer+pos, os.str().c_str(), check);
        pos += check;
        }
      assert( pos == len );
      return true;
      }
return false;
}
   
bool ImageValue::TryJPEG2000Codec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();
  Value *p = PixelData;
    const SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(p);

      JPEG2000Codec codec;
    if( codec.CanDecode( ts ) )
      {
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      std::stringstream is;
      unsigned long totalLen = sf->ComputeByteLength();
      sf->GetBuffer(buffer, totalLen);
      is.write(buffer, totalLen);
      std::stringstream os;
      bool r = codec.Decode(is, os);
      memcpy(buffer, os.str().c_str(), len);
      return r;
      }
  return false;
}

bool ImageValue::TryRLECodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();
  Value *p = PixelData;
    const SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(p);

      RLECodec codec;
    if( codec.CanDecode( ts ) )
      {
      //assert( sf->GetNumberOfFragments() == 1 );
      //assert( sf->GetNumberOfFragments() == GetDimensions(2) );
      codec.SetPlanarConfiguration( GetPlanarConfiguration() );
      codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
      codec.SetPixelFormat( GetPixelFormat() );
      codec.SetLUT( GetLUT() );
      unsigned long pos = 0;
      // Each RLE Frame store a 2D frame. len is the 3d length
      unsigned long llen = len / sf->GetNumberOfFragments();
      assert( GetNumberOfDimensions() == 2
           || GetDimension(2) == sf->GetNumberOfFragments() );
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
        codec.SetLength( llen );
        bool r = codec.Decode(is, os);
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
        memcpy(buffer+pos, os.str().c_str(), check);
        pos += check;
        }
      assert( pos == len || pos == 3*len );
      return true;
      }
  return false;
}

bool ImageValue::GetBuffer(char *buffer) const
{
  bool success = false;
  if( !success ) success = TryRAWCodec(buffer);
  if( !success ) success = TryJPEGCodec(buffer);
  if( !success ) success = TryJPEG2000Codec(buffer);
  if( !success ) success = TryRLECodec(buffer);
  if( !success )
    {
    buffer = 0;
    abort();
    }

  return success;
}

} // end namespace gdcm

