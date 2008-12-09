/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
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

/*
bool ImageChangeTransferSyntax::TryRAWCodecIcon(const DataElement &pixelde)
{
  unsigned long len = Input->GetIconImage().GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  RAWCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetIconImage().GetDimensions() );
    codec.SetPlanarConfiguration( Input->GetIconImage().GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetIconImage().GetPhotometricInterpretation() );
    codec.SetPixelFormat( Input->GetIconImage().GetPixelFormat() );
    codec.SetNeedOverlayCleanup( Input->GetIconImage().AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(Input->GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = Output->GetIconImage().GetDataElement();
    de.SetValue( out.GetValue() );
    if( !r )
      {
      return false;
      }
    return true;
    }
  return false;
}
*/

bool ImageChangeTransferSyntax::TryRAWCodec(const DataElement &pixelde, Pixmap const &input, Pixmap &output)
{
  unsigned long len = input.GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  RAWCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( input.GetDimensions() );
    codec.SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec.SetPixelFormat( input.GetPixelFormat() );
    codec.SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(input.GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    if( !r )
      {
      return false;
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryRLECodec(const DataElement &pixelde, Pixmap const &input, Pixmap &output)
{
  unsigned long len = input.GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  RLECodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( input.GetDimensions() );
    codec.SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec.SetPixelFormat( input.GetPixelFormat() );
    codec.SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(input.GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    if( !r )
      {
      return false;
      }
    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEGCodec(const DataElement &pixelde, Pixmap const &input, Pixmap &output)
{
  unsigned long len = input.GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( input.GetDimensions() );
    // FIXME: GDCM always apply the planar configuration to 0...
    //if( input.GetPlanarConfiguration() )
    //  {
    //  output.SetPlanarConfiguration( 0 );
    //  }
    codec.SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec.SetPixelFormat( input.GetPixelFormat() );
    codec.SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(input.GetDataElement(), out);
    bool r = codec.Code(pixelde, out);
    // FIXME: this is not the best place to change the Output image internal type,
    // but since I know IJG is always applying the Planar Configuration, it does make
    // any sense to EVER produce a JPEG image where the Planar Configuration would be one
    // so let's be nice and actually sync JPEG configuration with DICOM Planar Conf.
    output.SetPlanarConfiguration( 0 );
    //output.SetPhotometricInterpretation( PhotometricInterpretation::RGB );

    // Indeed one cannot produce a true lossless RGB image according to DICOM standard
    // when doing lossless jpeg:
    if( output.GetPhotometricInterpretation() == PhotometricInterpretation::RGB )
      {
      gdcmWarningMacro( "Technically this is not defined in the standard. \n"
        "Some validator may complains this image is invalid, but would be wrong.");
      }

    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
    if( !r )
      {
      return false;
      }
    // When compressing with JPEG I think planar should always be:
    //output.SetPlanarConfiguration(0);
    // FIXME ! This should be done all the time for all codec:
    // Did PI change or not ?
    if ( output.GetPhotometricInterpretation() != codec.GetPhotometricInterpretation() )
      {
      // HACK
      //gdcm::Image *i = (gdcm::Image*)this;
      //i->SetPhotometricInterpretation( codec.GetPhotometricInterpretation() );
abort();
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEGLSCodec(const DataElement &pixelde, Pixmap const &input, Pixmap &output)
{
  unsigned long len = input.GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGLSCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( input.GetDimensions() );
    codec.SetPixelFormat( input.GetPixelFormat() );
    //codec.SetNumberOfDimensions( input.GetNumberOfDimensions() );
    codec.SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(input.GetDataElement(), out);
    bool r = codec.Code(pixelde, out);

    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    return r;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEG2000Codec(const DataElement &pixelde, Pixmap const &input, Pixmap &output)
{
  unsigned long len = input.GetBufferLength();
  //assert( len == pixelde.GetByteValue()->GetLength() );
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec j2kcodec;
  ImageCodec *codec = &j2kcodec;
  if( UserCodec && UserCodec->CanCode( ts ) )
    {
    codec = UserCodec;
    }
  
  if( codec->CanCode( ts ) )
    {
    codec->SetDimensions( input.GetDimensions() );
    codec->SetPixelFormat( input.GetPixelFormat() );
    codec->SetNumberOfDimensions( input.GetNumberOfDimensions() );
    codec->SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec->SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec->SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;
    //bool r = codec.Code(input.GetDataElement(), out);
    bool r = codec->Code(pixelde, out);

    // The value of Planar Configuration (0028,0006) is irrelevant since the manner of encoding components is
    // specified in the JPEG 2000 standard, hence it shall be set to 0.
    output.SetPlanarConfiguration( 0 );

    if( input.GetPixelFormat().GetSamplesPerPixel() == 3 )
      {
      if( input.GetPhotometricInterpretation() == PhotometricInterpretation::RGB )
        {
        if( ts == TransferSyntax::JPEG2000Lossless )
          {
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_RCT );
          }
        else 
          {
          assert( ts == TransferSyntax::JPEG2000 );
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_ICT );
          }
        }
      else
        {
        assert( input.GetPhotometricInterpretation() == PhotometricInterpretation::YBR_FULL );
        if( ts == TransferSyntax::JPEG2000Lossless )
          {
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_FULL );
          // Indeed one cannot produce a true lossless RGB image according to DICOM standard
          gdcmWarningMacro( "Technically this is not defined in the standard. \n"
            "Some validator may complains this image is invalid, but would be wrong.");
          }
        else
          {
          assert( ts == TransferSyntax::JPEG2000 );
          //output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_ICT );
          // FIXME: technically when doing lossy we could be standard compliant and first convert to
          // RGB THEN compress to YBR_ICT. For now produce improper j2k image
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_FULL );
          }
        }
      }
    else
      {
      assert( input.GetPixelFormat().GetSamplesPerPixel() == 1 );
      }

    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    if( !r ) return false;
    assert( r );
    return r;
    }
  return false;
}

bool ImageChangeTransferSyntax::Change()
{
  // let's get rid of some easy case:
  if( Input->GetPhotometricInterpretation() == PhotometricInterpretation::PALETTE_COLOR && 
    TS.IsLossy() )
    {
    gdcmErrorMacro( "PALETTE_COLOR and Lossy compression are impossible. Convert to RGB first." );
    return false;
    }

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
    if( !success ) success = TryRAWCodec(pixeldata, *Input, *Output);
    if( !success ) success = TryJPEGCodec(pixeldata, *Input, *Output);
    if( !success ) success = TryJPEGLSCodec(pixeldata, *Input, *Output);
    if( !success ) success = TryJPEG2000Codec(pixeldata, *Input, *Output);
    if( !success ) success = TryRLECodec(pixeldata, *Input, *Output);
    Output->SetTransferSyntax( TS );
    if( !success )
      {
      //abort();
      return false;
      }

    // same goes for icon
    gdcm::DataElement iconpixeldata( gdcm::Tag(0x7fe0,0x0010) );
    if( !Input->GetIconImage().IsEmpty() )
{
    // same goes for icon
    gdcm::ByteValue *bv = new gdcm::ByteValue();
    unsigned long len = Input->GetIconImage().GetBufferLength();
    bv->SetLength( len );
    bool b = Input->GetIconImage().GetBuffer( (char*)bv->GetPointer() );
    if( !b )
      {
      return false;
      }
    iconpixeldata.SetValue( *bv );

    success = false;
    if( !success ) success = TryRAWCodec(iconpixeldata, Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEGCodec(iconpixeldata, Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEGLSCodec(iconpixeldata, Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEG2000Codec(iconpixeldata, Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryRLECodec(iconpixeldata, Input->GetIconImage(), Output->GetIconImage());
    Output->GetIconImage().SetTransferSyntax( TS );
    if( !success )
      {
      //abort();
      return false;
      }
    assert( Output->GetIconImage().GetTransferSyntax() == TS );
}

    assert( Output->GetTransferSyntax() == TS );
    return success;
    }

  // too bad we actually have to do some work...
  bool success = false;
  if( !success ) success = TryRAWCodec(Input->GetDataElement(), *Input, *Output);
  if( !success ) success = TryJPEGCodec(Input->GetDataElement(), *Input, *Output);
  if( !success ) success = TryJPEG2000Codec(Input->GetDataElement(), *Input, *Output);
  if( !success ) success = TryJPEGLSCodec(Input->GetDataElement(), *Input, *Output);
  if( !success ) success = TryRLECodec(Input->GetDataElement(), *Input, *Output);
  Output->SetTransferSyntax( TS );
  if( !success )
    {
    //abort();
    return false;
    }

    if( !Input->GetIconImage().IsEmpty() && CompressIconImage )
  {
    // same goes for icon
    success = false;
    if( !success ) success = TryRAWCodec(Input->GetIconImage().GetDataElement(), Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEGCodec(Input->GetIconImage().GetDataElement(), Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEGLSCodec(Input->GetIconImage().GetDataElement(), Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryJPEG2000Codec(Input->GetIconImage().GetDataElement(), Input->GetIconImage(), Output->GetIconImage());
    if( !success ) success = TryRLECodec(Input->GetIconImage().GetDataElement(), Input->GetIconImage(), Output->GetIconImage());
    Output->GetIconImage().SetTransferSyntax( TS );
    if( !success )
      {
      //abort();
      return false;
      }
  assert( Output->GetIconImage().GetTransferSyntax() == TS );
  }

  assert( Output->GetTransferSyntax() == TS );
  return success;
}


} // end namespace gdcm

