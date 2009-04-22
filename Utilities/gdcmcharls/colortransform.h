// 
// (C) Jan de Vaan 2007-2009, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 
#ifndef CHARLS_COLORTRANSFORM
#define CHARLS_COLORTRANSFORM


struct TransformNone
{
	inlinehint static Triplet Apply(int v1, int v2, int v3)
	{ return Triplet(v1, v2, v3); }
};

struct TransformRgbToHp1
{
	inlinehint static Triplet Apply(int R, int G, int B)
	{
		Triplet hp1;
		hp1.v2 = BYTE(G);
		hp1.v1 = BYTE(R - G + 0x80);
		hp1.v3 = BYTE(B - G + 0x80);
		return hp1;
	}
};

struct TransformHp1ToRgb
{
	inlinehint static Triplet Apply(int v1, int v2, int v3)
	{ return Triplet(v1 + v2 - 0x80, v2, v3 + v2 - 0x80); }
};



struct TransformRgbToHp2
{
	inlinehint static Triplet Apply(int R, int G, int B)
	{
		//Triplet hp2;
		//hp2.v1 = BYTE(R - G + 0x80);
		//hp2.v2 = BYTE(G);
		//hp2.v3 = BYTE(B - ((R+G )>>1) - 0x80);
		//return hp2;
		return Triplet(R - G + 0x80, G, B - ((R+G )>>1) - 0x80);
	}
};

struct TransformHp2ToRgb
{
	inlinehint static Triplet Apply(int v1, int v2, int v3)
	{
		Triplet rgb;
		rgb.R  = BYTE(v1 + v2 - 0x80);          // new R
		rgb.G  = BYTE(v2);                     // new G				
		rgb.B  = BYTE(v3 + ((rgb.R + rgb.G) >> 1) - 0x80); // new B
		return rgb;
	}
};

struct TransformRgbToHp3
{
	inlinehint static Triplet Apply(int R, int G, int B)
	{
		Triplet hp3;		
		hp3.v2 = BYTE(B - G + 0x80);
		hp3.v3 = BYTE(R - G + 0x80);

		hp3.v1 = BYTE(G + ((hp3.v2 + hp3.v3 )>>2) - 0x40);
		return hp3;
	}
};


struct TransformHp3ToRgb
{
	inlinehint static Triplet Apply(int v1, int v2, int v3)
	{
		int G = v1 - ((v3 + v2)>>2)+0x40;
		Triplet rgb;
		rgb.R  = BYTE(v3 + G - 0x80); // new R
		rgb.G  = BYTE(G);             // new G				
		rgb.B  = BYTE(v2 + G - 0x80); // new B
		return rgb;
	}
};


template<class TRANSFORM> 
void TransformLine(Triplet* pDest, const Triplet* pSrc, int pixelCount, const TRANSFORM&)
{	
	for (int i = 0; i < pixelCount; ++i)
	{
		pDest[i] = TRANSFORM::Apply(pSrc[i].v1, pSrc[i].v2, pSrc[i].v3);
	}
};


template<class TRANSFORM> 
void TransformLineToTriplet(const BYTE* ptypeInput, LONG pixelStrideIn, BYTE* pbyteBuffer, LONG pixelStride, const TRANSFORM&)
{
	int cpixel = MIN(pixelStride, pixelStrideIn);
	Triplet* ptypeBuffer = (Triplet*)pbyteBuffer;

	for (int x = 0; x < cpixel; ++x)
	{
		ptypeBuffer[x] = TRANSFORM::Apply(ptypeInput[x], ptypeInput[x + pixelStrideIn], ptypeInput[x + 2*pixelStrideIn]);
	}
}

template<class TRANSFORM> 
void TransformTripletToLine(const BYTE* pbyteInput, LONG pixelStrideIn, BYTE* ptypeBuffer, LONG pixelStride, const TRANSFORM&)
{
	int cpixel = MIN(pixelStride, pixelStrideIn);
	const Triplet* ptypeBufferIn = (Triplet*)pbyteInput;

	for (int x = 0; x < cpixel; ++x)
	{
		Triplet color = ptypeBufferIn[x];
		Triplet colorTranformed = TRANSFORM::Apply(color.v1, color.v2, color.v3);

		ptypeBuffer[x] = colorTranformed.v1;
		ptypeBuffer[x + pixelStride] = colorTranformed.v2;
		ptypeBuffer[x + 2 *pixelStride] = colorTranformed.v3;
	}
}


#endif
