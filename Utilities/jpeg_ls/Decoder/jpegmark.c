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

/* jpegmark.c --- for JPEG markers
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
#include "jpegmark.h"

#ifdef BUFINPUT
#   include "bitio.h"
#else
#   define	mygetc(in)	(getc(in))     
#   define 	myfeof(in)	(feof(in))
#endif

void
check_range(int param, char *name, int low, int high)
{
    if ( param < low || param > high ) {
	fprintf(stderr,"Allowed range for %s is [%d..%d]: got %d\n",
	name, low, high, param);
	exit(10);
    }
}

/*
 *
 *   Marker output functions
 *
 */

int
write_n_bytes(FILE *out, int value, int n)
{

	int	l;


	if (n>4)  {
		fprintf(stderr,"write_n_bytes: Only 32 bits variables supported.\n");
		exit(10);
	}
		

#ifdef BIG_ENDIAN
        for (l=n-1;l>=0;l--)  {
	    if ( putc((value>>(8*l))&0x000000FF,out) == EOF )
		return EOF;
        }
#else  /* little endian */
	for (l=0;l<n;l++) {
	    if ( putc((value&0x000000FF),out) == EOF )
		return EOF;
	    value >>= 8;
	}
#endif
	return n;

}

int
write_2_bytes(FILE *out, int value)
{
	return write_n_bytes(out,value,2);
}

int
write_marker(FILE *out, int marker)
/* Write a two-byte marker (just the marker identifier) */
{
	write_n_bytes(out, marker, 2);
	return 2;
}

int
write_jpegls_frame(FILE *out, jpeg_ls_header *jp)
{
    int i, marker_len,
	bpp, ct = 0;
		 
    ct += write_marker(out, SOF_LS);   /* write JPEG-LS frame marker */

    check_range(jp->comp, "frame components", 1, 255);
    marker_len = 8 + 3*jp->comp;

    ct += write_n_bytes(out, marker_len, 2); /* write marker length */

    for ( bpp=1; (1L<<bpp)<jp->alp; bpp++ );

    ct += write_n_bytes(out, bpp, 1);        /* write bits/sample */

    /* current implementation only supports up to 64K samples in 
       either direction. Also, they must be specified in the frame header  */
    check_range(jp->rows, "rows", 1, 65535);
    check_range(jp->columns, "columns", 1, 65535);

    ct += write_n_bytes(out, jp->rows, 2);     /* write number of rows */
    ct += write_n_bytes(out, jp->columns, 2);  /* write number of cols */

    ct += write_n_bytes(out, jp->comp, 1);

    /* now write a triplet of bytes per component */
    for ( i=0; i<jp->comp; i++ ) {
	int sx = jp->samplingx[i], 
	    sy = jp->samplingy[i];

	check_range(sx,"sampling(x)",1,4);
	check_range(sy,"sampling(y)",1,4);
	ct += write_n_bytes(out, jp->comp_ids[i], 1); /* component identifier */
	ct += write_n_bytes(out, (sx<<4)|sy, 1);  /* sampling rates */
	ct += write_n_bytes(out, 0, 1);    /* Tq unused */
    }
    return ct;
}

int
write_jpegls_scan(FILE *out, jpeg_ls_header *jp)
{
    int i, marker_len, ct=0;
		 
    ct += write_marker(out, SOS);   /* write JPEG-LS scan marker */

    check_range(jp->comp, "scan components", 1, 4);

    if ( jp->comp == 1 && jp->color_mode != PLANE_INT) {
	fprintf(stderr,"Interleave for 1 component must be PLANE_INT: got %d\n",
		jp->color_mode);
	exit(10);
    }

    if ( jp->comp >1 && jp->color_mode == 0 ) {
	fprintf(stderr,"Interleave for multi-component scan must be nonzero: got %d\n",
		jp->color_mode);
	exit(10);
    }

    marker_len = 6 + 2*jp->comp;

    ct += write_n_bytes(out, marker_len, 2); /* write marker length */
    ct += write_n_bytes(out, jp->comp, 1);   /* # of components for the scan */

    /* write 2 bytes per component */
    for ( i=0; i<jp->comp; i++ ) {
	ct += write_n_bytes(out, jp->comp_ids[i], 1); /* component identifier */
	ct += write_n_bytes(out, 0, 1);   /* no tables in this implementation */
    }

    check_range(jp->NEAR, "NEAR", 0, 255);
    ct += write_n_bytes(out, jp->NEAR, 1);

    check_range(jp->color_mode,"INTERLEAVE", 0, 2);
    ct += write_n_bytes(out, jp->color_mode, 1);

    check_range(jp->shift, "SHIFT", 0, 15);
    ct += write_n_bytes(out, jp->shift, 1);

    return ct;
}


