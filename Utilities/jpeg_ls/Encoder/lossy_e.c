/* SPMG/JPEG-LS IMPLEMENTATION V.2.1
   =====================================
   These programs are Copyright (c) University of British Columbia. All rights reserved.
   They may be freely redistributed in their entirety provided that this copyright
   notice is not removed. THEY MAY NOT BE SOLD FOR PROFIT OR INCORPORATED IN
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

/* lossy_e.c ---	the main pipeline which processes a scanline by doing
 *              prediction, context computation, context quantization,
 *              and statistics gathering. (for LOSSY compression)
 *
 * Initial code by Alex Jakulin,  Aug. 1995
 *
 * Modified and optimized: Gadiel Seroussi, October 1995
 *
 * Modified and added Restart marker and input tables by:
 * David Cheng-Hsiu Chu, and Ismail R. Ismail march 1999
 *
 */

#include <stdio.h>
#include <math.h>

#include "global.h"
#include "bitio.h"


/*byte getk[65][3000];
int clipPx[510];*/

static int eor_limit;


/* Do Golomb statistics and ENCODING for LOSSY images */
inline void lossy_regular_mode(int Q, int SIGN, int Px, pixel *xp)
{
	int At, Bt, Nt, absErrval, Errval, MErrval,
	    qErrval, iqErrval, Rx,
	    Ix = *xp;                          /* current pixel */
	int unary;
	int temp;
	byte k;


	Nt = N[Q];
	At = A[Q];
	/* Estimate k - Golomb coding variable computation (A.5.1) */    
	{
	    register nst = Nt;
		for(k=0; nst < At; nst<<=1, k++);
	}


	/* Prediction correction (A.4.2), compute prediction error (A.4.3)
	   , and error quantization (A.4.4) */

	Px = Px + (SIGN) * C[Q];
	clip(Px,alpha);
	Errval = SIGN * (Ix - Px);
	qErrval = qdiv[Errval];
	iqErrval = qmul[qErrval];
	Rx = Px + SIGN * iqErrval;

	clip(Rx, alpha);
	*xp = Rx;					/* store reconstructed pixel in scan line */


	/* Modulo reduction of predication error (A.4.5) */
	if ( qErrval < 0 )
		qErrval += qbeta;			/* qErrval is now in [0..qbeta-1] */


	/* Do Rice mapping and compute magnitude of diff */
	Bt = B[Q];


	/* Error Mapping (A.5.2) */
	temp = ( k==0 && NEAR==0 && ((Bt<<1) <= -Nt) );
	if (qErrval >= ceil_half_qbeta) {
		qErrval -= qbeta;
		absErrval = -qErrval;
		MErrval = 2*absErrval - 1 - temp;
	} else {
		absErrval = qErrval;
		MErrval = 2*qErrval + temp;
	}


	/* update bias stats (after correction of the difference) (A.6.1) */

	Errval = qmul[qErrval];         /* convert back to alphabet space */

	B[Q] = (Bt += Errval);

	/* update Golomb stats */
	A[Q] += absErrval;

	/* check for reset */
	if (Nt == reset) {
	/* reset for Golomb and bias cancelation at the same time */
		N[Q] = (Nt >>= 1);
		A[Q] >>= 1;
		B[Q] = (Bt >>= 1);
	}


	/* Do bias estimation for NEXT pixel */
	/* Bias cancelation tries to put error in (-1,0] (A.6.2)*/
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


	/* Actually output the code: Mapped Error Encoding (A.5.3) */
	unary = MErrval >> k;
	if ( unary < limit ) {
	    put_zeros(unary);
	    putbits((1 << k) + (MErrval & ((1 << k) - 1)), k + 1);
	}
	else {
	    put_zeros(limit);
	    putbits((1<<qbpp) + MErrval - 1, qbpp+1);
	}

}




