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


extern int zeroLUT[];     /* lookup table to find number of leading zeroes */

extern FILE *in, *out;

byte negbuff[BUFSIZE+4];    /* byte I/O buffer, allowing for 4 "negative" 
						       locations  */

/*
 'buff' is defined as 'rawbuff+4' in bitio.h, so that buff[-4]..buff[-1]
 are well defined. Those locations are used to "return" data to
 the byte buffer when flushing the input bit buffer .
 */


int fp; 	       /* index into byte buffer */
int truebufsize;       /* true size of byte buffer ( <= BUFSIZE) */
int foundeof;

int zeroLUT[256];      /* table to find out number of leading zeros */


/* BIT I/O variables */
dword reg; /* BIT buffer for input/output */
int bits;  /* number of bits free in bit buffer (on output) */
	   /* (number of bits free)-8 in bit buffer (on input)*/


/****************************************************************************
 *  INPUT ROUTINES
 *  note: some routines are implemented as preprocessor macros. See bitio.h.
 ****************************************************************************/


void bufiinit(FILE *fil) {
    /* argument is ignored */
    fp = BUFSIZE;
    truebufsize = 0;
    foundeof = 0;
}


byte fillinbuff(FILE *fil)
{
	int i;

	/* remember 4 last bytes of current buffer (for "undo") */
	for ( i=-4; i<0; i++ )
		buff[i] = buff[fp+i];
        truebufsize = fread(buff, 1, BUFSIZE, fil);
	if ( truebufsize < BUFSIZE ) 
	{
	    if ( truebufsize <= 0 ) 
		{
			if ( foundeof ) 
			{  /* second attempt to read past EOF */
				fprintf(stderr,"*** Premature EOF in compressed file\n");
				exit(10);
			}
			else 
			{
				/* One attempt to read past EOF is OK  */
				foundeof = 1;
			}
	    }
	    /* fill buffer with zeros */
	    memset(buff+truebufsize, 0, (BUFSIZE-truebufsize)*sizeof(*buff));
	}

	fp = 1;
    return buff[0];
}


/* Initializes the bit input routines */
void bitiinit() {
        bits = reg = 0;
        fillbuffer(24);
}


/* 
   Flush the input bit buffer TO A BYTE BOUNDARY. Return unused whole
   bytes to the byte buffer
 */
void bitiflush()  {
    int filled,
	discard, 
	dbytes,
	i, k, treg;
    byte *bp;

    filled = 24 - bits;    /* how many bits at the MS part of reg 
			      have unused data. These correspond to 
			      at most filled+2 bits from the input
			      stream, as at most 2 '0' bits might have
			      been dropped by marker processing */

    dbytes = (filled+2)/8;  /* the coorrect number of bytes we need to
				"unget" is either dbytes or dbytes-1 */
    /* this solution is more general than what is required here: it 
       will work correctly even if the end of a scan is not followed
       by a marker, as will necessarily be the case with the standard JPEG
       format */
    for ( ; ; dbytes-- ) 
	{
		bp = buff + fp - dbytes;  /* back-in the buffer */
		treg = k = 0;
		for ( i=0; i<dbytes; i++ ) 
		{
			if ( bp[i-1]==0xff && (bp[i]&0x80)==0 ) 
			{
				treg |= bp[i] << (BITBUFSIZE-7-k);
				k += 7;
			}
			else 
			{
				treg |= bp[i] << (BITBUFSIZE-8-k);
				k += 8;
			}
		}

		if ( k <= filled )
		break;
    }
    /* check consistency */
    if ( filled-k > 7 ) {
	fprintf(stderr,"bitiflush: inconsistent bits=%d filled=%d k=%d\n",bits,filled,k);
	exit(10);
    }
    discard = filled-k;
    if ( treg != (reg<<discard) ) {
	fprintf(stderr,"bitiflush: inconsistent bits=%d discard=%d reg=%08x treg=%08x\n",bits, discard, reg, treg);
	exit(10);
    }
    if ( reg & (((1<<discard)-1)<<(BITBUFSIZE-discard)) )
	fprintf(stderr,"bitiflush: Warning: discarding nonzero bits; reg=%08x bits=%d discard=%d\n",reg,bits,discard);

    fp -= dbytes;  /* do the unget */
    if ( buff[fp-1]==0xff && buff[fp]==0 ) fp++;

    bits = 0;
    reg = 0;
}




/* Unpad zeros from byte length */
void unpadzeros()
{
	int z;

	z = bits % 8;
	
	if (bits!=24)
	{
		reg = (reg << z);
		bits = bits + z;
	}


}
	
	


/* creates the bit counting look-up table. */
void createzeroLUT()
{
        int i, j, k, l;

        j = k = 1; l = 8;
        for (i = 0; i < 256; ++i) {
                zeroLUT[i] = l;
                --k;
                if (k == 0) {
                        k = j;
                        --l;
                        j *= 2;
                }
        }
}



#ifdef IOFXNS
/* if using functions instead of macros */
dword
getbits(int no) 
{
        register dword temp;

        assert(no > 0 && no <= 18);
        temp = reg >> (32 - no);
        fillbuffer(no);
        return temp;
}
#	define GETBITS(n)	getbits(n)
#else
/* see GETBITS(x,n) in bitio.h */
#endif
