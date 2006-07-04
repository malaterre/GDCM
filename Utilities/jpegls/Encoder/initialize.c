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

/* initialize.c --- functions to initialize look up tables
 *                  and statistics tables            
 *
 * Initial code by Alex Jakulin,  Aug. 1995
 *
 * Modified and optimized: Gadiel Seroussi, October 1995
 *
 * Modified and added Restart marker and input tables by:
 * David Cheng-Hsiu Chu, and Ismail R. Ismail march 1999
 */

#include <stdio.h>
#include <math.h>

#include "global.h"
#include "bitio.h"


int vLUT[3][2 * LUTMAX16];

/*byte getk[65][3000];*/
/*int clipPx[510];*/

int classmap[CONTEXTS1];

int	*qdiv0, *qdiv,        /* quantization table (division via look-up) */
	*qmul0, *qmul;        /* dequantization table */

int N[TOT_CONTEXTS], 
    A[TOT_CONTEXTS], 
    B[TOT_CONTEXTS],
	C[TOT_CONTEXTS];







/* Setup Look Up Tables for quantized gradient merging */
void prepareLUTs()
{
	int i, j, idx, lmax;
	byte k;

	lmax = min(alpha,lutmax);
	
	/* implementation limitation: */
	if ( T3 > lmax-1 ) {
		fprintf(stderr,"Sorry, current implementation does not support threshold T3 > %d, got %d\n",lmax-1,T3);
		exit(10);
	}


	/* Build classification tables (lossless or lossy) */
	
	if (lossy==FALSE) {

		for (i = -lmax + 1; i < lmax; i++) {

			if  ( i <= -T3 )        /* ...... -T3  */
				idx = 7;
			else if ( i <= -T2 )    /* -(T3-1) ... -T2 */
				idx = 5;
			else if ( i <= -T1 )    /* -(T2-1) ... -T1 */
				idx = 3;

			else if ( i <= -1 )     /* -(T1-1) ...  -1 */
				idx = 1;
			else if ( i == 0 )      /*  just 0 */
				idx = 0;

			else if ( i < T1 )      /* 1 ... T1-1 */
				idx = 2;
			else if ( i < T2 )      /* T1 ... T2-1 */
				idx = 4;
			else if ( i < T3 )      /* T2 ... T3-1 */
				idx = 6;
			else                    /* T3 ... */
				idx = 8;

			vLUT[0][i + lutmax] = CREGIONS * CREGIONS * idx;
			vLUT[1][i + lutmax] = CREGIONS * idx;
			vLUT[2][i + lutmax] = idx;
		}

	} else {

		for (i = -lmax + 1; i < lmax; i++) {

			if ( NEAR >= (alpha-1) )
				idx = 0;   /* degenerate case, regardless of thresholds */
			else

				if  ( i <= -T3 )        /* ...... -T3  */
					idx = 7;
				else if ( i <= -T2 )    /* -(T3-1) ... -T2 */
					idx = 5;
				else if ( i <= -T1 )    /* -(T2-1) ... -T1 */
					idx = 3;

				else if ( i <= -NEAR-1 )     /* -(T1-1) ...  -NEAR-1 */
					idx = 1;
				else if ( i <= NEAR )      /*  within NEAR of 0 */
					idx = 0;

				else if ( i < T1 )      /* 1 ... T1-1 */
					idx = 2;
				else if ( i < T2 )      /* T1 ... T2-1 */
					idx = 4;
				else if ( i < T3 )      /* T2 ... T3-1 */
					idx = 6;
				else                    /* T3 ... */
					idx = 8;

			vLUT[0][i + lutmax] = CREGIONS * CREGIONS * idx;
			vLUT[1][i + lutmax] = CREGIONS * idx;
			vLUT[2][i + lutmax] = idx;
		}

	}


	/*  prepare context mapping table (symmetric context merging) */
	classmap[0] = 0;
	for ( i=1, j=0; i<CONTEXTS1; i++) {
	    int q1, q2, q3, n1=0, n2=0, n3=0, ineg, sgn;

	    if(classmap[i])
			continue;

	    q1 = i/(CREGIONS*CREGIONS);		/* first digit */
	    q2 = (i/CREGIONS)%CREGIONS;		/* second digit */
    	q3 = i%CREGIONS;    			/* third digit */

	    if((q1%2)||(q1==0 && (q2%2))||(q1==0 && q2==0 && (q3%2)))
			sgn = -1;
	    else
			sgn = 1;

	    /* compute negative context */
    	if(q1) n1 = q1 + ((q1%2) ? 1 : -1);
	    if(q2) n2 = q2 + ((q2%2) ? 1 : -1);
	    if(q3) n3 = q3 + ((q3%2) ? 1 : -1);

	    ineg = (n1*CREGIONS+n2)*CREGIONS+n3;
	    j++ ;    /* next class number */
	    classmap[i] = sgn*j;
	    classmap[ineg] = -sgn*j;

	}

	/* prepare table to find k */

	
/*	for (i=1; i< 65; i++)	/* value of N[] */
/*		for (j=1; j<2500; j++)	/* value of A[] */
/*		{
			register nst = i;
			for(k=0; nst < j; nst<<=1, k++);
			getk[i][j]=k;
		}*/

	/* prepare table to find clip of Px with 8-bit */
/*	for (i=0; i<127; i++)
		clipPx[i] = 0;
	for (i=127; i<382; i++)
		clipPx[i] = i - 127;
	for (i=382; i<510; i++)
		clipPx[i] = 255;*/

}





/* prepare quantization tables for near-lossless quantization */
void prepare_qtables(int absize, int NEAR)
{
    int dif, qdiff;
    int beta, quant;

    quant = 2*NEAR+1;
    beta = absize;

    if ( (qdiv0 = (int *)calloc(2*absize-1,sizeof(int)))==NULL ) {
	    perror("qdiv  table");
	    exit(10);
    }
    qdiv = qdiv0+absize-1;

    if ( (qmul0 = (int *)calloc(2*beta-1,sizeof(int)))==NULL ) {
	    perror("qmul  table");
	    exit(10);
    }
    qmul = qmul0+beta-1;

    for ( dif = -(absize-1); dif<absize; dif++ ) {
	    if ( dif<0 )
		    qdiff = - ( (NEAR-dif)/quant );
	    else
		    qdiff = ( NEAR + dif )/quant;
	    qdiv[dif] = qdiff;
    }
    for ( qdiff = -(beta-1); qdiff<beta; qdiff++ ) {
	    dif = quant*qdiff;
	    qmul[qdiff] = dif;
    }
}



/* Initialize A[], B[], C[], and N[] arrays */
void init_stats(int absize) 
{
	int i, initabstat, slack;

	slack = 1<<INITABSLACK;
	initabstat = (absize + slack/2)/slack;
	if ( initabstat < MIN_INITABSTAT ) initabstat = MIN_INITABSTAT;

	/* do the statistics initialization */
	for (i = 0; i < TOT_CONTEXTS; ++i) {
		C[i]= B[i] = 0;
		N[i] = INITNSTAT;
		A[i] = initabstat;
	}
}
