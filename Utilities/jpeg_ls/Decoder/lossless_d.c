/* SPMG/JPEG-LS IMPLEMENTATION V.2.1
   =====================================
   These programs are Copyright (c) University of British Columbia. All rights reserved.
   They may be freely redistributed in their entirety provided that this copyright
   notice is not removed.  THEY MAY NOT BE SOLD FOR PROFIT OR INCORPORATED IN
   COMMERCIAL PROGRAMS WITHOUT THE WRITTEN PERMISSION OF THE COPYRIGHT HOLDER.
   Each program is provided as is, without any express or implied warranty,
   without even the warranty of fitness for a particular purpose.

   =========================================================
   THIS SOFTWARE IS BASED ON HP's implementation of jpeg-ls:
   =========================================================

   LOCO-I/JPEG-LS IMPLEMENTATION V.0.90
   -------------------------------------------------------------------------------
   (c) COPYRIGHT HEWLETT-PACKARD COMPANY, 1995-1999.
        HEWLETT-PACKARD COMPANY ("HP") DOES NOT WARRANT THE ACCURACY OR
   COMPLETENESS OF THE INFORMATION GIVEN HERE.  ANY USE MADE OF, OR
   RELIANCE ON, SUCH INFORMATION IS ENTIRELY AT USER'S OWN RISK.
        BY DOWNLOADING THE LOCO-I/JPEG-LS COMPRESSORS/DECOMPRESSORS
   ("THE SOFTWARE") YOU AGREE TO BE BOUND BY THE TERMS AND CONDITIONS
   OF THIS LICENSING AGREEMENT.
        YOU MAY DOWNLOAD AND USE THE SOFTWARE FOR NON-COMMERCIAL PURPOSES
   FREE OF CHARGE OR FURTHER OBLIGATION.  YOU MAY NOT, DIRECTLY OR
   INDIRECTLY, DISTRIBUTE THE SOFTWARE FOR A FEE, INCORPORATE THIS
   SOFTWARE INTO ANY PRODUCT OFFERED FOR SALE, OR USE THE SOFTWARE
   TO PROVIDE A SERVICE FOR WHICH A FEE IS CHARGED.
        YOU MAY MAKE COPIES OF THE SOFTWARE AND DISTRIBUTE SUCH COPIES TO
   OTHER PERSONS PROVIDED THAT SUCH COPIES ARE ACCOMPANIED BY
   HEWLETT-PACKARD'S COPYRIGHT NOTICE AND THIS AGREEMENT AND THAT
   SUCH OTHER PERSONS AGREE TO BE BOUND BY THE TERMS OF THIS AGREEMENT.
        THE SOFTWARE IS NOT OF PRODUCT QUALITY AND MAY HAVE ERRORS OR DEFECTS.
   THE JPEG-LS STANDARD IS STILL UNDER DEVELOPMENT. THE SOFTWARE IS NOT A
   FINAL OR FULL IMPLEMENTATION OF THE STANDARD.  HP GIVES NO EXPRESS OR
   IMPLIED WARRANTY OF ANY KIND AND ANY IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR PURPOSE ARE DISCLAIMED.
        HP SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL,
   OR CONSEQUENTIAL DAMAGES ARISING OUT OF ANY USE OF THE SOFTWARE.
   -------------------------------------------------------------------------------
*/

/* lossless_d.c --- the main pipeline which processes a scanline by doing
 *                prediction, context computation, context quantization,
 *                and statistics gathering. (for lossless mode)
 *
 * Initial code by Alex Jakulin,  Aug. 1995
 *
 * Modified and optimized: Gadiel Seroussi, October 1995
 *
 * Modified and added Restart marker and input tables by:
 * David Cheng-Hsiu Chu, and Ismail R. Ismail march 1999
 */

#include "global.h"
#include "bitio.h"

#include <stdio.h>
#include <math.h>


static int eor_limit;

