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

/*
 * bitio.c --- for I/O routines
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

extern FILE *in, *out;

byte negbuff[BUFSIZE+4];    /* byte I/O buffer, allowing for 4 "negative"
			       locations  */

 /*
 'buff' is defined as 'rawbuff+4' in bitio.h, so that buff[-4]..buff[-1]
 are well defined. Those locations are used to "return" data to
 the byte buffer when flushing the input bit buffer .
 */

int fp; 		/* index into byte buffer */
int truebufsize;        /* true size of byte buffer ( <= BUFSIZE) */
int foundeof;


/* BIT I/O variables */
dword reg;	   /* BIT buffer for input/output */
int bits;          /* number of bits free in bit buffer (on output) */
		   /* (number of bits free)-8 in bit buffer (on input)*/



/****************************************************************************
 *  OUTPUT ROUTINES
 *  note: some routines are implemented as preprocessor macros. See bitio.h.
 ****************************************************************************/

void flushbuff(FILE *fil) {
	/* fwrite must work correctly, even if fp is equal to 0 */
    fwrite(buff, 1, fp, fil);
    fp = 0;
}



/* Flushes the bit output buffer and the byte output buffer */
void bitoflush() {
	register unsigned int outbyte;
    
    while (bits < 32) {
		outbyte = reg >> 24;
        myputc(outbyte, out);
		if ( outbyte == 0xff ) {
			bits += 7;
			reg <<= 7;
			reg &= ~(1<<(8*sizeof(reg)-1)); /* stuff a 0 at MSB */
		} else {
		    bits += 8;
		    reg <<= 8;
		}
	}
	flushbuff(out);
	bitoinit();
}



/* Initializes the bit output routines */
void bitoinit() {
	bits = 32;
	reg = 0;
	fp = 0;
}
