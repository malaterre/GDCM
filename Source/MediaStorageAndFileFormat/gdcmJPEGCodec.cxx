/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmJPEGCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmTrace.h"
#include "gdcmDataElement.h"
#include "gdcmSequenceOfFragments.h"

#include "gdcmJPEG8Codec.h"
#include "gdcmJPEG12Codec.h"
#include "gdcmJPEG16Codec.h"

namespace gdcm
{

JPEGCodec::JPEGCodec():BitSample(0),Lossless(true),Quality(100)
{
  Internal = NULL;
}

JPEGCodec::~JPEGCodec()
{
  delete Internal;
}

void JPEGCodec::SetQuality(double q)
{
  Quality = q;
}

double JPEGCodec::GetQuality() const
{
  return Quality;
}

void JPEGCodec::SetLossless(bool l)
{
  Lossless = l;
}

bool JPEGCodec::GetLossless() const
{
  return Lossless;
}

bool JPEGCodec::CanDecode(TransferSyntax const &ts) const
{
  return ts == TransferSyntax::JPEGBaselineProcess1
      || ts == TransferSyntax::JPEGExtendedProcess2_4
      || ts == TransferSyntax::JPEGExtendedProcess3_5
      || ts == TransferSyntax::JPEGSpectralSelectionProcess6_8
      || ts == TransferSyntax::JPEGFullProgressionProcess10_12
      || ts == TransferSyntax::JPEGLosslessProcess14
      || ts == TransferSyntax::JPEGLosslessProcess14_1;
}

bool JPEGCodec::CanCode(TransferSyntax const &ts) const
{
  return ts == TransferSyntax::JPEGBaselineProcess1
      || ts == TransferSyntax::JPEGExtendedProcess2_4
      || ts == TransferSyntax::JPEGExtendedProcess3_5
      || ts == TransferSyntax::JPEGSpectralSelectionProcess6_8
      || ts == TransferSyntax::JPEGFullProgressionProcess10_12
      || ts == TransferSyntax::JPEGLosslessProcess14
      || ts == TransferSyntax::JPEGLosslessProcess14_1;
}

void JPEGCodec::SetPixelFormat(PixelFormat const &pt)
{
  ImageCodec::SetPixelFormat(pt);
  // Here is the deal: D_CLUNIE_RG3_JPLY.dcm is a 12Bits Stored / 16 Bits Allocated image
  // the jpeg encapsulated is: a 12 Sample Precision
  // so far so good.
  // So what if we are dealing with image such as: SIEMENS_MOSAIC_12BitsStored-16BitsJPEG.dcm
  // which is also a 12Bits Stored / 16 Bits Allocated image
  // however the jpeg encapsulated is now a 16 Sample Precision
  //SetBitSample( pt.GetBitsAllocated() );
  SetBitSample( pt.GetBitsStored() );
}

void JPEGCodec::SetBitSample(int bit)
{
  BitSample = bit;
  delete Internal; Internal = NULL;
  assert( Internal == NULL );
  if ( BitSample <= 8 )
    {
    gdcmDebugMacro( "Using JPEG8" );
    Internal = new JPEG8Codec;
    }
  else if ( BitSample <= 12 )
    {
    gdcmDebugMacro( "Using JPEG12" );
    Internal = new JPEG12Codec;
    }
  else if ( BitSample <= 16 )
    {
    gdcmDebugMacro( "Using JPEG16" );
    Internal = new JPEG16Codec;
    }
  else
    {
    // gdcmNonImageData/RT/RTDOSE.dcm 
    gdcmWarningMacro( "Cannot instantiate JPEG codec for bit sample: " << bit );
    // Clearly make sure Internal will not be used
    delete Internal;
    Internal = NULL;
    return;
    }
  Internal->SetDimensions( this->GetDimensions() );
  Internal->SetPlanarConfiguration( this->GetPlanarConfiguration() );
  Internal->SetPhotometricInterpretation( this->GetPhotometricInterpretation() );
  Internal->ImageCodec::SetPixelFormat( this->ImageCodec::GetPixelFormat() );
  //Internal->SetNeedOverlayCleanup( this->AreOverlaysInPixelData() );
  assert( Internal != NULL );
}

/*
A.4.1 JPEG image compression

For all images, including all frames of a multi-frame image, the JPEG Interchange Format shall be used
(the table specification shall be included).
*/
bool JPEGCodec::Decode(DataElement const &in, DataElement &out)
{
  assert( Internal );
  out = in;
  // Fragments...
  const SequenceOfFragments *sf = in.GetSequenceOfFragments();
  const ByteValue *jpegbv = in.GetByteValue();
  if( !sf && !jpegbv ) return false;
  std::stringstream os;
  if( sf )
    {
    //unsigned long pos = 0;
    for(unsigned int i = 0; i < sf->GetNumberOfFragments(); ++i)
      {
      std::stringstream is;
      const Fragment &frag = sf->GetFragment(i);
      if( frag.IsEmpty() ) return false;
      const ByteValue &bv = dynamic_cast<const ByteValue&>(frag.GetValue());
      char *mybuffer = new char[bv.GetLength()];
      bv.GetBuffer(mybuffer, bv.GetLength());
      is.write(mybuffer, bv.GetLength());
      delete[] mybuffer;
      bool r = Decode(is, os);
      // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
      if( !r )
        {
        return false;
        }
      }
    }
  else if ( jpegbv )
    {
    // GEIIS Icon:
    std::stringstream is;
    char *mybuffer = new char[jpegbv->GetLength()];
    jpegbv->GetBuffer(mybuffer, jpegbv->GetLength());
    is.write(mybuffer, jpegbv->GetLength());
    delete[] mybuffer;
    bool r = Decode(is, os);
    if( !r )
      {
      return false;
      }
    }
  //assert( pos == len );
  std::string str = os.str();
  out.SetByteValue( &str[0], str.size() );
  return true;
}

void JPEGCodec::ComputeOffsetTable(bool b)
{
  // Not implemented 
  assert(0);
}

bool JPEGCodec::GetHeaderInfo( std::istream & is, TransferSyntax &ts )
{
  if ( !Internal->GetHeaderInfo(is, ts) )
    {
    // let's check if this is one of those buggy lossless JPEG
    if( this->BitSample != Internal->BitSample )
      {
      // MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm
      // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm
      gdcmWarningMacro( "DICOM header said it was " << this->BitSample <<
        " but JPEG header says it's: " << Internal->BitSample );
      if( this->BitSample < Internal->BitSample )
        {
        //assert(0); // Outside buffer will be too small
        }
      this->BitSample = Internal->BitSample; // Store the value found before destroying Internal
      delete Internal; Internal = 0; // Do not attempt to reuse the pointer
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
        assert(0);
        }
      if( Internal->GetHeaderInfo(is, ts) )
        {
        // Foward everything back to meta jpeg codec:
        this->SetDimensions( Internal->GetDimensions() );
        this->SetPhotometricInterpretation( Internal->GetPhotometricInterpretation() );
        int prep = this->GetPixelFormat().GetPixelRepresentation();
        this->PF = Internal->GetPixelFormat(); // DO NOT CALL SetPixelFormat
        this->PF.SetPixelRepresentation( prep );
        return true;
        }
      else
        {
        assert(0); // FATAL ERROR
        }
      }
    return false;
    }
  // else
  // Foward everything back to meta jpeg codec:
  this->SetDimensions( Internal->GetDimensions() );
  this->SetPhotometricInterpretation( Internal->GetPhotometricInterpretation() );
  this->PF = Internal->GetPixelFormat(); // DO NOT CALL SetPixelFormat

