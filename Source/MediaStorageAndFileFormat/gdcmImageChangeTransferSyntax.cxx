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
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"
#include "gdcmRAWCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEGLSCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmRLECodec.h"

namespace gdcm
{

bool ImageChangeTransferSyntax::TryRAWCodec(const DataElement &pixelde)
{
  unsigned long len = Input->GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  RAWCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(Input->GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = Output->GetDataElement();
    de.SetValue( out.GetValue() );
    if( !r )
      {
      return false;
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryRLECodec(const DataElement &pixelde)
{
  unsigned long len = Input->GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  RLECodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(Input->GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = Output->GetDataElement();
    de.SetValue( out.GetValue() );
    if( !r )
      {
      return false;
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEGCodec(const DataElement &pixelde)
{
  unsigned long len = Input->GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    // FIXME: GDCM always apply the planar configuration to 0...
    if( Input->GetPlanarConfiguration() )
      {
      // Fow now simply return an error
      return false;
      }
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(Input->GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = Output->GetDataElement();
    de.SetValue( out.GetValue() );
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
    if( !r )
      {
      return false;
      }
    // When compressing with JPEG I think planar should always be:
    //Output->SetPlanarConfiguration(0);
    // FIXME ! This should be done all the time for all codec:
    // Did PI change or not ?
    if ( Output->GetPhotometricInterpretation() != codec.GetPhotometricInterpretation() )
      {
      // HACK
      //gdcm::Image *i = (gdcm::Image*)this;
      //i->SetPhotometricInterpretation( codec.GetPhotometricInterpretation() );
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEGLSCodec(const DataElement &pixelde)
{
  unsigned long len = Input->GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGLSCodec codec;
  if( codec.CanCode( ts ) )
    {
    //codec.SetDimensions( Input->GetDimensions() );
    //codec.SetPixelFormat( Input->GetPixelFormat() );
    //codec.SetNumberOfDimensions( Input->GetNumberOfDimensions() );
    //codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    //codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    //codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    //DataElement out;
    ////bool r = codec.Code(Input->GetDataElement(), out);
    //bool r = codec.Code(pixelde, out);

    //DataElement &de = Output->GetDataElement();
    //de.SetValue( out.GetValue() );
    //assert( r );
    //return r;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEG2000Codec(const DataElement &pixelde)
{
  unsigned long len = Input->GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNumberOfDimensions( Input->GetNumberOfDimensions() );
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(Input->GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = Output->GetDataElement();
    de.SetValue( out.GetValue() );
    assert( r );
    return r;
    }
  return false;
}

bool ImageChangeTransferSyntax::Change()
{
  Output = Input;

  // Fast path
  if( Input->GetTransferSyntax() == TS && !Force ) return true;

  // FIXME
  // For now only support raw input, otherwise we would need to first decompress them
  if( Input->GetTransferSyntax() != TransferSyntax::ImplicitVRLittleEndian 
    && Input->GetTransferSyntax() != TransferSyntax::ExplicitVRLittleEndian
    && Input->GetTransferSyntax() != TransferSyntax::ExplicitVRBigEndian
    || Force )
    {
    // In memory decompression:
    gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
    gdcm::ByteValue *bv = new gdcm::ByteValue();
    unsigned long len = Input->GetBufferLength();
    bv->SetLength( len );
    bool b = Input->GetBuffer( (char*)bv->GetPointer() );
    if( !b )
      {
      return false;
      }
    pixeldata.SetValue( *bv );

    bool success = false;
    if( !success ) success = TryRAWCodec(pixeldata);
    if( !success ) success = TryJPEGCodec(pixeldata);
    if( !success ) success = TryJPEG2000Codec(pixeldata);
    if( !success ) success = TryRLECodec(pixeldata);
    Output->SetTransferSyntax( TS );
    if( !success )
      {
      //abort();
      return false;
      }

    assert( Output->GetTransferSyntax() == TS );
    return success;
    }

  // too bad we actually have to do some work...
  bool success = false;
  if( !success ) success = TryRAWCodec(Input->GetDataElement());
  if( !success ) success = TryJPEGCodec(Input->GetDataElement());
  if( !success ) success = TryJPEG2000Codec(Input->GetDataElement());
  if( !success ) success = TryJPEGLSCodec(Input->GetDataElement());
  if( !success ) success = TryRLECodec(Input->GetDataElement());
  Output->SetTransferSyntax( TS );
  if( !success )
    {
    //abort();
    return false;
    }

  assert( Output->GetTransferSyntax() == TS );
  return success;
}


} // end namespace gdcm

