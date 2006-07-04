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
   (c) COPYRIGHT HEWLETT-PACKARD COMPANY, 1995-1997.
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

/* melcode.c --- for processing in run mode
 *
 * Initial code by Alex Jakulin,  Aug. 1995
 *
 * Modified and optimized: Gadiel Seroussi, October 1995
 *
 * Color Enhancement: Guillermo Sapiro, August 1996
 *
 * Modified and added Restart marker and input tables by:
 * David Cheng-Hsiu Chu, and Ismail R. Ismail march 1999
 */

#include <stdio.h>
#include "global.h"
#include "bitio.h"


#define MELCSTATES	32	/* number of melcode states */

static J[MELCSTATES] = {
	0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,6,7,
	7,8,9,10,11,12,13,14,15 
};

static int melcstate[MAX_COMPONENTS],        /* index to the state array */
		   melclen[MAX_COMPONENTS];          /* contents of the state array location
												indexed by melcstate: the "expected"
												run length is 2^melclen, shorter runs are
												encoded by a 1 followed by the run length
												in binary representation, wit a fixed length
												of melclen bits */

static unsigned long melcorder[MAX_COMPONENTS];  /* 2^ melclen */


void init_process_run(int maxrun)    /* maxrun is ignoreed when using MELCODE,
					 					kept here for function compatibility */				    
{
	int	n_c;

	for (n_c=0;n_c<components;n_c++) {
	melcstate[n_c] = 0;
	melclen[n_c] = J[0];
	melcorder[n_c] = 1<<melclen[n_c];
	}
}



process_run(int runlen, int eoline, int color)
{
	int hits = 0;


	while ( runlen >= melcorder[color] ) {
		hits ++;
		runlen -= melcorder[color];
		if ( melcstate[color] < MELCSTATES ) {
			melclen[color] = J[++melcstate[color]];
			melcorder[color] = (1L<<melclen[color]);
		}
	}

	/* send the required number of "hit" bits (one per occurrence
	   of a run of length melcorder). This number is never too big:
	   after 31 such "hit" bits, each "hit" would represent a run of 32K
	   pixels.
	*/
	PUT_ONES(hits);

	if ( eoline==EOLINE ) {
		/* when the run is broken by end-of-line, if there is
		   a non-null remainder, send it as if it were 
		   a max length run */
		if ( runlen )
			PUT_ONES(1);
		return;
	}

	/* now send the length of the remainder, encoded as a 0 followed
	   by the length in binary representation, to melclen bits */
	limit_reduce = melclen[color]+1;
	PUTBITS(runlen,limit_reduce);

	/* adjust melcoder parameters */
	if ( melcstate[color] ) {
		melclen[color] = J[--melcstate[color]];
		melcorder[color] = (1L<<melclen[color]);
	}
	return;
}




void
close_process_run()
{
/* retained for compatibility with ranked runs */
}
