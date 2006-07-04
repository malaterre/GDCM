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

/* encoder.c --- the main module, argument parsing, file I/O
 *
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

#include "global.h"
#include "math.h"
#include "string.h"
#include "jpegmark.h"

static char *banner="\n\
=============================================\n\
SPMG/JPEG-LS COMPRESSOR " JPEGLSVERSION "\n\
=============================================\n\
These programs are Copyright (c) University of British Columbia.\n\
All rights reserved. They may be freely redistributed in their\n\
entirety provided that this copyright  notice is not removed.\n\
They may not be sold for profit or incorporated in commercial\n\
programs without the written permission of the copyright holder.\n\
Each program is provided as is, without any express or implied\n\
warranty, without even the warranty of fitness for a particular\n\
purpose.\n\
\n\
=========================================================\n\
THIS SOFTWARE IS BASED ON HP's implementation of jpeg-ls:\n\
=========================================================\n\
(c) COPYRIGHT HEWLETT-PACKARD COMPANY, 1995-1999.\n";

pixel *pscanline, *cscanline, *scanl0, *scanl1;
pixel *c_pscanline[MAX_COMPONENTS], *c_cscanline[MAX_COMPONENTS], 
      *c_scanl0[MAX_COMPONENTS],    *c_scanl1[MAX_COMPONENTS];

jpeg_ls_header *head_frame,*head_scan[MAX_SCANS];

int columns, rows, components, 
    samplingx[MAX_COMPONENTS], samplingy[MAX_COMPONENTS];
int c_columns[MAX_COMPONENTS];
int c_rows[MAX_COMPONENTS];
int whose_max_size_rows, whose_max_size_columns;
int	color_mode;	
int	need_lse;			 	/* if we need an LSE marker (non-default params) */
int need_table;					/* if we need an LSE marker (mapping table) */
int need_restart;				/* if we need to add restart markers */
int restart_interval;    			/* indicates the restart interval */
int	multi;					/* if the files are separate */
int	application_header;			/* application bytes written in the header */
int	all_header;				/* all bytes of the header, including application
						   bytes and JPEG-LS bytes */
int	shift=0;				/* Shift value for sparse images */
int	palete=0;				/* for paletized images */
int lossy;					/* Indicates if in lossy mode or not */
int lutmax;					/* lutmax is either 256 or 4501 */
int bpp16;               			/* Indicates if 16 bits per pixel mode or not */
char *mappingtablefilename=NULL; 		/* Mapping table filename */

/* reset */
#ifndef FIXRESET
int	RESET;
#endif


/* alphabet size */
#ifndef FIXALPHA
int     alpha,     	 /* alphabet size */
	ceil_half_alpha; /* ceil(alpha/2) */
#endif

#ifdef POW2
int	highmask;
#endif




/* Read one row of pixel values */

inline void read_one_line(pixel* line, int cols, FILE* infile)
{
	unsigned char* line8;
	int i;
	
	if (bpp16==FALSE)
	{
		line8 = (unsigned char *)safealloc(cols);

		if (fread(line8, 1, cols, infile) != cols)
			fprintf(stderr,"Input file is truncated");

		for(i=0; i<cols; i++)
                        line[i] = line8[i];
		free(line8);

	}
	else
	{
		if (fread(line, 2, cols, infile) != cols)
			fprintf(stderr,"Input file is truncated");

	}
}