/* Do end of run encoding for LOSSY images -  returns reconstructed value of Ix */
pixel lossy_end_of_run(pixel Ra, pixel Rb, pixel Ix, int RItype)
{  
	int qErrval, iqErrval, xpr,
		MErrval,
		Q,
		absErrval,
		oldmap, 
		k,
		Nt,
		At,
		Errval;
	int Rx;			/* reconstructed pixel */
	int unary;

	Q = EOR_0 + RItype;
	Nt = N[Q]; 
	At = A[Q];

	if (RItype) {
		Errval = Ix - (xpr = Ra);
		At += Nt/2;
	}
	else {
		Errval = Ix - (xpr = Rb);
		if ( Rb < Ra )
			Errval = -Errval;
	}

	qErrval = qdiv[Errval];
	iqErrval = qmul[qErrval];

	if ( RItype || (Rb >= Ra) ) 
		Rx = xpr + iqErrval;
	else
		Rx = xpr - iqErrval;

	clip(Rx,alpha);    /* reconstructed pixel */
	Ix = Rx;

	/* Estimate k */
	for(k=0; Nt < At; Nt *=2, k++);

	if (qErrval < 0)
		qErrval += qbeta;

	if( qErrval >= ceil_half_qbeta )
		qErrval -= qbeta;
			
	oldmap = ( k==0 && qErrval && 2*B[Q]<Nt );
			
	/* 
		Note: the Boolean variable 'oldmap' is not 
		identical to the variable 'map' in the
		JPEG-LS draft. We have
		oldmap = (qErrval<0) ? (1-map) : map;
	*/

	/* Error mapping for run-interrupted sample (Figure A.22) */
	if( qErrval < 0) {
		MErrval = -2*qErrval-1-RItype+oldmap;
		B[Q]++; 
	}
	else
		MErrval = 2*qErrval-RItype-oldmap;
			   
	absErrval = (MErrval+1-RItype)/2;

	/* update stats */
	A[Q] += absErrval;
	if (N[Q] == reset) {
		N[Q] >>= 1;
		A[Q] >>= 1;
		B[Q] >>= 1;
	}

	N[Q]++; /* for next pixel */

	/* Do the actual Golomb encoding: */
	eor_limit = limit - limit_reduce;
	unary = MErrval >> k;
	if ( unary < eor_limit ) {
		put_zeros(unary);
		putbits((1 << k) + (MErrval & ((1 << k) - 1)), k + 1);
	}
	else {
		put_zeros(eor_limit);
		putbits((1<<qbpp) + MErrval-1, qbpp+1);
	}

	return Ix;
}






/* For line and plane interleaved mode in LOSSY mode */

void lossy_doscanline(pixel *psl,          /* previous scanline */
		      pixel *sl,           /* current scanline */
		      int no, int color)   /* number of values in it */

