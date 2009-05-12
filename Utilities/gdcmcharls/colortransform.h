// 
// (C) Jan de Vaan 2007-2009, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 
#ifndef CHARLS_COLORTRANSFORM
#define CHARLS_COLORTRANSFORM

template<class sample>
struct TransformNoneImpl
{
	typedef sample SAMPLE;

	inlinehint static Triplet<SAMPLE> Apply(int v1, int v2, int v3)
	{ return Triplet<SAMPLE>(v1, v2, v3); }
};

template<class sample>
struct TransformNone : public TransformNoneImpl<sample>
{

	typedef struct TransformNoneImpl<sample> INVERSE;
};

template<class sample, int RANGE>
struct TransformHp1ToRgb
{
	typedef sample SAMPLE;

	inlinehint static Triplet<SAMPLE> Apply(int v1, int v2, int v3)
	{ return Triplet<SAMPLE>(v1 + v2 - RANGE/2, v2, v3 + v2 - RANGE/2); }
};


template<class sample, int RANGE>
struct TransformHp1
{
	typedef sample SAMPLE;

	typedef struct TransformHp1ToRgb<SAMPLE,RANGE> INVERSE;
	inlinehint static Triplet<SAMPLE> Apply(int R, int G, int B)
	{
		Triplet<SAMPLE> hp1;
		hp1.v2 = SAMPLE(G);
		hp1.v1 = SAMPLE(R - G + RANGE/2);
		hp1.v3 = SAMPLE(B - G + RANGE/2);
		return hp1;
	}
};


template<class sample, int RANGE>
struct TransformHp2ToRgb
{
	typedef sample SAMPLE;

	inlinehint static Triplet<SAMPLE> Apply(int v1, int v2, int v3)
	{
		Triplet<SAMPLE> rgb;
		rgb.R  = SAMPLE(v1 + v2 - RANGE/2);          // new R
		rgb.G  = SAMPLE(v2);                     // new G				
		rgb.B  = SAMPLE(v3 + ((rgb.R + rgb.G) >> 1) - RANGE/2); // new B
		return rgb;
	}
};


template<class sample, int RANGE>
struct TransformHp2
{
	typedef sample SAMPLE;
	typedef struct TransformHp2ToRgb<SAMPLE,RANGE> INVERSE;
	inlinehint static Triplet<SAMPLE> Apply(int R, int G, int B)
	{
		return Triplet<SAMPLE>(R - G + RANGE/2, G, B - ((R+G )>>1) - RANGE/2);
	}
};



template<class sample, int RANGE>
struct TransformHp3ToRgb
{
	typedef sample SAMPLE;
	inlinehint static Triplet<SAMPLE> Apply(int v1, int v2, int v3)
	{
		int G = v1 - ((v3 + v2)>>2) + RANGE/4;
		Triplet<SAMPLE> rgb;
		rgb.R  = SAMPLE(v3 + G - RANGE/2); // new R
		rgb.G  = SAMPLE(G);             // new G				
		rgb.B  = SAMPLE(v2 + G - RANGE/2); // new B
		return rgb;
	}
};

template<class sample, int RANGE>
struct TransformHp3
{
	typedef sample SAMPLE;
	typedef struct TransformHp3ToRgb<SAMPLE,RANGE> INVERSE;
	inlinehint static Triplet<SAMPLE> Apply(int R, int G, int B)
	{
		Triplet<SAMPLE> hp3;		
		hp3.v2 = SAMPLE(B - G + RANGE/2);
		hp3.v3 = SAMPLE(R - G + RANGE/2);
		hp3.v1 = SAMPLE(G + ((hp3.v2 + hp3.v3)>>2)) - RANGE/4;
		return hp3;
	}
};




#endif
