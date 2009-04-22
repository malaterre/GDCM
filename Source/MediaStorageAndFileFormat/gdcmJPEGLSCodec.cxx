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
  (void)is; (void)ts;
  return false;
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

/*
void SwapBytes(std::vector<BYTE>* rgbyte)
{
	 for (unsigned int i = 0; i < rgbyte->size(); i += 2)
	 {
		 std::swap((*rgbyte)[i], (*rgbyte)[i + 1]);
	 }
}

void TestCompliance(const BYTE* pbyteCompressed, int cbyteCompressed, const BYTE* rgbyteRaw, int cbyteRaw)
{	
	JlsParamaters params = {0};
	JpegLsReadHeader(pbyteCompressed, cbyteCompressed, &params);

	std::vector<BYTE> rgbyteCompressed;
	rgbyteCompressed.resize(params.height *params.width* 4);
	
	std::vector<BYTE> rgbyteOut;
	rgbyteOut.resize(params.height *params.width * ((params.bitspersample + 7) / 8) * params.components);
	
	JLS_ERROR result = JpegLsDecode(&rgbyteOut[0], rgbyteOut.size(), pbyteCompressed, cbyteCompressed);
	ASSERT(result == OK);

	if (params.allowedlossyerror == 0)
	{
		BYTE* pbyteOut = &rgbyteOut[0];
		for (int i = 0; i < cbyteRaw; ++i)
		{
			if (rgbyteRaw[i] != pbyteOut[i])
			{
				ASSERT(false);
				break;
			}
		}						    
	}

//	int cbyteCompressedActual = 0;

	JLS_ERROR error = JpegLsVerifyEncode(&rgbyteRaw[0], cbyteRaw, pbyteCompressed, cbyteCompressed);
	ASSERT(error == OK);
}

void DecompressFile(SZC strNameEncoded, SZC strNameRaw, int ioffs)
{
	//std::cout << "Conformance test:" << strNameEncoded << "\n\r";
	std::vector<BYTE> rgbyteFile;
	ReadFile(strNameEncoded, &rgbyteFile);

	JlsParamaters metadata;
	if (JpegLsReadHeader(&rgbyteFile[0], rgbyteFile.size(), &metadata) != OK)
	{
		ASSERT(false);
		return;
	}

// 	std::vector<BYTE> rgbyteRaw;
//	ReadFile(strNameRaw, &rgbyteRaw, ioffs);
//
//	if (metadata.bitspersample > 8)
//	{
//		SwapBytes(&rgbyteRaw);		
//	}

//	Size size = Size(metadata.width, metadata.height);

//	if (metadata.ilv == ILV_NONE && metadata.components == 3)
//	{
//		Triplet2Planar(rgbyteRaw, Size(metadata.width, metadata.height));
//	}
//
//	if (metadata.ilv == ILV_LINE && metadata.components == 3)
//	{
//		Triplet2Line(rgbyteRaw, Size(metadata.width, metadata.height));
//	}

	TestCompliance(&rgbyteFile[0], rgbyteFile.size(), &rgbyteRaw[0], rgbyteRaw.size());
}
*/

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