/* Initialize the buffers for each line */
void initbuffers(int multi, int comp) {

    int	i;

    if (multi) 		/* The files are received independent */

		for (i=0;i<comp;i++) {
			c_scanl0[i] = (pixel *)safecalloc((c_columns[i]+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );
			c_scanl1[i] = (pixel *)safecalloc((c_columns[i]+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );

		    c_pscanline[i] = c_scanl0[i] + (LEFTMARGIN-1);
		    c_cscanline[i] = c_scanl1[i] + (LEFTMARGIN-1);
		}

    else { 			/* Only 1 file received */
	
	    scanl0 = (pixel *)safecalloc(components*(columns+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );
	    scanl1 = (pixel *)safecalloc(components*(columns+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );

	/* Adjust scan line pointers taking into account the margins,
	   and also the fact that indexing for scan lines starts from 1
	 */
 	    pscanline = scanl0 + components*(LEFTMARGIN-1);
	    cscanline = scanl1 + components*(LEFTMARGIN-1);
    }

    bitoinit();
}




/* Swap the pointers to the current and previous scanlines */

void swaplines()
{
	pixel *temp;
	temp = pscanline;
	pscanline = cscanline;
	cscanline = temp;
}




/* Swap the pointers to the current and previous scanlines */

void c_swaplines(int i)
{
	pixel *temp;
	temp = c_pscanline[i];
	c_pscanline[i] = c_cscanline[i];
	c_cscanline[i] = temp;
}



/* close the line buffers */
int closebuffers(int multi) {
	int pos,i;

        bitoflush();

	if (multi==0)
	   fclose(in);
    else
       for (i=0;i<components;i++)
		  fclose(c_in[i]);

	pos = ftell(out);

        fclose(out);

        free(scanl0);
        free(scanl1);

	return pos;
}




/* Initialization Function - Reads in parameters from image and command line */

void initialize(int argc, char *argv[]) 
{
	char *infilename=NULL,
	     *c_infilename[MAX_COMPONENTS],
		 *outfilename = OUTFILE COMPSUFFIX,
		 *color_mode_string;
	int  i, n_c, common_rows, common_alpha,
		 min_size_rows, min_size_columns,
		 temp_reset,
		 alpha0,
		 gotinf = 0,
		 gotoutf = 0;


	n_c=0;
	multi=0;
	color_mode=DEFAULT_COLOR_MODE;
	need_lse=0;
	need_table=0;
	need_restart=0;
	restart_interval=0;
	components=0;
	T1=T2=T3=0;
#ifndef FIXRESET
	RESET=DEFAULT_RESET;
#endif
	
	/* Initialize NEAR to zero and loss-less mode */
	NEAR = DEF_NEAR;
	lossy = FALSE;

	/* Go through the arguments in command line */
	for ( i=1; i<argc; i++ )
	    if ( argv[i][0] == '-' )  {
			switch ( argv[i][1] ) {

			/* Enable use of Restart Markers */
			case 't':
				need_restart = 1;
				if ( sscanf(argv[i]+2,"%d",&restart_interval) != 1 ) {
					bad_flag(argv[i]);
				}
				break;

			/* Enable use of Mapping Tables */
			case 'm':
				need_table = 2;
				mappingtablefilename = argv[i]+2;
				break;

			/* Reset value */
			case 'r': 
				if ( sscanf(argv[i]+2,"%d",&temp_reset) != 1 ) {
					bad_flag(argv[i]);
				}
				if ( temp_reset != DEFAULT_RESET ) {
					need_lse = 1;
#ifdef FIXRESET
					fprintf(stderr,"ERROR: This version compiled with fixed RESET = %d, got %d\n",DEFAULT_RESET,temp_reset);
					exit(10);
#else
				RESET = temp_reset;
#endif
				}
			    break;

			/* Colour mode */
			case 'c':
				if ( sscanf(argv[i]+2,"%d",&color_mode) != 1 ) {
					bad_flag(argv[i]);
				}
				break;

			/* Sparse(?) mode */
			case 'p':
				if ( sscanf(argv[i]+2,"%d",&shift) != 1 ) {
					bad_flag(argv[i]);
				}
				if (shift!=0) {
					fprintf(stderr,"Sorry, sparse mode not implemented (shift=%d).\n",shift);
					exit(10);
				}
				break;

			/* Infile names */
			case 'i':
				infilename = c_infilename[components++] = argv[i]+2;
				gotinf = 1;
				break;

			/* Outfile names */
			case 'o':
				outfilename = argv[i]+2;
				gotoutf = 1;
				break;

			/* Verbose level */
			case 'v':
				if ( sscanf(argv[i],"-v%d",&verbose) != 1 ) {
					verbose=2;
				}
				break;

			/* Error level - if 0 then means loss-less mode */
			case 'e':
			case 'n':
				if ( sscanf(argv[i]+2,"%d",&NEAR) != 1 ) {
					bad_flag(argv[i]);
				}
				if ( NEAR == 0 )
					lossy = FALSE;
				else
					lossy = TRUE;
				break;

			/* Threshold Levels */
			case 's':
			case 'S':
			case 'T':
				need_lse = 1;
				switch(argv[i][2]) {

				case 'a':
					if ( sscanf(argv[i]+3,"%d",&T1) != 1 ) {
						bad_flag(argv[i]);
					}
					break;

				case 'b':
					if ( sscanf(argv[i]+3,"%d",&T2) != 1 ) {
						bad_flag(argv[i]);
					}
					break;

				case 'c':
					if ( sscanf(argv[i]+3,"%d",&T3) != 1 ) {
						bad_flag(argv[i]);
					}
					break;

				default:
					bad_flag(argv[i]);
					break;
				}
				break;

			default:
				usage();
				exit(0);
			}
	    }
	    else {
			infilename = c_infilename[components++] = argv[i];
			gotinf = 1;
	    }

			
	
	if ( verbose < 1 )
	    verbose = 1;  /* at least the banner will show */

	/* check that color mode is valid and pick color mode string */
	switch ( color_mode ) {
	    case PLANE_INT:
			color_mode_string = plane_int_string;
			multi=1;
			break;
	    case LINE_INT:
			color_mode_string = line_int_string;
			if (components>1) multi=1;
				break;
	    case PIXEL_INT:
			color_mode_string = pixel_int_string;
			if (components>1){
				fprintf(stderr,"ERROR: specified more than 1 input file in pixel interleaved mode\n");
				exit(10);
			}
			break;
	    default:
			fprintf(stderr,"ERROR: Invalid color mode %d\n",color_mode);
			usage();
			exit(10);
	}


	/* Assign file pointers to in files */
	if ( (infilename == NULL) && (multi==0 || components<1) ) {
		usage();
		exit(0);
	}
	else {
		if ( strcmp(infilename,"-") == 0 )
			in = stdin;
		else {
		  if (multi==0) {
			if ( (in=fopen(infilename,"rb")) == NULL ) {
			  perror(infilename);
			  exit(10);
			}
		  }
		  else {
		    for (i=0;i<components;i++)
				if ( (c_in[i]=fopen(c_infilename[i],"rb")) == NULL ) {
					perror(c_infilename[i]);
					exit(10);
				}
		  }
		}
	}


	/* Assigns pointers to out files */
	if ( outfilename == NULL ) {
		usage();
		exit(0);
	}
	else {
		if ( strcmp(outfilename,"-") == 0 ) {
			out = stdout;
			msgfile = stderr;
		}
		else if ( (out=fopen(outfilename,"wb")) == NULL ) {
			perror(outfilename);
			exit(10);
		}
	}

	/* Print messages */
	if ( verbose )
	    fprintf(msgfile,"%s\n",banner);


#define LESS_CONTEXTS 1

	if ( verbose>1 )
	    fprintf(msgfile,"Number of contexts (non-run): %d regular + %d EOR = %d\n",CONTEXTS-LESS_CONTEXTS,EOR_CONTEXTS,TOT_CONTEXTS-LESS_CONTEXTS);
	
	/* Read image headers*/
	if (multi==0) {
		if ( read_header_6(in, &columns, &rows, &alpha0, &components) != 0 )
			error("Could not read image header. Must be PPM or PGM file.\n");
		/* Single component => PLANE_INT */
		if ( (color_mode==LINE_INT || color_mode==PIXEL_INT) && components==1) {	
			/*
                        fprintf(msgfile,"Single component received: Color mode changed to PLANE INTERLEAVED\n");
			*/
			color_mode=PLANE_INT;
			color_mode_string = plane_int_string;
			multi=1;
			c_columns[0]=columns;
			c_rows[0] = rows;
			c_in[0]=in;
		}
	}
	else {
		for (i=0;i<components;i++) {
			if (read_header_5(c_in[i], &(c_columns[i]), &(c_rows[i]), &alpha0) != 0 )
				error("ERROR: Could not read image header. Must be PGM file.\n");
			if (i==0) {
				common_rows=c_rows[0];
				common_alpha=alpha0;
			}
			else if ((alpha0!=common_alpha)) {
				fprintf(stderr,"\nERROR: All components must have same maximal value\n");
				exit(10);
			}
		}
	}

#ifdef FIXALPHA
        alpha0++;
	if ( alpha0 != alpha ) {
	    fprintf(stderr, "Sorry, this version has been optimized for alphabet size = %d, got %d\n",alpha,alpha0);
	    exit(10);
	}
#else
	alpha = alpha0+1;  /* number read from file header is alpha-1 */
	ceil_half_alpha = (alpha+1)/2;
#endif

#ifdef POW2
	highmask = -alpha;
/* check that alpha is a power of 2 */
	for ( alpha0=alpha, i=-1; alpha0; alpha0>>=1, i++);
	if ( alpha != (1<<i) ) {
	    fprintf(stderr, "Sorry, this version has been optimized for alphabet size = power of 2, got %d\n",alpha);
	    exit(10);
	}
#endif	

	/* Check for 16 or 8 bit mode */
	if (alpha <= MAXA16 && alpha > MAXA8)
	{
		bpp16 = TRUE;
		lutmax = LUTMAX16;
	}
	else if (alpha <= MAXA8 && alpha >= 1)
	{
		bpp16 = FALSE;
		lutmax = LUTMAX8;
	}
	else { 
		fprintf(stderr,"Got alpha = %d\n",alpha);
		error("Bad value for alpha. Sorry...\n");
	}


	/* print out parameters */
	if ( verbose ) {
	    if (!multi)
			fprintf(msgfile,"Input  file: %s\nOutput file: %s\n",infilename,outfilename);
	    else {
			fprintf(msgfile,"Input  files: ");
			for (i=0;i<components;i++)
				fprintf(msgfile," %s ",c_infilename[i]);
			fprintf(msgfile,"\nOutput file: %s\n",outfilename);
	    }

	    if (!multi)
			fprintf(msgfile,"Image: cols=%d rows=%d alpha=%d comp=%d mode=%d (%s)",
				columns, rows, alpha, components, 
				color_mode, color_mode_string);
	    else {
			fprintf(msgfile,"Image: cols=");
			for (i=0;i<components;i++)
				fprintf(msgfile," %d",c_columns[i]);
			fprintf(msgfile," rows=");
			for (i=0;i<components;i++)
				fprintf(msgfile," %d",c_rows[i]);
			fprintf(msgfile," alpha=%d comp=%d mode=%d (%s)",
				alpha, components, color_mode,
				color_mode_string);
	    }

	    fprintf(msgfile,"\n");
 	}


	/* compute auxiliary parameters for near-lossless (globals) */
	if (lossy==TRUE) {
		quant = 2*NEAR+1;
		qbeta = (alpha + 2*NEAR + quant-1 )/quant;
		beta = quant*qbeta;
		ceil_half_qbeta = (qbeta+1)/2;
		negNEAR = -NEAR;
		if ( verbose )
			fprintf(msgfile,"Near-lossless mode: NEAR = %d  beta = %d  qbeta = %d\n",NEAR,beta,qbeta);
	}


	/* compute bits per sample for input symbols */
	for ( bpp=1; (1L<<bpp)<alpha; bpp++ );

	/* check if alpha is a power of 2: */
	if ( alpha != (1<<bpp) )
	    need_lse = 1; /* if not, MAXVAL will be non-default, and 
						 we'll need to specify it in an LSE marker */


	/* compute bits per sample for unencoded prediction errors */
	if (lossy==TRUE)
		for ( qbpp=1; (1L<<qbpp)<qbeta; qbpp++ );
	else
		qbpp = bpp;


	if ( bpp < 2 ) bpp = 2;
	
	/* limit for unary part of Golomb code */
	if ( bpp < 8 )
	    limit = 2*(bpp + 8) - qbpp -1;
	else
	    limit = 4*bpp - qbpp - 1;   


	/* check for smallest subsampled file and compute the sampling */
	if ((components>1) && (multi)) {
		min_size_columns=c_columns[components-1];
		min_size_rows=c_rows[components-1];
		for (i=0;i<components-1;i++) {
			if (c_columns[i]<min_size_columns) 
				min_size_columns=c_columns[i];
			if (c_rows[i]<min_size_rows) 
				min_size_rows=c_rows[i];
		}

		for (i=0;i<components;i++) {
			samplingx[i]=c_columns[i]/min_size_columns;
			samplingy[i]=c_rows[i]/min_size_rows;
			if ((samplingx[i]>4) || ((c_columns[i]%min_size_columns)!=0)) {
				fprintf(stderr,"\nImage sizes not compatible\n");
				exit(10);
			}
			if ((samplingy[i]>4) || ((c_rows[i]%min_size_rows)!=0)) {
				fprintf(stderr,"\nImage sizes not compatible\n");
				exit(10);
			}
		}

		min_size_columns=c_columns[0];
		whose_max_size_columns=0;
		min_size_rows=c_rows[0];
		whose_max_size_rows=0;

		for (i=1;i<components;i++) { 
			if (c_columns[i]>min_size_columns) {
				whose_max_size_columns=i;
				min_size_columns=c_columns[i];
			}
			if (c_rows[i]>min_size_rows) {
				whose_max_size_rows=i;
				min_size_rows=c_rows[i];
			}
		}
	}
	else {
	  for (i=0;i<components;i++) samplingx[i] = samplingy[i] = 1;
	}

	/* Allocate memory pools. */
	initbuffers(multi, components);  
}





int main (int argc, char *argv[]) {

    int n,n_c,n_r,my_i, number_of_scans, n_s, i;
	double t0, t1, get_utime();
	long tot_in = 0,
	     tot_out = 0,
	     pos0, pos1;
	int temp_columns;
	int MCUs_counted;


	pixel *local_scanl0,*local_scanl1,*local_pscanline,*local_cscanline;

	application_header = all_header = 0;

	/* Parse the parameters, initialize */
	initialize(argc, argv); 

	/* Start timer (must be AFTER initialize()) */
	t0 = get_utime();   

	/* Compute the number of scans */
	/* Multiple scans only for PLANE_INT in this implementation */

	if (color_mode==PLANE_INT)
		number_of_scans=components;
	else
		number_of_scans = 1;


	/* Write the frame header - allocate memory for jpegls header */
	head_frame = (jpeg_ls_header *) safecalloc(1,sizeof(jpeg_ls_header));
	for (n_s=0;n_s<number_of_scans;n_s++)
		head_scan[n_s] = (jpeg_ls_header *) safecalloc(1,sizeof(jpeg_ls_header));

	/* Assigns columns/rows to head_frame */
	if (!multi) {
		head_frame->columns=columns;
		head_frame->rows=rows;
	}
	else {
		head_frame->columns=c_columns[whose_max_size_columns];
		head_frame->rows=c_rows[whose_max_size_rows];
	}

	head_frame->alp=alpha;
	head_frame->comp=components;

	/* Assign component id and samplingx/samplingy */
	for (i=0;i<components;i++) {
		head_frame->comp_ids[i]=i+1;
		head_frame->samplingx[i]=samplingx[i];
		head_frame->samplingy[i]=samplingy[i];
	}

	head_frame->NEAR=NEAR; /* Not needed, scan information */
	head_frame->need_lse=need_lse; /* Not needed, for commpletness  */
	head_frame->color_mode=color_mode; /* Not needed, scan information */
	head_frame->shift=shift; /* Not needed, scan information */

	for (n_s=0;n_s<number_of_scans;n_s++) {
		head_scan[n_s]->alp = alpha;
		head_scan[n_s]->NEAR = NEAR;
		head_scan[n_s]->T1 = T1;
		head_scan[n_s]->T2 = T2;
		head_scan[n_s]->T3 = T3;
		head_scan[n_s]->RES = RESET;
		head_scan[n_s]->shift = shift;
		head_scan[n_s]->color_mode = color_mode;
	}


	if (color_mode==PLANE_INT) { /* One plane per scan */
		for (n_s=0;n_s<number_of_scans;n_s++) {
			head_scan[n_s]->comp=1;
			head_scan[n_s]->comp_ids[0]=n_s+1;
		}
	}
	else {
		for (n_s=0;n_s<number_of_scans;n_s++) {
			head_scan[n_s]->comp=head_frame->comp;
			for (n_c=0;n_c<head_frame->comp;n_c++)
				head_scan[n_s]->comp_ids[n_c]=n_c+1;
		}
	}
	
	/* Write SOI */
	all_header = write_marker(out, SOI);

	/* Write the frame */
	all_header += write_jpegls_frame(out, head_frame);

	/* End of frame header writing */


	if ((components>1) && (multi==0)) {

	/* Received PPM file, allocate auxiliary buffers */

		local_scanl0 = (pixel *)safecalloc(columns+LEFTMARGIN+RIGHTMARGIN,sizeof(pixel) );
		local_scanl1 = (pixel *)safecalloc(columns+LEFTMARGIN+RIGHTMARGIN,sizeof(pixel) );

		local_pscanline = local_scanl0 + LEFTMARGIN-1;
		local_cscanline = local_scanl1 + LEFTMARGIN-1;

	}


	/* Go through each scan and process line by line */
	for (n_s=0;n_s<number_of_scans;n_s++) {

		/* process scans one by one */

		if (n_s==0) {
			/* The thresholds for the scan. Must re-do per scan is change. */
			set_thresholds(alpha, NEAR, &T1, &T2, &T3);
			for (i=0;i<number_of_scans;i++) {
				head_scan[n_s]->T1=T1;
				head_scan[n_s]->T2=T2;
				head_scan[n_s]->T3=T3;
			}

			/* After the thresholds are set, write LSE marker if we have */
			/* non-default parameters or if we need a mapping table */
			if ( need_lse != 0 )
				all_header += write_jpegls_extmarker(out, head_scan[n_s], LSE_PARAMS, mappingtablefilename);
			if ( need_table != 0 )
				all_header += write_jpegls_extmarker(out, head_scan[n_s], LSE_MAPTABLE, mappingtablefilename);


			/* If using restart markers, write the DRI header */
			if ( need_restart != 0 )
			{	
				head_scan[n_s]->restart_interval = restart_interval;
				all_header += write_jpegls_restartmarker(out, head_scan[n_s]);
			}
			
			
			/* Print out parameters */
			if (verbose)
				fprintf(msgfile,"Parameters: T1=%d T2=%d T3=%d RESET=%d limit=%d\n",T1, T2, T3,RESET,limit);

			/* Prepare LUTs for context quantization */
			/* Must re-do when Thresholds change */
			prepareLUTs();

			if (lossy==TRUE)
				/* prepare div/mul tables for near-lossless quantization */
				prepare_qtables(alpha, NEAR);

			/* Check for errors */
			check_compatibility(head_frame, head_scan[0],0);

		}

		/* Restart Marker is reset after every scan */
		MCUs_counted = 0;

		/* Write the scan header */
		all_header += write_jpegls_scan(out, head_scan[n_s]);
		pos0 = ftell(out);  /* position in output file, after header */

		/* Initializations for each scan */
		/* Start from 1st image row */
		n=0;

		/* initialize stats arrays */
		if (lossy==TRUE)
			init_stats(qbeta);
		else
			init_stats(alpha);

		/* initialize run processing */
		init_process_run(MAXRUN);


		if (color_mode==LINE_INT) {	/* line interleaved */
			if (!multi) { 			/* Single file received */
/***********************************************************************/
/*           Line interleaved mode with single file received           */
/***********************************************************************/

				if (lossy==FALSE)

					/* LOSSLESS mode */
					while (++n <= rows) {

						read_one_line(cscanline + components, components*columns, in);

						tot_in += components*columns;

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c] = cscanline[n_c]=pscanline[components+n_c];

						for (n_c=0;n_c<components;n_c++) {
							if (components > 1) {
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++){
									local_cscanline[-1+my_i]=cscanline[-components+my_i*components+n_c];
									local_pscanline[-1+my_i]=pscanline[-components+my_i*components+n_c];
								}
							}
							else {
								local_cscanline=cscanline;
								local_pscanline=pscanline;
							}

							/* process the lines */
							lossless_doscanline(local_pscanline, local_cscanline, columns,n_c);
						}

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c]=cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}
					}

				else

					/* LOSSY mode */
					while (++n <= rows) {

						read_one_line(cscanline + components, components*columns, in);

						tot_in += components*columns;

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c] = cscanline[n_c]=pscanline[components+n_c];

						for (n_c=0;n_c<components;n_c++) {
							if (components > 1) {
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++){
									local_cscanline[-1+my_i]=cscanline[-components+my_i*components+n_c];
									local_pscanline[-1+my_i]=pscanline[-components+my_i*components+n_c];
								}
							}
							else {
								local_cscanline=cscanline;
								local_pscanline=pscanline;
							}

							/* process the lines */
							lossy_doscanline(local_pscanline, local_cscanline, columns,n_c);

							if (components>1)
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++)
									cscanline[-components+my_i*components+n_c]=local_cscanline[-1+my_i];
						}

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c]=cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}
					}

			}
			else {	/* Multiple files */
				/* color_mode==LINE_INT and multi==1  */

/***********************************************************************/
/*           Line interleaved mode with multiple files received        */
/***********************************************************************/
				n++;

				if (lossy==FALSE)

					/* LOSSLESS mode */
					while (n <= c_rows[whose_max_size_rows]) {

						for (n_c=0;n_c<components;n_c++) {
							for (n_r=0;n_r<samplingy[n_c];n_r++) {

								read_one_line(c_cscanline[n_c] + 1, c_columns[n_c], c_in[n_c]);

								tot_in += c_columns[n_c];

								/* 'extend' the edges */
								c_cscanline[n_c][-1]=c_cscanline[n_c][0]=c_pscanline[n_c][1];

								/* process the lines */
								lossless_doscanline(c_pscanline[n_c], c_cscanline[n_c], c_columns[n_c],n_c);

								/* 'extend' the edges */
								c_cscanline[n_c][c_columns[n_c]+1]=c_cscanline[n_c][c_columns[n_c]];

								/* make the current scanline the previous one */
								c_swaplines(n_c);
							}
						}	/* End of loop for each file */

						n+=samplingy[whose_max_size_rows];

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}

					}	/* End while of LINE_INT with multiple input files */

				else

					/* LOSSY mode */
					while (n <= c_rows[whose_max_size_rows]) {

						for (n_c=0;n_c<components;n_c++) {
							for (n_r=0;n_r<samplingy[n_c];n_r++) {

								read_one_line(c_cscanline[n_c] + 1, c_columns[n_c], c_in[n_c]);

								tot_in += c_columns[n_c];

								/* 'extend' the edges */
								c_cscanline[n_c][-1]=c_cscanline[n_c][0]=c_pscanline[n_c][1];

								/* process the lines */
								lossy_doscanline(c_pscanline[n_c], c_cscanline[n_c], c_columns[n_c],n_c);

								/* 'extend' the edges */
								c_cscanline[n_c][c_columns[n_c]+1]=c_cscanline[n_c][c_columns[n_c]];

								/* make the current scanline the previous one */
								c_swaplines(n_c);
							}
						}	/* End of loop for each file */

						n+=samplingy[whose_max_size_rows];

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}

					}	/* End while of LINE_INT with multiple input files */

			}	/* Closes the else, LINE_INT and multi=1 */

		}	/* Closes part for color_mode=LINE_INT */
		else {
			if (color_mode==PIXEL_INT) {
/***********************************************************************/
/*           Pixel interleaved mode with single file received          */
/***********************************************************************/

				if (lossy==FALSE)

					/* LOSSLESS mode */
					while (++n <= rows) {

						read_one_line(cscanline+components, components*columns, in);

						tot_in += components*columns;

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						/* process the lines */
						lossless_doscanline_pixel(pscanline, cscanline, components*columns);

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}
					}

				else

					/* LOSSY mode */
					while (++n <= rows) {

						read_one_line(cscanline+components, components*columns, in);

						tot_in += components*columns;

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						/* process the lines */
						lossy_doscanline_pixel(pscanline, cscanline, components*columns);

						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}
					}

			}	/* Closes if PIXEL_INT */
			else {	/* NON PIXEL_INT */
/***********************************************************************/
/*           Plane interleaved mode 								   */
/***********************************************************************/

				if (lossy==FALSE)
				
					/* LOSSLESS mode */
					while (++n <= c_rows[n_s]) {
						
						temp_columns = c_columns[n_s];

						read_one_line(c_cscanline[n_s]+1, temp_columns, c_in[n_s]);

						tot_in += temp_columns;

						/* 'extend' the edges */
						c_cscanline[n_s][-1]=c_cscanline[n_s][0]=c_pscanline[n_s][1];

						/* process the lines */
						lossless_doscanline(c_pscanline[n_s], c_cscanline[n_s], temp_columns, n_s);

						/* 'extend' the edges */
						c_cscanline[n_s][temp_columns+1] = c_cscanline[n_s][temp_columns];

						/* make the current scanline the previous one */
						c_swaplines(n_s);

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}

					}

				else

					/* LOSSY mode */
					while (++n <= c_rows[n_s]) {

						temp_columns = c_columns[n_s];

						read_one_line(c_cscanline[n_s]+1, temp_columns, c_in[n_s]);

						tot_in += temp_columns;

						/* 'extend' the edges */
						c_cscanline[n_s][-1]=c_cscanline[n_s][0]=c_pscanline[n_s][1];

						/* process the lines */
						lossy_doscanline(c_pscanline[n_s], c_cscanline[n_s], temp_columns,n_s);

						/* 'extend' the edges */
						c_cscanline[n_s][temp_columns+1] = c_cscanline[n_s][temp_columns];

						/* make the current scanline the previous one */
						c_swaplines(n_s);

						/* Insert restart markers if enabled */
						if (need_restart)
						{
							/* Insert restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitoflush();
								write_marker(out, (RSTm + ((MCUs_counted / restart_interval)%8)));
							}
							MCUs_counted++;
						}

					}

			}	/* End for each component in PLANE_INT */

		}	/* End for non LINE_INT */
		bitoflush();

	}	/* End of loop on scans */

	all_header += write_marker(out, EOI);

	/* Close down */
	close_process_run();
    pos1= closebuffers(multi);

	/* total bytes out, including JPEG-LS header, but not
	   application-specific header bytes */
	/* tot_out = (pos1-all_header)*8; */
	tot_out = pos1*8;

	t1 = get_utime();

	if (need_table)
		fprintf(msgfile, "Used the mapping table from file : %s\n",mappingtablefilename);

	if (need_restart)
		fprintf(msgfile, "Used restart markers with restart interval : %i\n", restart_interval);

	if ( verbose )
	    fprintf(msgfile,"Marker segment bytes: %ld\n",all_header);

	fprintf(msgfile,"Total bits out: %ld  Symbols in: %ld  %5.3lf bps  (%5.3lf : 1)\n",
		       tot_out,
		       tot_in,tot_out/(double)tot_in, 
		       (log((double)alpha)/log(2.0))*tot_in/tot_out);
	fprintf(msgfile,"Time = %1.3lf secs : %1.0lf KSymbols/sec\n",t1-t0,
					(tot_in)/(1024*(t1-t0)));

    return 0;                                       /* OK! */
}