int
write_jpegls_extmarker(FILE *out, jpeg_ls_header *jp)
{
    int marker_len, ct=0;
		 
    ct += write_marker(out, LSE);   /* write JPEG-LS extended marker id */

    ct += write_n_bytes(out, 13, 2); /* marker length */
    ct += write_n_bytes(out,  LSE_PARAMS, 1); /* ext marker id */
    ct += write_n_bytes(out, jp->alp-1, 2);  /* MAXVAL */
    ct += write_n_bytes(out, jp->T1, 2); 
    ct += write_n_bytes(out, jp->T2, 2); 
    ct += write_n_bytes(out, jp->T3, 2); 
    ct += write_n_bytes(out, jp->RES, 2);
    return ct;
}


/*
 *
 *   Marker input functions
 *
 */

int
seek_marker(FILE *in, int *mkp )
/* Seeks a marker in the input stream. Returns the marker head, or EOF */
{
    int c, c2, ct=0;
    while ( (c=mygetc(in)) != EOF ) {
	ct ++;
	if ( c == 0xFF ) {
	    if ( (c2=mygetc(in)) == EOF )
			return EOF;
	    ct ++;
	    if ( c2 & 0x80 ) {
			*mkp = (c<<8)|c2;
		return ct;
	    }
	}
    }
    return EOF;
}
	

unsigned int
read_n_bytes(FILE *in, int n)
/* reads n bytes (0 <= n <= 4) from the input stream */
{
    unsigned int m = 0;
    int i;

    for ( i=0; i<n; i++ )
	m = (m << 8) | mygetc(in);
    return m;

}

int
read_marker(FILE *in, int *mkp)
/* reads a marker from the next two bytes in the input stream */
{
	unsigned int m, ct=0;

	m = read_n_bytes(in, 2);
	if ( feof(in) ) return EOF;
	if ( (m & 0xFF00) != 0xFF00 )  {
	    fprintf(stderr,"read_marker: Expected marker, got %04x\n",m);
	    exit(10);
	}
	*mkp = m;
	return 2;
}

int
read_jpegls_frame(FILE *in, jpeg_ls_header *jp)
/* reads the JPEG-LS frame marker (not including marker head) */
{
    int i,
	marker_len,
	bpp,
	tq,
	comp,
	ct = 0;

    /* Read Marker Length */
    marker_len = read_n_bytes(in, 2);
    ct += 2;

	/* Read the bits per pixel */
    bpp = read_n_bytes(in, 1);
    ct ++;

    check_range(bpp,"bpp",2,16);
    jp->alp = 1<<bpp;

	/* Read the rows and columns */
    jp->rows = read_n_bytes(in, 2);
    ct += 2;
    jp->columns = read_n_bytes(in, 2);
    ct += 2;
    
	/* Read component information */
	comp = read_n_bytes(in, 1);
    ct += 1;
    check_range(comp,"COMP",1,255);
    jp->comp = comp;

    for ( i=0; i<comp; i++ ) 
	{
		int sx, sy, cid;

		cid = read_n_bytes(in, 1);
		ct += 1;
		sx = read_n_bytes(in, 1);
		ct += 1;
		tq = read_n_bytes(in, 1);
		ct += 1;
		check_range(tq,"Tq",0,0);
		sy = sx & 0x0f;
		sx >>= 4;
		check_range(sx, "sampling(x)", 1, 4);
		check_range(sy, "sampling(y)", 1, 4);
		jp->samplingx[i] = sx;
		jp->samplingy[i] = sy;
		jp->comp_ids[i] = cid;
    }

	/* Check for errors */
    if ( myfeof(in) ) 
	{
		fprintf(stderr,"read_jpegls_frame: EOF while reading frame marker\n");
		return EOF;
    }
    if ( marker_len != 8 + 3*comp ) 
	{
		fprintf(stderr,"read_jpegls_frame: inconsistent marker length: expected %d, got %d\n",marker_len, 8 + 3*comp);
		exit(10);
    }

    return ct;
}