/* Do Golomb-Rice statistics and DECODING for LOSSLESS images */
inline int lossless_regular_mode_d(int Q, int SIGN, int Px)
{
	int At, Bt, Nt, Errval, absErrval;
	int current, k;

	/* This function is called only for regular contexts. 
	   End_of_run context is treated separately */

	Nt = N[Q];
	At = A[Q];
	{
		/* Estimate k */
	    register nst = Nt;
	    for(k=0; nst < At; nst *=2, k++);
	}

	/* Get the number of leading zeros */
	absErrval = 0;
	do {
		int temp;

		temp = zeroLUT[reg >> 24];
		absErrval += temp;
		if (temp != 8) {
			FILLBUFFER(temp + 1);
			break;
		}
		FILLBUFFER(8);
	} while (1);

	if ( absErrval < limit ) {
		/* now add the binary part of the Rice code */
		if (k) {
			register unsigned long temp;
			absErrval <<= k;
			GETBITS(temp,k);
			absErrval += temp;
		}
	}
	else {
	    /* the original unary would have been too long:
	       (mapped value)-1 was sent verbatim */
		GETBITS(absErrval, qbpp);
		absErrval ++;
	}

	/* Do the Rice mapping */
	if ( absErrval & 1 ) {        /* negative */
		absErrval = (absErrval + 1) / 2;
		Errval = -absErrval;
	} else {
		absErrval /= 2;
		Errval = absErrval;
	}

	Bt = B[Q];

	if ( k==0 && (2*Bt <= -Nt) )
	{
		/* special case: see encoder side */
		Errval = -(Errval+1);
		absErrval = (Errval<0)? (-Errval):Errval;
	}

	/* center, clip if necessary, and mask final error */
	if ( SIGN == -1 ) {
	    Px -= C[Q];
	    clip(Px, alpha);
	    
#if defined(POW2)
	    /* this is valid if alpha is a power of 2 */
	    current = (Px - Errval)&(alpha-1);
#else
	    current = Px - Errval;
#endif
	}
	else {
	    Px += C[Q];
	    clip(Px,alpha);
	    
#if defined(POW2)
	    /* valid if alpha is a power of 2 */
	    current = (Px + Errval)&(alpha-1);
#else
	    current = Px + Errval;
#endif
	}


#if !defined(POW2)
	/* reduce mod alpha, for arbitrary alpha */
	if (current < 0)
		current += alpha;
	else if (current >= alpha)
		current -= alpha;
#endif


	/* update bias stats */
	B[Q] = (Bt += Errval);

	/* update Golomb-Rice stats */
	A[Q] += absErrval;


	/* check reset (joint for Rice-Golomb and bias cancelation) */
	if(Nt == reset) {
		N[Q] = (Nt >>= 1);
		A[Q] >>= 1;
		B[Q] = (Bt >>= 1);
	}


	/* Do bias estimation for NEXT pixel */
	N[Q] = (++Nt);
	if  ( Bt <= -Nt ) {

	    if (C[Q] > MIN_C)
			--C[Q];

	    Bt = (B[Q] += Nt);

	    if ( Bt <= -Nt ) 
			B[Q] = -Nt+1;

	} else if ( Bt > 0 ) {

	    if (C[Q] < MAX_C)
			++C[Q];

	    Bt = (B[Q] -= Nt);

	    if ( Bt > 0 )
			B[Q] = 0;
	}

	return current;
}






