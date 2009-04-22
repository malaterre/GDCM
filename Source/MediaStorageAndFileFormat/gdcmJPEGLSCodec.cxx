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
  assert( NumberOfDimensions == 2 );

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

abort();
//  this->Dimensions[0] = comp->w;
//  this->Dimensions[1] = comp->h;
//  this->PF = PixelFormat( PixelFormat::UINT8 );
//    PI = PhotometricInterpretation::MONOCHROME2;
//    this->PF.SetSamplesPerPixel( 1 );
//
//    if( metadata.allowedlossyerror )
//      {
//    ts = TransferSyntax::JPEG2000Lossless;
//      }


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
