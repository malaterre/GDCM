// 
// (C) Jan de Vaan 2007-2009, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 
#ifndef CHARLS_PROCESSLINE
#define CHARLS_PROCESSLINE

#include "colortransform.h"


class ProcessLine
{
public:
	virtual ~ProcessLine() {}
	virtual void NewLineDecoded(const void* pSrc, int pixelCount, int byteStride) = 0;
	virtual void NewLineRequested(void* pSrc, int pixelCount, int byteStride) = 0;
};



class PostProcesSingleComponent : public ProcessLine
{
public:
	PostProcesSingleComponent(void* pbyteOutput, const JlsParamaters& info, int bytesPerPixel) :
		_pbyteOutput((BYTE*)pbyteOutput), 
		_bytesPerPixel(bytesPerPixel),
		_info(info)
	{
	}

	void NewLineRequested(void* pDst, int pixelCount, int byteStride)
	{
		::memcpy(pDst, _pbyteOutput, pixelCount * _bytesPerPixel);
		_pbyteOutput += pixelCount * _bytesPerPixel;
	}

	void NewLineDecoded(const void* pSrc, int pixelCount, int byteStride)
	{
		::memcpy(_pbyteOutput, pSrc, pixelCount * _bytesPerPixel);
		_pbyteOutput += pixelCount * _bytesPerPixel;
	}

private:
	BYTE* _pbyteOutput;
	int _bytesPerPixel;
	const JlsParamaters& _info;	
};




template<class TRANSFORM, class SAMPLE> 
void TransformLine(Triplet<SAMPLE>* pDest, const Triplet<SAMPLE>* pSrc, int pixelCount, const TRANSFORM&)
{	
	for (int i = 0; i < pixelCount; ++i)
	{
		pDest[i] = TRANSFORM::Apply(pSrc[i].v1, pSrc[i].v2, pSrc[i].v3);
	}
}


template<class TRANSFORM, class SAMPLE> 
void TransformLineToTriplet(const SAMPLE* ptypeInput, LONG pixelStrideIn, Triplet<SAMPLE>* pbyteBuffer, LONG pixelStride, const TRANSFORM&)
{
	int cpixel = MIN(pixelStride, pixelStrideIn);
	Triplet<SAMPLE>* ptypeBuffer = (Triplet<SAMPLE>*)pbyteBuffer;

	for (int x = 0; x < cpixel; ++x)
	{
		ptypeBuffer[x] = TRANSFORM::Apply(ptypeInput[x], ptypeInput[x + pixelStrideIn], ptypeInput[x + 2*pixelStrideIn]);
	}
}

template<class TRANSFORM, class SAMPLE> 
void TransformTripletToLine(const Triplet<SAMPLE>* pbyteInput, LONG pixelStrideIn, SAMPLE* ptypeBuffer, LONG pixelStride, const TRANSFORM&)
{
	int cpixel = MIN(pixelStride, pixelStrideIn);
	const Triplet<SAMPLE>* ptypeBufferIn = (Triplet<SAMPLE>*)pbyteInput;

	for (int x = 0; x < cpixel; ++x)
	{
		Triplet<SAMPLE> color = ptypeBufferIn[x];
		Triplet<SAMPLE> colorTranformed = TRANSFORM::Apply(color.v1, color.v2, color.v3);

		ptypeBuffer[x] = colorTranformed.v1;
		ptypeBuffer[x + pixelStride] = colorTranformed.v2;
		ptypeBuffer[x + 2 *pixelStride] = colorTranformed.v3;
	}
}



template<class TRANSFORM> 
class ProcessTransformed : public ProcessLine
{
	typedef typename TRANSFORM::SAMPLE SAMPLE;
	ProcessTransformed(const ProcessTransformed&) {}
public:
	ProcessTransformed(void* pbyteOutput, const JlsParamaters& info) :
		_pbyteOutput((BYTE*)pbyteOutput),
		_info(info)
	{
		ASSERT(_info.components == 3);
	}

	void NewLineRequested(void* pDst, int pixelCount, int byteStride)
	{
		if (_info.ilv == ILV_SAMPLE)
		{
			TransformLine((Triplet<SAMPLE>*)pDst, (const Triplet<SAMPLE>*)_pbyteOutput, pixelCount, TRANSFORM());
		}
		else
		{
			TransformTripletToLine((const Triplet<SAMPLE>*)_pbyteOutput, pixelCount, (SAMPLE*)pDst, byteStride, TRANSFORM());
		}
		_pbyteOutput += sizeof(Triplet<SAMPLE>)*pixelCount;
	}

	void NewLineDecoded(const void* pSrc, int pixelCount, int byteStride)
	{
		if (_info.ilv == ILV_SAMPLE)
		{
			TransformLine((Triplet<SAMPLE>*)_pbyteOutput, (const Triplet<SAMPLE>*)pSrc, pixelCount, typename TRANSFORM::INVERSE());
		}
		else
		{
			TransformLineToTriplet((const SAMPLE*)pSrc, byteStride, (Triplet<SAMPLE>*)_pbyteOutput, pixelCount, typename TRANSFORM::INVERSE());
		}
		_pbyteOutput += sizeof(Triplet<SAMPLE>)*pixelCount;
	}

private:
	BYTE* _pbyteOutput;
	const JlsParamaters& _info;	
};




#endif