/* Do end of run DECODING for LOSSLESS images */
inline pixel lossless_end_of_run_d(pixel Ra, pixel Rb, int RItype)
{

	int Ix,
		Errval,
		absErrval,
		MErrval,
		k,
		Q,
		oldmap, 
		Nt,
		At;

		Q = EOR_0 + RItype;
		Nt = N[Q], 
		At = A[Q];

		if ( RItype )
			At += Nt/2;

		/* Estimate k */
		for(k=0; Nt < At; Nt *=2, k++);

		/* read and decode the Golomb code */
		/* Get the number of leading zeros */
		MErrval = 0;
		do {
			int temp;

			temp = zeroLUT[reg >> 24];
			MErrval += temp;
			if (temp != 8) {
				FILLBUFFER(temp + 1);
				break;
			}
			FILLBUFFER(8);
		} while (1);

		eor_limit = limit - limit_reduce;

		if ( MErrval < eor_limit ) {
			/* now add the binary part of the Golomb code */
			if (k) {
				register unsigned long temp;
				MErrval <<= k;
				GETBITS(temp,k);
				MErrval += temp;
			}
		}
		else {
			/* the original unary would have been too long:
				(mapped value)-1 was sent verbatim */
			GETBITS(MErrval, qbpp);
			MErrval ++;
		}

		oldmap = ( k==0 && (RItype||MErrval) && (2*B[Q]<Nt));
		/* 
			Note: the Boolean variable 'oldmap' is not 
			identical to the variable 'map' in the
			JPEG-LS draft. We have
			oldmap = (qdiff<0) ? (1-map) : map;
		*/

		MErrval += ( RItype + oldmap );

		if ( MErrval & 1 ) { /* negative */
			Errval = oldmap - (MErrval+1)/2;
			absErrval = -Errval-RItype;
			B[Q]++;
		}
		else { /* nonnegative */
			Errval = MErrval/2;
			absErrval = Errval-RItype;
		}


		if ( Rb < Ra )
#    ifdef POW2
			Ix = ( Rb - Errval ) & (alpha-1);
#    else
			Ix = Rb - Errval;
#    endif
		else   /* includes case a==b */
#    ifdef POW2
			Ix = ( Rb + Errval ) & (alpha-1);
#    else
			Ix = Rb + Errval;
#    endif


#if !defined(POW2)
		/* reduce mod alpha, for arbitrary alpha */
		if (Ix < 0)
			Ix += alpha;
		else if (Ix >= alpha)
			Ix -= alpha;
#endif

		/* update stats */
		A[Q] += absErrval;
		if (N[Q] == reset) {
			N[Q] >>= 1;
			A[Q] >>= 1;
			B[Q] >>= 1;
		}

		N[Q]++;  /* for next pixel */

		return Ix;			
}






/* For line and plane interleaved mode in LOSSLESS mode */

int lossless_undoscanline(	pixel *psl,			/* previous scanline */
							pixel *sl,			/* current scanline */
							int no, int color)	/* number of values in it */