/* Message to show how to use program */
usage()
{
	fprintf(stderr,"%s\n",banner);
	fprintf(stderr,"Usage: %s [flags] infile1 [infile2,infile3,...] [-ooutfile]\n\
infile1    : Input file: must be in PGM or PPM format\n\
infile2,...: Additional input files for \"plane interleaved\"\n\
	     or \"line interleaved\" modes. Must be in PGM (P5) format.\n\
FLAGS  :\n\
-i<infile> : Alternate input specification, use -i- for stdin.\n\
-o<outfile>: Output specification, use -o- for stdout (default=%s).\n\
-Ta<num>, -Tb<num>, -Tc<num>: thresholds for context quantization (a.k.a.\n\
	     T1,T2,T3; must have Ta<=Tb<=Tc<=maxs; defaults depend on alphabet\n\
	     size and lossless/near-lossless mode; see standard specification).\n\
-r<num>    : Reset interval for statistics (standard default=%d).\n\
", "locoe", OUTFILE COMPSUFFIX,DEFAULT_RESET);
	fprintf(stderr,"\
-c<num>    : Mode for multi-component images (program default=%d):\n\
	     %d:%s  %d:%s  %d:%s.\n",
	       DEFAULT_COLOR_MODE,
	       PLANE_INT, "plane-interleaved",
	       LINE_INT,  "line-interleaved",
	       PIXEL_INT, "sample-interleaved"
		     );
fprintf(stderr,"\
-n<error> or\n\
-e<error>  : Max allowed loss per symbol (default = %d).\n",
DEF_NEAR);

fprintf(stderr,"\
-m<table>  : Use mapping table where <table> is a file in the format:\n\
	       1st byte of <table> is the Table ID,\n\
	       2nd byte of <table> is the Width of each table entry (in bytes),\n\
	       3rd - 6th byte of <table> is the Max Table Index Value specified\n\
	                 as an integer (4 bytes),\n\
	       7th byte and on are the table entries.\n");
fprintf(stderr,"\
-t<num>    : Use Restart Markers where <num> is the restart interval \n\
             (ie. number of MCU's between restart markers).\n");

fprintf(stderr,"\
-h         : Print this help.\n");
    fprintf(stderr,"\
*** No spaces allowed between a flag and its argument.\n\
*** Use -Ta,-Tb,-Tc,-r only if you know what you are doing!\n\
");
}