  if( this->PI != Internal->PI )
    {
    gdcmWarningMacro( "PhotometricInterpretation issue" );
    this->PI = Internal->PI;
    }

  return true;
}

bool JPEGCodec::Code(DataElement const &in, DataElement &out)
{
  out = in;

  // Create a Sequence Of Fragments:
  SmartPointer<SequenceOfFragments> sq = new SequenceOfFragments;
  const Tag itemStart(0xfffe, 0xe000);
  //sq->GetTable().SetTag( itemStart );
  //const char dummy[4] = {};
  //sq->GetTable().SetByteValue( dummy, sizeof(dummy) );

  const ByteValue *bv = in.GetByteValue();
  const unsigned int *dims = this->GetDimensions();
  const char *input = bv->GetPointer();
  unsigned long len = bv->GetLength();
  unsigned long image_len = len / dims[2];
  if(!Internal) return false;

  // forward parameter to low level bits implementation (8/12/16)
  Internal->SetLossless( this->GetLossless() );
  Internal->SetQuality( this->GetQuality() );

  for(unsigned int dim = 0; dim < dims[2]; ++dim)
    {
    std::stringstream os;
    const char *p = input + dim * image_len;
    bool r = Internal->InternalCode(p, image_len, os);
    if( !r )
      {
      return false;
      }

    std::string str = os.str();
    assert( str.size() );
    Fragment frag;
    //frag.SetTag( itemStart );
    frag.SetByteValue( &str[0], str.size() );
    sq->AddFragment( frag );

    }
  unsigned int n = sq->GetNumberOfFragments();
  assert( sq->GetNumberOfFragments() == dims[2] );
  out.SetValue( *sq );

  return true;
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
        //assert(0); // Outside buffer will be too small
        }
      this->BitSample = Internal->BitSample; // Store the value found before destroying Internal
      delete Internal; Internal = 0; // Do not attempt to reuse the pointer
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
        assert(0);
        }
      Internal->SetPlanarConfiguration( this->GetPlanarConfiguration() ); // meaning less ?
      Internal->SetPhotometricInterpretation( this->GetPhotometricInterpretation() );
      if( Internal->Decode(is,tmpos) )
        {
        return ImageCodec::Decode(tmpos,os);
        }
      else
        {
        assert(0); // FATAL ERROR
        }
      }
#endif
    return false;
    }
  if( this->PI != Internal->PI )
    {
    gdcmWarningMacro( "PhotometricInterpretation issue" );
    this->PI = Internal->PI;
    }
  if( this->PF == PixelFormat::UINT12
   || this->PF == PixelFormat::INT12 )
    {
    this->PF.SetBitsAllocated( 16 );
    }

  return ImageCodec::Decode(tmpos,os);
}

bool JPEGCodec::IsValid(PhotometricInterpretation const &pi)
{
  bool ret = false;
  switch( pi )
    {
    // JPEGCodec can produce the following PhotometricInterpretation as output:
    case PhotometricInterpretation::MONOCHROME1:
    case PhotometricInterpretation::MONOCHROME2:
    case PhotometricInterpretation::PALETTE_COLOR:
    case PhotometricInterpretation::RGB:
    case PhotometricInterpretation::YBR_FULL:
    case PhotometricInterpretation::YBR_FULL_422:
    case PhotometricInterpretation::YBR_PARTIAL_422:
    case PhotometricInterpretation::YBR_PARTIAL_420:
      ret = true;
      break;
    default:
      ;
//    case HSV:
//    case ARGB: // retired
//    case CMYK:
//    case YBR_RCT:
//    case YBR_ICT:
//      ret = false;
    }
  return ret;
}

} // end namespace gdcm
