// 
// (C) Jan de Vaan 2007-2009, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#ifndef CHARLS_CONTEXT
#define CHARLS_CONTEXT


#define MIN_C -128
#define MAX_C 127

//
// JlsContext: a JPEG-LS context with it's current statistics.
//
struct JlsContext
{
public:
	JlsContext() 
	{}

 	JlsContext(LONG a) :
		A(a),
		B(0),
		C(0),
		N(1)
	{
	}

	LONG A;
	LONG B;
	LONG C;
	LONG N;

	inlinehint LONG GetErrorCorrection(LONG k) const
	{
		if (k != 0)
			return 0;

		return BitWiseSign(2 * B + N - 1);
	}


	inlinehint void UpdateVariables(LONG Errval, LONG NEAR, LONG NRESET)
	{
		ASSERT(N != 0);

		B = B + Errval * (2 * NEAR + 1); 
		A = A + abs(Errval);
		
		ASSERT(A < 65536 * 256);
		ASSERT(abs(B) < 65536 * 256);

		if (N == NRESET) 
		{
			A = A >> 1;
			B = B >> 1;
			N = N >> 1;
		}

		N = N + 1;

		if (B <= - N) 
		{
			B = MAX(-N + 1, B + N);
			if (C > MIN_C)
			{
				C--;
			}
		} 
		else if (B > 0) 
		{
			B = MIN(B - N, 0);				
			if (C < MAX_C) 
			{
				C++;
			}

		}
		ASSERT(N != 0);
	}



	inlinehint LONG GetGolomb() const
	{
		LONG Ntest	= N;
		LONG Atest	= A;
		LONG k = 0;
		for(; (Ntest << k) < Atest; k++) 
		{ 
			ASSERT(k <= 32); 
		};
		return k;
	}

};

#endif