/* Print out message for a bad flag */
bad_flag(char *s)
{
    fprintf(stderr,"Bad flag %s\n",s);
    usage();
    exit(10);
}



/* Functions that read the PGM header */

#define HEADER_MAXLINE 256

int read_header_6(FILE *fin, int *widthp, int *heightp, int *maxvalp, int *comp)
{
	char line[HEADER_MAXLINE];
	int  cols,rows,maxval;

	if ( nextline(line, fin) != 0 )
		return -10;

	if (strncmp(line,"P5",2)==0) *comp=1;
	else if (strncmp(line,"P6",2)==0) *comp=3;
	     else if (strncmp(line,"P7",2)==0) *comp=4;
		      else return -1;
	
	if ( nextline(line, fin) != 0 )
		return -10;
	
	if ( sscanf(line,"%d %d",&cols,&rows) != 2 )
		return -1;
	
	if ( nextline(line, fin) != 0 )
		return -10;

	if ( sscanf(line,"%d",&maxval) != 1 )
		return -1;
	
	*widthp = cols;
	*heightp = rows;
	*maxvalp = maxval;

	return 0;
}



int read_header_5(FILE *fin, int *widthp, int *heightp, int *maxvalp)
{
	char line[HEADER_MAXLINE];
	int  cols,rows,maxval;

	if ( nextline(line, fin) != 0 )
		return -10;

	if (strncmp(line,"P5",2)!=0)
		return -1;
	
	if ( nextline(line, fin) != 0 )
		return -10;
	
	if ( sscanf(line,"%d %d",&cols,&rows) != 2 )
		return -1;
	
	if ( nextline(line, fin) != 0 )
		return -10;

	if ( sscanf(line,"%d",&maxval) != 1 )
		return -1;
	
	*widthp = cols;
	*heightp = rows;
	*maxvalp = maxval;

	return 0;
}



/* Used to read in header lines of PGM/PPM files */
int nextline(char *line, FILE *fp)
{
	char *p;

	do {
		p = fgets(line, HEADER_MAXLINE, fp);
		/*
		if ( p != NULL )
		    fprintf(stderr,"%s",line);
		*/

	} while ( p != NULL && *p == '#' );

	if ( p==NULL )
		return -1;
	
	return 0;
}