/*** watch it! actual pixels in the scan line are numbered 1 to no .
     pixels with indices < 1 or > no are dummy "border" pixels  */
{
	int i, psfix;
	pixel Ra, Rb, Rc, Rd;
	int SIGN;
	int cont;

	psfix = 0;


	/**********************************************/
	/* Do for all pixels in the row in 8-bit mode */
	/**********************************************/
	if (bpp16==FALSE)
	{

		Rc = psl[0];
		Rb = psl[1];
		Ra = sl[0];

		i = 1;
		do {
			pixel Px;

			Rd = psl[i + 1];

			/* Quantize the gradient */
			cont =  vLUT[0][Rd - Rb + LUTMAX8] +
					vLUT[1][Rb - Rc + LUTMAX8] +
					vLUT[2][Rc - Ra + LUTMAX8];

			if ( cont == 0 )
			{
		    /*********** RUN STATE **********/

				register int n, m;

				/* get length of the run */
				/* arg is # of pixels left */
				m = n = process_run_dec(no-i+1, color); 

				if ( m > 0 )  {  /* run of nonzero length, otherwise
									we go directly to the end-of-run 
									state */
					do {
						sl[i++] = Ra;
					} while(--n > 0);

					if (i > no)
						/* end of line */
						return 0;

					/* update context pixels */
				    Rb = psl[i];
				    Rd = psl[i + 1];
				}

				/* Do end of run encoding for LOSSLESS images */
				Ra = lossless_end_of_run_d(Ra, Rb, (Ra==Rb));
	
			}       /* Run state block */ 
			else 
			{
			/************ REGULAR CONTEXT **********/

				predict(Rb, Ra, Rc);

				/* map symmetric contexts */
				cont = classmap[cont];

				if (cont < 0) 
				{
					SIGN = -1;
					cont = -cont;
				}
				else
					SIGN = +1;

				/* decode a Rice code of a given context */
				Ra = lossless_regular_mode_d(cont, SIGN, Px);

			}

			sl[i] = Ra;
			Rc = Rb;
			Rb = Rd;
			++i;

		} while (i <= no);

	}
	else
	/***********************************************/
	/* Do for all pixels in the row in 16-bit mode */
	/***********************************************/
	{

		Rc = ENDIAN16(psl[0]);
		Rb = ENDIAN16(psl[1]);
		Ra = ENDIAN16(sl[0]);

		i = 1;
		do {

			pixel Px;

			Rd = ENDIAN16(psl[i + 1]);

			/* Quantize the gradient */
			{
				register int diff;

				/* Following segment assumes that T3 <= LUTMAX16 */
				/* This condition should have been checked when the
					lookup tables were built */
				diff = Rd - Rb;
				if (diff < 0)
					cont = (diff > -LUTMAX16) ? vLUT[0][diff + LUTMAX16] : 7*CREGIONS*CREGIONS;
				else 
					cont = (diff < LUTMAX16) ? vLUT[0][diff + LUTMAX16] : 8*CREGIONS*CREGIONS;

				diff = Rb - Rc;
				if (diff < 0)
					cont += (diff > -LUTMAX16) ? vLUT[1][diff + LUTMAX16] : 7*CREGIONS;
				else 
					cont += (diff < LUTMAX16) ? vLUT[1][diff + LUTMAX16] : 8*CREGIONS;
				
				diff = Rc - Ra;
				if (diff < 0)
					cont += (diff > -LUTMAX16) ? vLUT[2][diff + LUTMAX16] : 7;
				else 
					cont += (diff < LUTMAX16) ? vLUT[2][diff + LUTMAX16] : 8;
			}

			if ( cont == 0 ) {

		    /********** RUN STATE **********/

				register int n, m;

				/* get length of the run */
				/* arg is # of pixels left */
				m = n = process_run_dec(no-i+1, color); 

				if ( m > 0 )  {  /* run of nonzero length, otherwise
									we go directly to the end-of-run 
									state */
					do {
						sl[i++] = ENDIAN16(Ra);
					}	while(--n > 0);

					if (i > no)
						/* end of line */
						return 0;

					/* update context pixels */
				    Rb = ENDIAN16(psl[i]);
				    Rd = ENDIAN16(psl[i + 1]);
				}

			
				/* Do end of run encoding for LOSSLESS images */
				Ra = lossless_end_of_run_d(Ra, Rb, (Ra==Rb));
	
			}
			else 
			{
			/********** REGULAR CONTEXT **********/

				predict(Rb, Ra, Rc);

				/* map symmetric contexts */
				cont = classmap[cont];

				if (cont < 0) 
				{
					SIGN = -1;
					cont = -cont;
				}
				else
					SIGN = +1;

				/* decode a Rice code of a given context */
				Ra = lossless_regular_mode_d(cont, SIGN, Px);

			}

			sl[i] = ENDIAN16(Ra);
			Rc = Rb;
			Rb = Rd;
			++i;

		} while (i <= no);

	} /* End "if 8/16 bit" */

	return 0;
}







/* For DEOCODING pixel interleavde mode for LOSSLESS images */

int lossless_undoscanline_pixel(pixel *psl,		/* previous scanline */
								pixel *sl,		/* current scanline */
								int no)			/* number of values in it */
