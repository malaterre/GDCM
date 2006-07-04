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

/* global.c --- support and portability routines: error handling, safe memory
 *                              management, etc.
 *
 * Initial code by Alex Jakulin,  Aug. 1995
 *
 * Modified and optimized: Gadiel Seroussi, October 1995 - ...
 *
 * Modified and added Restart marker and input tables by:
 * David Cheng-Hsiu Chu, and Ismail R. Ismail march 1999
 */

#include <time.h>
#include "global.h"



char *disclaimer = "\
This program is Copyright (c) University of British Columbia.\n\
All rights reserved. It may be freely redistributed in its\n\
entirety provided that this copyright notice is not removed.\n\
It may not be sold for profit or incorporated in commercial programs\n\
without the written permission of the copyright holder.\n\
";



/* I/O files */
FILE *in, *out;
FILE *c_in[MAX_COMPONENTS];
FILE *c_out[MAX_COMPONENTS];
FILE *msgfile = stdout;

/* Context quantization thresholds  - initially unset */
int     T3 = -1,
        T2 = -1,
        T1 = -1,
		Ta = -1;


int verbose = 1;   /* verbosity level */
int nopause = 0;   /* whether to pause the legal notice or not */
int nolegal = 0;   /* whether to print the legal notice or not */


/* parameters for LOSSY images */
int	quant,          /* quantization = 2*NEAR+1 */
	beta,		/* size of extended alphabet */
	qbeta,          /* size of quantized alphabet */
	ceil_half_qbeta, /* ceil(qbeta/2) */
	negNEAR,            /* -NEAR */
	alpha1eps;       /* alpha-1+NEAR */

int	NEAR = DEF_NEAR; 	/* loss tolerance per symbol, fixed at 0 for lossless */
int bpp,    /* bits per sample */
	qbpp,   /* bits per sample for quantized prediction errors */
    limit,  /* limit for unary part of Golomb code */
    limit_reduce;  /* reduction on above for EOR states */


/* define color mode strings */
char *plane_int_string = "plane by plane",
	 *line_int_string = "line intlv",
	 *pixel_int_string = "sample intlv";


/* function to print out error messages */
void error(char *msg) {
	fprintf(stderr, msg);
	exit(-1);
}


/* function to safely call malloc */
void *safealloc(size_t size) {
	void *temp;

	temp = malloc(size);
    if (temp == NULL)
		error("\nsafealloc: Out of memory. Aborting...\n");
	return temp;
}


/* function to safely call calloc **/
void *safecalloc(size_t numels, size_t size) {
	void *temp;

	temp = calloc(numels, size);
    if (temp == NULL)
		error("\nsafecalloc: Out of memory. Aborting...\n");
	return temp;
}


/*
 * TIMING ROUTINES
 */


double get_utime()
{
	clock_t c;

	return (double)clock()/CLOCKS_PER_SEC;
}


/* Set thresholds to default unless specified by header: */
set_thresholds(int alfa, int NEAR, int *T1p, int *T2p, int *T3p)
{
	int lambda,
	    ilambda = 256/alfa,
	    quant = 2*NEAR+1,
	    T1 = *T1p, 
	    T2 = *T2p, 
	    T3 = *T3p;
	
	if (alfa<4096)
	   lambda = (alfa+127)/256;
        else
	   lambda = (4096+127)/256;



	if ( T1 <= 0 )  {
		/* compute lossless default */
		if ( lambda ) 
			T1 = lambda*(BASIC_T1 - 2) + 2;
		else {  /* alphabet < 8 bits */
			T1 = BASIC_T1/ilambda;
			if ( T1 < 2 ) T1 = 2;
		}
		/* adjust for lossy */
		T1 += 3*NEAR;

		/* check that the default threshold is in bounds */
		if ( T1 < NEAR+1 || T1 > (alfa-1) ) 
		     T1 = NEAR+1;         /* eliminates the threshold */
	}
	if ( T2 <= 0 )  {
		/* compute lossless default */
		if ( lambda ) 
			T2 = lambda*(BASIC_T2 - 3) + 3;
		else {
			T2 = BASIC_T2/ilambda;
			if ( T2 < 3 ) T2 = 3;
		}
		/* adjust for lossy */
		T2 += 5*NEAR;

		/* check that the default threshold is in bounds */
		if ( T2 < T1 || T2 > (alfa-1) ) 
		     T2 = T1;         /* eliminates the threshold */
	}
	if ( T3 <= 0 )  {
		/* compute lossless default */
		if ( lambda ) 
			T3 = lambda*(BASIC_T3 - 4) + 4;
		else {
			T3 = BASIC_T3/ilambda;
			if ( T3 < 4 ) T3 = 4;
		}
		/* adjust for lossy */
		T3 += 7*NEAR;

		/* check that the default threshold is in bounds */
		if ( T3 < T2 || T3 > (alfa-1) ) 
		     T3 = T2;         /* eliminates the threshold */
	}

	*T1p = T1;
	*T2p = T2;
	*T3p = T3;
	return 0;
}




