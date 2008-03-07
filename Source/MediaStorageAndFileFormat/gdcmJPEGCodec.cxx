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
#include "gdcmDataElement.h"
#include "gdcmSequenceOfFragments.h"

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

void JPEGCodec::SetPixelFormat(PixelFormat const &pt)
{
  ImageCodec::SetPixelFormat(pt);
  //SetBitSample( pt.GetBitsAllocated() );
  SetBitSample( pt.GetBitsStored() );
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
    gdcmWarningMacro( "Cannot instantiate JPEG codec for bit sample: " << bit );
    // Clearly make sure Internal will not be used
    delete Internal;
    Internal = NULL;
    }
  Internal->SetPhotometricInterpretation( this->GetPhotometricInterpretation() );
  Internal->ImageCodec::SetPixelFormat( this->ImageCodec::GetPixelFormat() );
}

bool JPEGCodec::Decode(DataElement const &in, DataElement &out)
{
  out = in;
      // Fragments...
    const SequenceOfFragments *sf = in.GetSequenceOfFragments();
    assert( sf );
//#define MDEBUG
#ifdef MDEBUG
    sf->GetBuffer(buffer, len);
    unsigned long totalLen = sf->ComputeByteLength();
    std::ofstream f("/tmp/debug.jpg");
    f.write(buffer, totalLen);
    f.close();
#endif
        std::stringstream os;
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
        bool r = Decode(is, os);
        assert( r == true );
        //std::streampos p = is.tellg();
        //assert( (bv.GetLength() - p) == 0 );
        //std::string::size_type check = os.str().size();
        //memcpy(buffer+pos, os.str().c_str(), check);
        //pos += check;
        }
      //assert( pos == len );
    std::string str = os.str();
    out.SetByteValue( &str[0], str.size() );
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
        //abort(); // Outside buffer will be too small
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
