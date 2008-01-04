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
#include "gdcmJPEGCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmTrace.h"

#include "gdcmJPEG8Codec.h"
#include "gdcmJPEG12Codec.h"
#include "gdcmJPEG16Codec.h"

namespace gdcm
{

JPEGCodec::JPEGCodec():BitSample(0)
{
  Internal = NULL;
}

JPEGCodec::~JPEGCodec()
{
  delete Internal;
}

bool JPEGCodec::CanDecode(TransferSyntax const &ts)
{
  return ts == TransferSyntax::JPEGBaselineProcess1
    || ts == TransferSyntax::JPEGExtendedProcess2_4
    || ts == TransferSyntax::JPEGExtendedProcess3_5
    || ts == TransferSyntax::JPEGSpectralSelectionProcess6_8
    || ts == TransferSyntax::JPEGFullProgressionProcess10_12
    || ts == TransferSyntax::JPEGLosslessProcess14
    || ts == TransferSyntax::JPEGLosslessProcess14_1;
}

void JPEGCodec::SetPixelType(PixelType const &pt)
{
  //SetBitSample( pt.GetBitsAllocated() );
  SetBitSample( pt.GetBitsStored() );
  ImageCodec::SetPixelType(pt);
}

void JPEGCodec::SetBitSample(int bit)
{
  BitSample = bit;
  assert( Internal == NULL );
  if ( BitSample <= 8 )
    {
    Internal = new JPEG8Codec;
    }
  else if ( BitSample <= 12 )
    {
    Internal = new JPEG12Codec;
    }
  else if ( BitSample <= 16 )
    {
    Internal = new JPEG16Codec;
    }
  else
    {
    gdcmWarningMacro( "bla" );
    // Clearly make sure Internal will not be used
    delete Internal;
    Internal = NULL;
    }
  Internal->SetPhotometricInterpretation( this->GetPhotometricInterpretation() );
}

bool JPEGCodec::Decode(std::istream &is, std::ostream &os)
{
  std::stringstream tmpos;
  if ( !Internal->Decode(is,tmpos) )
    {
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    // let's check if this is one of those buggy lossless JPEG
    if( this->BitSample != Internal->BitSample )
      {
      // MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm
      // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm
      gdcmWarningMacro( "DICOM header said it was " << this->BitSample <<
        " but JPEG header says it's: " << Internal->BitSample );
      if( this->BitSample < Internal->BitSample )
        {
        //abort(); // Outside buffer will be too small
        }
      this->BitSample = Internal->BitSample; // Store the value before destroying Internal
      delete Internal;
      Internal = 0; // Do not attempt to reuse the pointer
      is.seekg(0, std::ios::beg);
      switch( this->BitSample )
        {
      case 8:
        Internal = new JPEG8Codec;
        break;
      case 12:
        Internal = new JPEG12Codec;
        break;
      case 16:
        Internal = new JPEG16Codec;
        break;
      default:
        abort();
        }
      Internal->SetPhotometricInterpretation(
        this->GetPhotometricInterpretation() );
      if( Internal->Decode(is,tmpos) )
        {
        return ImageCodec::Decode(tmpos,os);
        }
      else
        {
        abort(); // FATAL ERROR
        }
      }
#endif
    return false;
    }

  return ImageCodec::Decode(tmpos,os);
}

} // end namespace gdcm
