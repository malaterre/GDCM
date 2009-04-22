/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmJPEGLSCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmDataElement.h"

// CharLS includes
#include "gdcmcharls/stdafx.h" // sigh...
#include "gdcmcharls/interface.h"
#include "gdcmcharls/util.h"
#include "gdcmcharls/defaulttraits.h"
#include "gdcmcharls/losslesstraits.h"


namespace gdcm
{

JPEGLSCodec::JPEGLSCodec():BufferLength(0)
{
}

JPEGLSCodec::~JPEGLSCodec()
{
}

bool JPEGLSCodec::GetHeaderInfo(std::istream &is, TransferSyntax &ts)
{
#ifndef GDCM_USE_JPEGLS
  return false;
#else
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(0, std::ios::beg);
  is.read( dummy_buffer, buf_size);

  JlsParamaters metadata;
  if (JpegLsReadHeader(dummy_buffer, buf_size, &metadata) != OK)
    {
    return false;
    }
  delete[] dummy_buffer;

  // $1 = {width = 512, height = 512, bitspersample = 8, components = 1, allowedlossyerror = 0, ilv = ILV_NONE, colorTransform = 0, custom = {MAXVAL = 0, T1 = 0, T2 = 0, T3 = 0, RESET = 0}}

  this->Dimensions[0] = metadata.width;
  this->Dimensions[1] = metadata.height;
  switch( metadata.bitspersample )
    {
  case 8:
    this->PF = PixelFormat( PixelFormat::UINT8 );
    break;
  case 12:
    this->PF = PixelFormat( PixelFormat::UINT16 );
    this->PF.SetBitsStored( 12 );
    break;
  case 16:
    this->PF = PixelFormat( PixelFormat::UINT16 );
    break;
  default:
    abort();
    }
  if( metadata.components == 1 )
    {
    PI = PhotometricInterpretation::MONOCHROME2;
    this->PF.SetSamplesPerPixel( 1 );
    }
  else if( metadata.components == 3 )
    {
    PI = PhotometricInterpretation::RGB;
    this->PF.SetSamplesPerPixel( 3 );
    }
  else abort();


  if( metadata.allowedlossyerror == 0 )
    {
    ts = TransferSyntax::JPEGLSLossless;
    }
  else
    {
    ts = TransferSyntax::JPEGLSNearLossless;
    }


  return true;
#endif
}

bool JPEGLSCodec::CanDecode(TransferSyntax const &ts) const
{
#ifndef GDCM_USE_JPEGLS
  return false;
#else
  return ts == TransferSyntax::JPEGLSLossless 
      || ts == TransferSyntax::JPEGLSNearLossless;
#endif
}

bool JPEGLSCodec::CanCode(TransferSyntax const &ts) const
{
#ifndef GDCM_USE_JPEGLS
  return false;
#else
  return ts == TransferSyntax::JPEGLSLossless 
      || ts == TransferSyntax::JPEGLSNearLossless;
#endif
}

bool JPEGLSCodec::Decode(DataElement const &in, DataElement &out)
{
#ifndef GDCM_USE_JPEGLS
  return false;
#else
  assert( NumberOfDimensions == 2 );

  const SequenceOfFragments *sf = in.GetSequenceOfFragments();
  assert( sf );
  std::stringstream is;
  unsigned long totalLen = sf->ComputeByteLength();
  char *buffer = new char[totalLen];
  sf->GetBuffer(buffer, totalLen);
  //is.write(buffer, totalLen);

  JlsParamaters metadata;
  if (JpegLsReadHeader(buffer, totalLen, &metadata) != OK)
    {
    return false;
    }

  // allowedlossyerror == 0 => Lossless
  LossyFlag = metadata.allowedlossyerror;

	//TestCompliance(&rgbyteFile[0], rgbyteFile.size(), &rgbyteRaw[0], rgbyteRaw.size());
  // void TestCompliance(const BYTE* pbyteCompressed, int cbyteCompressed, const BYTE* rgbyteRaw, int cbyteRaw)
  const BYTE* pbyteCompressed = (const BYTE*)buffer;
  int cbyteCompressed = totalLen;

	JlsParamaters params = {0};
	JpegLsReadHeader(pbyteCompressed, cbyteCompressed, &params);

	std::vector<BYTE> rgbyteCompressed;
	rgbyteCompressed.resize(params.height *params.width* 4);
	
	std::vector<BYTE> rgbyteOut;
	rgbyteOut.resize(params.height *params.width * ((params.bitspersample + 7) / 8) * params.components);
	
	JLS_ERROR result = JpegLsDecode(&rgbyteOut[0], rgbyteOut.size(), pbyteCompressed, cbyteCompressed);
	ASSERT(result == OK);

	//if (params.allowedlossyerror == 0)
	//{
	//	BYTE* pbyteOut = &rgbyteOut[0];
	//	for (int i = 0; i < cbyteRaw; ++i)
	//	{
	//		if (rgbyteRaw[i] != pbyteOut[i])
	//		{
	//			ASSERT(false);
	//			break;
	//		}
	//	}						    
	//}

//	int cbyteCompressedActual = 0;

//	JLS_ERROR error = JpegLsVerifyEncode(&rgbyteRaw[0], cbyteRaw, pbyteCompressed, cbyteCompressed);
//	ASSERT(error == OK);


    delete[] buffer;

    out = in;

    out.SetByteValue( (char*)&rgbyteOut[0], rgbyteOut.size() );
    return true;

#endif
}

// Compress into JPEG
bool JPEGLSCodec::Code(DataElement const &in, DataElement &out)
{
#ifndef GDCM_USE_JPEGLS
  return false;
#else
  return false;

#endif
}

} // end namespace gdcm