/* We first check compatibility with JPEG-LS, then with this implementation */

void check_compatibility(jpeg_ls_header *head_frame, jpeg_ls_header *head_scan, int n_s) 
{

    int	number_of_scans,i;	
    int maxreset;

/* Check implemented color modes */
    if ((head_scan->color_mode>PIXEL_INT)) {
	fprintf(stderr,"Color mode %d not supported\n",head_scan->color_mode);
	exit(10);
    }

    if (head_scan->color_mode==PLANE_INT) 
	number_of_scans=head_frame->comp;
    else 
	number_of_scans=1;
    

/* Test standard compatibility */

    if (head_frame->columns<=0 || head_frame->rows <=0) {
	fprintf(stderr,"Image size must be positive for this implementation.\n");
	exit(10);
    }

    if (head_frame->alp<4) {
	fprintf(stderr,"Alphabet size must be >= 4, got %d\n",head_frame->alp);
	exit(10);
    }


    if (head_scan->T1>head_scan->T2 || head_scan->T2>head_scan->T3 ||
	head_scan->T1<head_scan->NEAR+1 || head_scan->T3>=head_scan->alp ) {
	fprintf(stderr,"Bad thresholds: must be %d <= Ta <= Tb <= Tc <= %d\n",
			head_scan->NEAR+1,head_scan->alp-1);
	exit(10);
    }

    if (head_frame->comp>255) {
	fprintf(stderr,"Too many components (must be less than 255)\n");
	exit(10);
    }

    if (head_scan->NEAR>=head_scan->alp) {
	fprintf(stderr,"Error for near-lossless must be smaller than alphabet (%d), got %d",head_scan->alp,head_scan->NEAR);
	exit(10);
    }

    /*
    if (head_scan->RES < MINRESET || head_scan->RES >= head_scan->alp ) {
	fprintf(stderr,"Reset parameter must be between %d and %d\n",
					MINRESET, head_scan->alp-1);
	exit(10);
    }
    */

    maxreset = (head_scan->alp >= 256)? (head_scan->alp-1):255;

    if (head_scan->RES < MINRESET || head_scan->RES > maxreset ) {
	fprintf(stderr,"Reset parameter must be between %d and %d\n",
					MINRESET, head_scan->alp-1);
	exit(10);
    }

    for (i=0;i<head_frame->comp;i++)
	if (head_frame->comp_ids[i] != (i+1)) {
	   fprintf(stderr,"Components id in frame not compatible with this implementation.\n");
	   exit(10);
        }

    if (number_of_scans == 1) {
	if (head_frame->comp != head_scan->comp) {
	   fprintf(stderr,"In this implementation, when single scan, all components must be in the scan.\n");
	   exit(10);
        }
        for (i=0;i<head_frame->comp;i++)
	  if (head_scan->comp_ids[i] != (i+1)) {
	     fprintf(stderr,"Components id in single scan not compatible with this implementation.\n");
	     exit(10);
          }

    }
    else {
	if (head_scan->comp != 1) {
	   fprintf(stderr,"Only 1 component per scan for plane interleaved mode\n");
	   exit(10);
        }
        if (head_scan->comp_ids[0] != (n_s+1)) {
	   fprintf(stderr,"Components id in multiple scan not compatible with this implementation.\n");
	   exit(10);
        }

    }
}


/* for writing disclaimer to command line in DOS */

char *ttyfilename = "CON";

#define PAUSE	20

fprint_disclaimer(FILE *fp, int nopause)
{
    char *p0, *p1;
    FILE *ttyf;
    int  i, c;

    nopause = nopause | !isatty(fileno(fp));

    if ( !nopause && (ttyf=fopen(ttyfilename,"r"))==NULL ) {
	nopause = 1;
    }

    for ( i=1, p0=disclaimer; ; i++ ) {
	if ( !(*p0)  ) break;
	if ( !nopause && i%PAUSE==0 ) {
	    fflush(fp);
	    fprintf(stderr, "--- (press RETURN to continue) ---"); 
	    fflush(stderr);
	    c = getc(ttyf);
	}
	for ( p1=p0; (*p1 != '\n') && (*p1 != 0); p1++ );
	*p1 = 0;
	fprintf(fp,"%s\n",p0);
	p0 = p1+1;
    }
    fprintf(fp,"\n"); fflush(fp);
    if ( !nopause) fclose(ttyf);
}