/* reads the JPEG-LS scan marker (not including marker head) */
int read_jpegls_scan(FILE *in, jpeg_ls_header *jp)
{
    int i, marker_len,
	comp, ct=0;
		 

    marker_len = read_n_bytes(in, 2);
    ct += 2;

    comp = read_n_bytes(in, 1);
    ct += 1;
    check_range(comp, "scan components", 1, 4);

    jp->comp = comp;

    /* read 2 bytes per component */
    for ( i=0; i<comp; i++ ) {
	int cid, tm;

	cid = read_n_bytes(in, 1); /* component identifier */
	ct += 1;
	tm = read_n_bytes(in, 1);  /* table identifier */
	ct += 1;

	if ( tm ) {
	    fprintf(stderr,"read_jpegls_scan: found nonzero table identifier, not supported\n");
	    exit(10);
	}
	jp->comp_ids[i] = cid;
    }

    jp->NEAR = read_n_bytes(in, 1);
    ct += 1;
    check_range(jp->NEAR,"NEAR", 0, 255);

    jp->color_mode = read_n_bytes(in, 1);
    ct += 1;
    check_range(jp->color_mode, "INTERLEAVE", 0, 2);

    if ( jp->comp == 1 && jp->color_mode != 0 ) {
	/*
	fprintf(stderr,"Interleave for 1 component must be 0: got %d\n",
		jp->color_mode);
	*/

	/* ignore interleave value, set to 0 */
	jp->color_mode = 0;
    }

    if ( jp->comp >1 && jp->color_mode == 0 ) {
	fprintf(stderr,"Interleave for multi-component scan must be nonzero: got %d\n",
		jp->color_mode);
	exit(10);
    }


    jp->shift = read_n_bytes(in, 1);
    ct += 1;
    check_range(jp->shift, "SHIFT", 0, 15);

    if ( myfeof(in) ) {
	fprintf(stderr,"read_jpegls_scan: EOF while reading frame marker\n");
	return EOF;
    }
    if ( marker_len != 6 + 2*comp ) {
	fprintf(stderr,"read_jpegls_scan: inconsistent marker length: expected %d, got %d\n",marker_len, 6 + 2*comp);
	exit(10);
    }
    return ct;
}



/* reads the JPEG-LS extension marker (not including marker head) */
/* Supports non-default type (1) and mapping table type (2) */
int read_jpegls_extmarker(FILE *in, jpeg_ls_header *jp)

{
    int marker_len,		/* marker length */
		maxval,			/* max value */
		T1, T2, T3,		/* thresholds */
		ct = 0;			
	int IDtype;			/* LSE type */
	int TID;			/* table ID */
	int Wt;				/* width of each table entry */
	int MAXTAB;			/* maximum table index */
	int i;


	/* Read marker length */
	marker_len = read_n_bytes(in, 2); /* marker length */
	ct += 2;

	/* Read id type */
	IDtype = read_n_bytes(in,  1);
	ct += 1;
	

	/* For Type 1 - non default parameters */
	if (IDtype == LSE_PARAMS)
	{
		if ( marker_len != 13 ) 
		{
			fprintf(stderr,"read_jpegls_extmarker: bad marker length %d\n",marker_len);
			exit(10);
		}

		/* read maxval */
		maxval = read_n_bytes(in, 2);
		ct += 2;
		jp->alp = maxval +1;

		/* read thresholds and reset */
		jp->T1 = read_n_bytes(in, 2);
		ct += 2;
		jp->T2 = read_n_bytes(in, 2);
		jp->T3 = read_n_bytes(in, 2);
		jp->RES = read_n_bytes(in, 2);
		ct += 6;

		if ( myfeof(in) ) {
			fprintf(stderr,"read_jpegls_extmarker: EOF while reading frame marker\n");
			return EOF;
		}

		return ct;
	}

	/* For Type 2 - mapping table */
	if (IDtype == LSE_MAPTABLE)
	{

		/* Indicate table used */
		jp->need_table = 1;

		/* Read table ID */
		jp->TID = TID = read_n_bytes(in, 1);
		ct += 1;

		/* Read width of table entry */
		jp->Wt = Wt = read_n_bytes(in, 1);
		if (Wt<=0 || Wt>3)
		{	
			fprintf(stderr, "Width of mapping table entries must be either 1,2 or 3 in this implementation. Sorry!\n");
			exit(0);
		}
		ct += 1;

		/* Calculate value of MAXTAB */
		jp->MAXTAB = MAXTAB = ((marker_len - 5) / Wt) - 1;

		/* Get table entries */
		jp->TABLE[TID] = (unsigned int *)safecalloc((MAXTAB+1)*sizeof(int), 1);
		for (i=0; i<=MAXTAB; i++)
		{
			jp->TABLE[TID][i] = read_n_bytes(in, Wt);
		}
		ct += ((MAXTAB+1) * Wt);

		return ct;
	}

	/* Non supported types */

	fprintf(stderr, "LSE marker type %i not supported in this implementation.\n", IDtype);
	exit(0);

}





/* Read DRI restart marker */
int read_jpegls_restartmarker(FILE *in, jpeg_ls_header *jp)
{
	int ct = 0;
	int marker_len;		/* the marker length */
	int Ri;				/* the restart interval */

	/* Read marker length */
    marker_len = read_n_bytes(in, 2);
    ct += 2;

	/* Read the restart interval */
	Ri = read_n_bytes(in, marker_len - 2);
	ct += (marker_len - 2);

	jp->restart_interval = Ri;

	return ct;
	
}