/*** watch it! actual pixels in the scan line are numbered 1 to no .
     pixels with indices < 1 or > no are dummy "border" pixels  */
{
	int i;
	pixel Ra, Rb, Rc, Rd,           /* context pixels */
	      Ix,	                /* current pixel */
	      Px; 		        /* predicted current pixel */
	int Rx;			        /* reconstructed current pixel */

	int SIGN;		    /* sign of current context */
	int cont;		    /* context */
	int unary;
	int RItype;

	i = 1;    /* pixel indices in a scan line go from 1 to no */

	/**********************************************/
	/* Do for all pixels in the row in 8-bit mode */
	/**********************************************/

	if (bpp16==FALSE) {
		
		Rc = psl[0];
		Rb = psl[1];
		Ra = sl[0];

		/*	For 8-bit Image */
	
		do {
			int RUNcnt;

			Ix = sl[i];
			Rd = psl[i + 1];

			/* Context determination */

			/* Quantize the gradient */
			/* partial context number: if (b-e) is used then its 
			   contribution is added after determination of the run state.
			   Also, sign flipping, if any, occurs after run
			   state determination */

			cont =  vLUT[0][Rd - Rb + LUTMAX8] +
					vLUT[1][Rb - Rc + LUTMAX8] +
					vLUT[2][Rc - Ra + LUTMAX8];
				

			if ( cont == 0 ) {      /* Run state? */
			/*************** RUN STATE ***************************/

				register delta = Ix - Ra;
				RUNcnt = 0;

				if ( delta <= NEAR && delta >= negNEAR )
				{
					while ( 1 )
					{
						++RUNcnt;

						sl[i] = Ra;

						if (++i > no) {	
							/* Run-lenght coding when reach end of line (A.7.1.2) */
							process_run(RUNcnt, EOLINE, color);
							return;	 /* end of line */
						}

						Ix = sl[i];

						delta = Ix-Ra;
						if ( delta > NEAR || delta < negNEAR )  /*  Run is broken */
						{
							Rd = psl[i + 1];
							Rb = psl[i];
							break;  /* out of while loop */
						}
						/* Run continues */
					}
				}

				/* we only get here if the run is broken by
				   a non-matching symbol */

				/* Run-lenght coding when end of line not reached (A.7.1.2) */
				process_run(RUNcnt,NOEOLINE, color);


				/* This is the END_OF_RUN state */
				RItype = ((Rb-Ra)<=NEAR && (Rb-Ra)>=negNEAR);
				Ix = lossy_end_of_run(Ra, Rb, Ix, RItype);
				
			}  
			else {
			
			/*************** REGULAR CONTEXT *******************/

				predict(Rb, Ra, Rc);

				/* do symmetric context merging */
				cont = classmap[cont];

				if (cont<0) {
					SIGN=-1;
					cont = -cont;
				} else
					SIGN=+1;

				/* output a rice code */
				lossy_regular_mode(cont, SIGN, Px, &Ix);
			}

			/* context for next pixel: */
			sl[i] = Ix;
			Ra = Ix;
			Rc = Rb;
			Rb = Rd;
		} while (++i <= no);

	} else { /* 16 bit mode instead of 8 */

		/***********************************************/
		/* Do for all pixels in the row in 16-bit mode */
		/***********************************************/

		Rc = ENDIAN16(psl[0]);
		Rb = ENDIAN16(psl[1]);
		Ra = ENDIAN16(sl[0]);

		/*	For 16-bit Image */
	
		do {
			int RUNcnt;

			Ix = ENDIAN16(sl[i]);
			Rd = ENDIAN16(psl[i + 1]);

			/* Context determination */

			/* Quantize the gradient */
			/* partial context number: if (b-e) is used then its 
				contribution is added after determination of the run state.
				Also, sign flipping, if any, occurs after run
				state determination */

			{
				register int diff;

				/* Following segment assumes that Sc <= LUTMAX16 */
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
				
			if ( cont == 0 ) {      /* Run state? */
		/*************** RUN STATE ***************************/

				register delta = Ix - Ra;
				RUNcnt = 0;

				if ( delta <= NEAR && delta >= negNEAR )
				{
					while ( 1 )
					{
						++RUNcnt;
	
						sl[i] = ENDIAN16(Ra);
	
						if (++i > no) {	
							/* Run-lenght coding when reach end of line (A.7.1.2) */
							process_run(RUNcnt, EOLINE, color);
							return;	 /* end of line */
						}
	
						Ix = ENDIAN16(sl[i]);
	
						delta = Ix-Ra;
						if ( delta > NEAR || delta < negNEAR )  /*  Run is broken */
						{
							Rd = ENDIAN16(psl[i + 1]);
							Rb = ENDIAN16(psl[i]);
							break;  /* out of while loop */
						}
						/* Run continues */
					}
				}
	
				/* we only get here if the run is broken by
					a non-matching symbol */

				/* Run-lenght coding when end of line not reached (A.7.1.2) */
				process_run(RUNcnt,NOEOLINE, color);

				/* This is the END_OF_RUN state */
				RItype = ((Rb-Ra)<=NEAR && (Rb-Ra)>=negNEAR);
				Ix = lossy_end_of_run(Ra, Rb, Ix, RItype);

			}
			else {
			
			/*************** REGULAR CONTEXT *******************/

				predict(Rb, Ra, Rc);

				/* do symmetric context merging */
				cont = classmap[cont];

				if (cont<0) {
					SIGN=-1;
					cont = -cont;
				} else
					SIGN=+1;

				/* output a rice code */
				lossy_regular_mode(cont, SIGN, Px, &Ix);
			}

			/* context for next pixel: */
			sl[i] = ENDIAN16(Ix);
			Ra = Ix;
			Rc = Rb;
			Rb = Rd;
		} while (++i <= no);

	} /* for "if" 16 or 8 bit mode */

}






/* For pixel interleavde mode for LOSSY encoding */

void lossy_doscanline_pixel(pixel *psl,            /* previous scanline */
							pixel *sl,             /* current scanline */
							int no)                /* number of values in it */
/*** watch it! actual pixels in the scan line are numbered 1 to no .
     pixels with indices < 1 or > no are dummy "border" pixels  */
{
	int i,n_c, enter_run=0, break_run, was_in_run=0, test_run;
	int color;		/* Index to the component, 0..COMPONENTS-1 */
	pixel c_aa[MAX_COMPONENTS],
	      c_bb[MAX_COMPONENTS],
	      c_cc[MAX_COMPONENTS],
	      c_dd[MAX_COMPONENTS],
	      c_xx[MAX_COMPONENTS],
	      Ra, Rb, Rc, Rd,	/* context pixels */
	      Ix,				/* current pixel */
	      Px;				/* predicted current pixel */
	int SIGN;		    /* sign of current context */
	int cont,c_cont[MAX_COMPONENTS];		    /* context */


	if (bpp16==FALSE)
	{
	/**********************************************/
	/* Do for all pixels in the row in 8-bit mode */
	/**********************************************/

		for (n_c=0; n_c<components; n_c++) {
			c_cc[n_c] = psl[n_c];
			c_bb[n_c] = psl[components+n_c];
			c_aa[n_c] = sl[n_c];
		}

		i = components;    /* pixel indices in a scan line go from COMPONENTS to no */
		color = -1;

		do {
			int RUNcnt;

			if (!was_in_run) color = (color+1)%components;
			else color = 0;
			Ix = sl[i];

			for (n_c=0;n_c<components;n_c++)
				c_xx[n_c] = sl[i+n_c];

			if (color == 0)
			for (n_c=0;n_c<components;n_c++) {

				c_dd[n_c] = psl[i+components+n_c];

				/* Context determination */

				/* Quantize the gradient */
				/* partial context number: if (b-e) is used
					then its contribution is added after
					determination of the run state.
					Also, sign flipping, if any, occurs after run
					state determination */

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
			/*************** RUN STATE ***************************/

				int delta[MAX_COMPONENTS];

				enter_run = was_in_run = 1;
				for (n_c=0;n_c<components;n_c++) {
					delta[n_c] = sl[i+n_c] - c_aa[n_c];
					if (delta[n_c]>NEAR || delta[n_c]<negNEAR) enter_run=0;
				}
				RUNcnt = 0;

				if (enter_run)
				{
					while ( 1 ) {
						++RUNcnt;

						for (n_c=0; n_c<components; n_c++) 
							sl[i+n_c] = c_aa[n_c];

						if((i=i+components)>(no+components-1)){	
							process_run(RUNcnt, EOLINE, 0);
							return;	 /* end of line */
						}

						for (n_c=0;n_c<components;n_c++) 
							c_xx[n_c] = sl[i+n_c];

						break_run=0;
						for (n_c=0;n_c<components;n_c++) {
							delta[n_c] = c_xx[n_c] - c_aa[n_c];
							if(delta[n_c]>NEAR || delta[n_c]<negNEAR) break_run=1;
						}

						if ( break_run )
						{
							for(n_c=0; n_c<components; n_c++){
								c_dd[n_c] = psl[i+components+n_c];
								c_bb[n_c] = psl[i+n_c];
							}
							break;  /* out of while loop */
						}
						/* Run continues */
					}
				}

				/* we only get here if the run is broken by
					a non-matching symbol */

				process_run(RUNcnt, NOEOLINE, 0);

				/* This is the END_OF_RUN state */

				for (n_c=0;n_c<components;n_c++) {
					/* The end of run is done for each component */
					Ix = c_xx[n_c];
					Rb = c_bb[n_c];
					Ra = c_aa[n_c];

					/* Handle two special EOR states */
					c_xx[n_c] = Ix = lossy_end_of_run(Ra, Rb, Ix, 0);
					
				}   /* loop for components */

			}           /* Run state block */
			else {
			
			/*************** REGULAR CONTEXT *******************/

				predict(Rb, Ra, Rc);
				cont = classmap[cont];
				
				if (cont<0)
				{	SIGN=-1;
					cont=-cont;
				}
				else
					SIGN=1;

				/* output a rice code */
				lossy_regular_mode(cont, SIGN, Px, &Ix);
			}

			/* context for next pixel: */
			if (!was_in_run) {

				c_aa[color] = Ix; 
				sl[i] = Ix;   /* store reconstructed x */

				c_cc[color] = Rb;
				c_bb[color] = Rd;
				i++;
			}
			else {
				for(n_c=0;n_c<components;n_c++) {
					c_aa[n_c] = c_xx[n_c];
					sl[i+n_c] = c_xx[n_c];

					c_cc[n_c] = c_bb[n_c];
					c_bb[n_c] = c_dd[n_c];
				}
		        i += components;
			}

		} while (i <= (no+components-1));
	
	} else

	{

	/***********************************************/
	/* Do for all pixels in the row in 16-bit mode */
	/***********************************************/

		for (n_c=0; n_c<components; n_c++) {
			c_cc[n_c] = ENDIAN16(psl[n_c]);
			c_bb[n_c] = ENDIAN16(psl[components+n_c]);
			c_aa[n_c] = ENDIAN16(sl[n_c]);
		}

		i = components;    /* pixel indices in a scan line go from COMPONENTS to no */
		color = -1;

		do {
			int RUNcnt;

			if (!was_in_run) color = (color+1)%components;
			else color = 0;
			Ix = ENDIAN16(sl[i]);

			for (n_c=0;n_c<components;n_c++)
				c_xx[n_c] = ENDIAN16(sl[i+n_c]);

			if (color == 0)
			for (n_c=0;n_c<components;n_c++) {

				c_dd[n_c] = ENDIAN16(psl[i+components+n_c]);

				/* Context determination */

				/* Quantize the gradient */
				/* partial context number: if (b-e) is used
					then its contribution is added after
					determination of the run state.
					Also, sign flipping, if any, occurs after run
					state determination */
				{
				register int diff;

				/* Following segment assumes that Sc <= LUTMAX16 */
				/* This condition should have been checked when the
			   l	ookup tables were built */
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
			/*************** RUN STATE ***************************/

				int delta[MAX_COMPONENTS];

				enter_run = was_in_run = 1;
				for (n_c=0;n_c<components;n_c++) {
					delta[n_c] = ENDIAN16(sl[i+n_c]) - c_aa[n_c];
					if (delta[n_c]>NEAR || delta[n_c]<negNEAR) enter_run=0;
				}
				RUNcnt = 0;

				if (enter_run)
				{
					while ( 1 ) {
						++RUNcnt;

						for (n_c=0; n_c<components; n_c++) 
							sl[i+n_c] = ENDIAN16(c_aa[n_c]);

						if((i=i+components)>(no+components-1)){	
							process_run(RUNcnt, EOLINE, 0);
							return;	 /* end of line */
						}

						for (n_c=0;n_c<components;n_c++) 
							c_xx[n_c] = ENDIAN16(sl[i+n_c]);

						break_run=0;
						for (n_c=0;n_c<components;n_c++) {
							delta[n_c] = c_xx[n_c] - c_aa[n_c];
							if(delta[n_c]>NEAR || delta[n_c]<negNEAR) break_run=1;
						}

						if ( break_run )
						{
							for(n_c=0; n_c<components; n_c++){
								c_dd[n_c] = ENDIAN16(psl[i+components+n_c]);
								c_bb[n_c] = ENDIAN16(psl[i+n_c]);
							}
							break;  /* out of while loop */
						}
						/* Run continues */
					}
				}

				/* we only get here if the run is broken by
					a non-matching symbol */

				process_run(RUNcnt, NOEOLINE, 0);

				/* This is the END_OF_RUN state */

				for (n_c=0;n_c<components;n_c++) {
					/* The end of run is done for each component */
					Ix = c_xx[n_c];
					Rb = c_bb[n_c];
					Ra = c_aa[n_c];

					/* Handle two special EOR states */
					c_xx[n_c] = Ix = lossy_end_of_run(Ra, Rb, Ix, 0);
					
				}   /* loop for components */

			}           /* Run state block */
			else {
			
			/*************** REGULAR CONTEXT *******************/

				predict(Rb, Ra, Rc);
				cont = classmap[cont];
				
				if (cont<0)
				{	SIGN=-1;
					cont=-cont;
				}
				else
					SIGN=1;

				/* output a rice code */
				lossy_regular_mode(cont, SIGN, Px, &Ix);
			}

			/* context for next pixel: */
			if (!was_in_run) {

				c_aa[color] = Ix; 
				sl[i] = ENDIAN16(Ix);   /* store reconstructed x */

				c_cc[color] = Rb;
				c_bb[color] = Rd;
				i++;
			}
			else {
				for(n_c=0;n_c<components;n_c++) {
					c_aa[n_c] = c_xx[n_c];
					sl[i+n_c] = ENDIAN16(c_xx[n_c]);

					c_cc[n_c] = c_bb[n_c];
					c_bb[n_c] = c_dd[n_c];
				}
		        i += components;
			}

		} while (i <= (no+components-1));

	}	/* ends 'if' for 8 or 16 bit */
}