/*** watch it! actual pixels in the scan line are numbered 1 to no .
     pixels with indices < 1 or > no are dummy "border" pixels  */
{
	int i, psfix, n_c, color, enter_run=0, break_run, was_in_run = 0,
	    test_run;
	pixel Ra, Rb, Rc, Rd;
	pixel c_aa[MAX_COMPONENTS],
	      c_bb[MAX_COMPONENTS],
	      c_cc[MAX_COMPONENTS],
	      c_dd[MAX_COMPONENTS],
	      c_xx[MAX_COMPONENTS];


	int	SIGN;
	int cont,c_cont[MAX_COMPONENTS];

	psfix = 0;

	/**********************************************/
	/* Do for all pixels in the row in 8-bit mode */
	/**********************************************/
	if (bpp16==FALSE)
	{

		for (n_c=0; n_c<components; n_c++) {
			c_cc[n_c] = psl[n_c];
			c_bb[n_c] = psl[components+n_c];
			c_aa[n_c] = sl[n_c];
		}

		i = components;
		color = -1;

		do {
			pixel Px;

			if (!was_in_run) color = (color+1)%components;
			else color = 0;

			if (color == 0)

				for (n_c=0;n_c<components;n_c++) {
					c_dd[n_c] = psl[i + components + n_c];

					/* Quantize the gradient */		   
					c_cont[n_c] =	vLUT[0][c_dd[n_c] - c_bb[n_c] + LUTMAX8] +
									vLUT[1][c_bb[n_c] - c_cc[n_c] + LUTMAX8] +
									vLUT[2][c_cc[n_c] - c_aa[n_c] + LUTMAX8];
				}

			Ra=c_aa[color];
			Rb=c_bb[color];
			Rc=c_cc[color];
			Rd=c_dd[color];
			cont=c_cont[color];

			enter_run = was_in_run = test_run = 0;
		
			if (color == 0) {
				test_run = 1;
				for (n_c=0;n_c<components;n_c++)
					if (c_cont[n_c]!=0) {
						test_run=0;
						break;
					}
			}

			if ( test_run ) {

		    /********** RUN STATE *********/

				register int n, m;

				enter_run = was_in_run = 1;

				/* get length of the run */
				/* arg is # of pixels left */
				m = n = process_run_dec((no+components-1-i+1)/components, 0); 

				if ( m > 0 )  {  /* run of nonzero length, otherwise
									we go directly to the end-of-run 
									state */
					do {
						for (n_c=0;n_c<components;n_c++) {
							sl[i++] = c_aa[n_c];
						}
					} while(--n > 0);

					if (i > no+components-1)
					    /* end of line */
					    return 0;

					/* update context pixels */
					for (n_c=0;n_c<components;n_c++) {
			    		c_bb[n_c] = psl[i+n_c];
			    		c_dd[n_c] = psl[i+components+n_c];
					}
				}

				/* here we handle the "end-of-run" stat */

				for (n_c=0;n_c<components;n_c++) {
				/* The end of run is processed for each component */
					Ra = c_aa[n_c];
					Rb = c_bb[n_c];
					c_aa[n_c] = c_xx[n_c] = lossless_end_of_run_d(Ra, Rb, 0);
				}       /* Components loop */

			}       /* Run state block */
			else {

			/******* REGULAR CONTEXT *******/

				predict(Rb, Ra, Rc);
		
			    cont = classmap[cont];
				if (cont < 0) 
				{
					SIGN = -1;
					cont = -cont;
				}
				else
					SIGN = +1;

				/* decode a Rice code of a given context */
				c_aa[color] = Ra = lossless_regular_mode_d(cont, SIGN, Px);
			}

			if (!was_in_run) {
				sl[i] = Ra;
				c_cc[color] = Rb;
				c_bb[color] = Rd;
				i++;
			}
			else {
				for (n_c=0;n_c<components;n_c++) {
					sl[i+n_c] = c_aa[n_c];
					c_cc[n_c] = c_bb[n_c];
					c_bb[n_c] = c_dd[n_c];
				}
				i+=components;
			}
			
		} while (i <= (no+components-1));

	}
	else
	/***********************************************/
	/* Do for all pixels in the row in 16-bit mode */
	/***********************************************/
	{

		for (n_c=0; n_c<components; n_c++) {
			c_cc[n_c] = ENDIAN16(psl[n_c]);
			c_bb[n_c] = ENDIAN16(psl[components+n_c]);
			c_aa[n_c] = ENDIAN16(sl[n_c]);
		}

		i = components;
		color = -1;

		do {
			pixel Px;

			if (!was_in_run) color = (color+1)%components;
			else color = 0;

			if (color == 0)
				for (n_c=0;n_c<components;n_c++) {

					c_dd[n_c] = ENDIAN16(psl[i + components + n_c]);

					/* Quantize the gradient */
					{
						register int diff;

						/* Following segment assumes that T3 <= LUTMAX16 */
						/* This condition should have been checked when the
						lookup tables were built */
						diff = c_dd[n_c] - c_bb[n_c];
						if (diff < 0)
							c_cont[n_c] = (diff > -LUTMAX16) ? vLUT[0][diff + LUTMAX16] : 7*CREGIONS*CREGIONS;
						else 
							c_cont[n_c] = (diff < LUTMAX16) ? vLUT[0][diff + LUTMAX16] : 8*CREGIONS*CREGIONS;

						diff = c_bb[n_c] - c_cc[n_c];
						if (diff < 0)
							c_cont[n_c] += (diff > -LUTMAX16) ? vLUT[1][diff + LUTMAX16] : 7*CREGIONS;
						else 
							c_cont[n_c] += (diff < LUTMAX16) ? vLUT[1][diff + LUTMAX16] : 8*CREGIONS;

						diff = c_cc[n_c] - c_aa[n_c];
						if (diff < 0)
							c_cont[n_c] += (diff > -LUTMAX16) ? vLUT[2][diff + LUTMAX16] : 7;
						else 
							c_cont[n_c] += (diff < LUTMAX16) ? vLUT[2][diff + LUTMAX16] : 8;
					}
				}

			Ra=c_aa[color];
			Rb=c_bb[color];
			Rc=c_cc[color];
			Rd=c_dd[color];
			cont=c_cont[color];

			enter_run = was_in_run = test_run = 0;
		
			if (color == 0) {
				test_run = 1;
				for (n_c=0;n_c<components;n_c++)
					if (c_cont[n_c]!=0) {
						test_run=0;
						break;
					}
			}

			if ( test_run ) {

		    /********* RUN STATE *********/

				register int n, m;

				enter_run = was_in_run = 1;

				/* get length of the run */
				/* arg is # of pixels left */
				m = n = process_run_dec((no+components-1-i+1)/components, 0); 

				if ( m > 0 )  {  /* run of nonzero length, otherwise
									we go directly to the end-of-run 
									state */
					do {
						for (n_c=0;n_c<components;n_c++) {
							sl[i++] = ENDIAN16(c_aa[n_c]);
						}
					} while(--n > 0);

					if (i > no+components-1)
						/* end of line */
						return 0;

					/* update context pixels */
					for (n_c=0;n_c<components;n_c++) {
			    		c_bb[n_c] = ENDIAN16(psl[i+n_c]);
			    		c_dd[n_c] = ENDIAN16(psl[i+components+n_c]);
					}
				}

				/* here we handle the "end-of-run" state */
				for (n_c=0;n_c<components;n_c++) {
					/* The end of run is processed for each component */
					Ra = c_aa[n_c];
					Rb = c_bb[n_c];

					c_aa[n_c] = c_xx[n_c] = lossless_end_of_run_d(Ra, Rb, 0);
				}       /* Components loop */

			}       /* Run state block */
			else {

			/******** REGULAR CONTEXT ********/

				predict(Rb, Ra, Rc);
			
				cont = classmap[cont];
			
				if (cont < 0) 
				{
					SIGN = -1;
					cont = -cont;
				}
				else
					SIGN = +1;

				/* decode a Rice code of a given context */
				c_aa[color] = Ra = lossless_regular_mode_d(cont, SIGN, Px);

			}

			if (!was_in_run) {
				sl[i] = ENDIAN16(Ra);
				c_cc[color] = Rb;
				c_bb[color] = Rd;
				i++;
			}
			else {
				for (n_c=0;n_c<components;n_c++) {
				sl[i+n_c] = ENDIAN16(c_aa[n_c]);
				c_cc[n_c] = c_bb[n_c];
				c_bb[n_c] = c_dd[n_c];
				}
				i+=components;
			}

		} while (i <= (no+components-1));

	} /* ends "if 8/16 bit */

	return 0;
}
