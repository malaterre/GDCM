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

  const ByteValue *bv = PixelData.GetByteValue();
  if( bv )
    {
    RAWCodec codec;
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetLUT( GetLUT() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedByteSwap( GetNeedByteSwap() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    if( len != bv->GetLength() )
      {
      // SIEMENS_GBS_III-16-ACR_NEMA_1.acr
      gdcmDebugMacro( "Pixel Length " << bv->GetLength() <<
        " is different from computed value " << len );
      ((ByteValue*)outbv)->SetLength( len );
      }
    unsigned long check = outbv->GetLength();  // FIXME
    assert( check == len );
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return r;
    }
  return false;
}

bool ImageValue::TryJPEGCodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanDecode( ts ) )
    {
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    // DermaColorLossLess.dcm has a len of 63531, but DICOM will give us: 63532 ...
    memcpy(buffer, outbv->GetPointer(), len /*outbv->GetLength()*/ );  // FIXME

    return true;
    }
  return false;
}
   
bool ImageValue::TryJPEG2000Codec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec codec;
  if( codec.CanDecode( ts ) )
    {
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return r;
    }
  return false;
}

bool ImageValue::TryRLECodec(char *buffer) const
{
  const TransferSyntax &ts = GetTransferSyntax();

  RLECodec codec;
  if( codec.CanDecode( ts ) )
    {
    //assert( sf->GetNumberOfFragments() == 1 );
    //assert( sf->GetNumberOfFragments() == GetDimensions(2) );
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetLUT( GetLUT() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);

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
    throw Exception( "Not codec found for this image");
    }

  return success;
}

} // end namespace gdcm

