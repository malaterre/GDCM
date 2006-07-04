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

/* bitio.h --- for I/O routines
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

#ifndef BITIO_H
#define BITIO_H

#include "global.h"

/* BYTE I/O variables */
#define BUFSIZE ((16*1024)-4) /* Size of input BYTE buffer */
extern int fp;                /* index into byte  buffer */
extern int truebufsize;       /* true size of byte buffer ( <= BUFSIZE) */
extern byte negbuff[];        /* the buffer */
#define buff (negbuff+4)


/* BIT I/O variables */
extern dword reg;         /* BIT buffer for input/output */
extern int bits;          /* number of bits free in bit buffer (on output) */
                          /* (number of bits free)-8 in bit buffer (on input)*/
#define BITBUFSIZE (8*sizeof(reg))

extern int zeroLUT[];     /* lookup table to find number of leading zeroes */

extern FILE *in, *out;


#define mygetc(fil) ((fp >= BUFSIZE) ? (fillinbuff(fil)) : (buff[fp++]))
#define myungetc(x,fil) (buff[--fp]=x)
#define myfeof(fil) ((fp >= truebufsize) && feof(fil))


extern void bufiinit(FILE *fil);

extern byte fillinbuff(FILE *fil);



/* loads more data in the input buffer (inline code )*/
#define fillbuffer(no) {                        \
        byte x;                                 \
                                                \
	assert(no+bits <= 24);			\
        reg <<= no;                             \
        bits += no;                             \
        while (bits >= 0) {                     \
                x = mygetc(in);                 \
		if ( x == 0xff ) {              \
		    if ( bits < 8 ) {           \
			myungetc(0xff, in);     \
			break;                  \
		    }				\
		    else {			\
			x = mygetc(in);		\
			if ( !(x & 0x80) )  { /* non-marker: drop 0 */	\
			    reg |= (0xff << bits) | ((x & 0x7f)<<(bits-7));\
			    bits -= 15;		\
			}			\
			else {			\
			    /* marker: hope we know what we're doing */\
			    /* the "1" bit following ff is NOT dropped */\
			    reg |= (0xff << bits) | (x <<(bits-8));\
			    bits -= 16;		\
			}			\
			continue;		\
		    }				\
		}				\
                reg |= x << bits;               \
                bits -= 8;                      \
        }                                       \
}

#define FILLBUFFER(n)	fillbuffer(n)


/* Initializes the bit input routines */
extern void bitiinit();


/* creates the bit counting look-up table. */
extern void createzeroLUT();


#ifdef IOFXNS
extern dword getbits(int no);
#	define GETBITS(n)	getbits(n)
#else
#  define GETBITS(x, n)\
 { x = reg >> (32 - (n));\
   FILLBUFFER(n);\
 }
#endif



#endif /* BITIO_H */
