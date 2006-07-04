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
#endif

/* Makes sure a parameter falls within its allowed range */
void check_range(int param, char *name, int low, int high)
{
    if ( param < low || param > high )
	{
		fprintf(stderr,"Allowed range for %s is [%d..%d]: got %d\n",
			name, low, high, param);
		exit(10);
    }
}

/* reads n bytes (0 <= n <= 4) from the input stream */

unsigned int read_n_bytes(FILE *in, unsigned int n)
{
    unsigned int m = 0;
    int i;

    for ( i=0; i<n; i++ )
        m = (m << 8) | ((unsigned char)getc(in));
    return m;
}

/*
 *   Marker output functions
 */

int write_n_bytes(FILE *out, int value, int n)
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



int write_2_bytes(FILE *out, int value)
{
	return write_n_bytes(out,value,2);
}



int write_marker(FILE *out, int marker)
/* Write a two-byte marker (just the marker identifier) */
{
	write_n_bytes(out, marker, 2);
	return 2;
}


/* Write the frame header to the JLS file */
int write_jpegls_frame(FILE *out, jpeg_ls_header *jp)
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


/* Write the Scan header to JLS file */
int write_jpegls_scan(FILE *out, jpeg_ls_header *jp)
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



/* Write out LSE header to JLS file - only supports type 1 and 2 currently */
int write_jpegls_extmarker(FILE *out, jpeg_ls_header *jp, int IDtype, char *mapfilename)
{
    int ct=0;

	/* For Type 1 - non default parameters */
	if (IDtype == LSE_PARAMS)
	{
		ct += write_marker(out, LSE);			/* write JPEG-LS extended marker id */

		ct += write_n_bytes(out, 13, 2);			/* marker length */
		ct += write_n_bytes(out, LSE_PARAMS, 1);	/* ext marker id */
		ct += write_n_bytes(out, jp->alp-1, 2);		/* MAXVAL */
		ct += write_n_bytes(out, jp->T1, 2);
		ct += write_n_bytes(out, jp->T2, 2);
		ct += write_n_bytes(out, jp->T3, 2);
		ct += write_n_bytes(out, jp->RES, 2);
		return ct;
	}

	/* For Type 2 - Mapping Table */
	if (IDtype == LSE_MAPTABLE)
	{
		unsigned int TID,		/* Table ID */
			     Wt,		/* Width of table entries */
			     MAXTAB,		/* Maximum index of table */
			     length	;	/* Marker length */
		int i;
		FILE* tablefile;

		/* Is only implemented for 8 bpp images in this implementation */
		if (bpp16==TRUE)
		{
			fprintf(stderr, "Sorry, mapping tables are only supported for 8 bpp images in this implementation.\n");
			exit(1);
		}
		
		/* Open the table file */
		if ( mapfilename == NULL )
		{
			usage();
			exit(1);
		}
		if ( (tablefile=fopen(mapfilename,"rb")) == NULL )
		{
			perror(mapfilename);
			exit(10);
		}

		/* Assign values to jpeg header */
		/* Read the table ID */
		jp->TID = TID = read_n_bytes(tablefile, 1);

		/* Read the width of each entry */
		jp->Wt = Wt = read_n_bytes(tablefile, 1);

		/* Read the max table index value */
		MAXTAB = read_n_bytes(tablefile, 4);
		
		/* Create the table */
		jp->TABLE[TID] = (unsigned int *) safecalloc ((MAXTAB+1)*sizeof(unsigned int), 1);
	
		for (i=0; i <= MAXTAB; i++)
		{
			if (i==200)
				i=200;

			jp->TABLE[TID][i] = read_n_bytes(tablefile, Wt);
			if feof(tablefile)
			{
				fprintf(stderr,"Error Reading Table File - Premature EOF found.\n");
				exit(1);
			}
		}


		length = 5 + (Wt*(MAXTAB+1));
		
		/* Write out the header */
		ct += write_marker(out, LSE);
		ct += write_n_bytes(out, length, 2);		/* marker length */
		ct += write_n_bytes(out, LSE_MAPTABLE, 1);	/* LSE marker id */
		ct += write_n_bytes(out, TID, 1);			/* table id */
		ct += write_n_bytes(out, Wt, 1);			/* width of table entries in bytes */

		for (i=0; i<=MAXTAB; i++)
			ct += write_n_bytes(out, jp->TABLE[TID][i], Wt);


		return ct;
	}
	else
	{
		fprintf(stderr, "LSE Parameter %i not defined in this implementation.\n",IDtype);
		exit(1);
	}

}





/* Writes the DRI header to the JLS file */
int write_jpegls_restartmarker(FILE *out, jpeg_ls_header *jp)
{
	int ct=0;
	int Ri;		/* the restart interval (# of MCU's between markers) */
	int length;	/* the length of the DRI header */

	Ri = jp->restart_interval;

	if (Ri <= 65535)
		length = 4;
	else
		length = 6;

	ct += write_marker(out, DRI);
	ct += write_n_bytes(out, length, 2);
	ct += write_n_bytes(out, Ri, 2);

	return ct;
}
