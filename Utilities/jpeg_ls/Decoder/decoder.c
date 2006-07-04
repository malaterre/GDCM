/* SPMG/JPEG-LS IMPLEMENTATION V.2.1
   =====================================
   These programs are Copyright (c) University of British Columbia. All right reserved.
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

/* decoder.c --- the main module, argument parsing, file I/O 
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
#include <string.h>
#include "jpegmark.h"

#define  PGMNAME PGMPREFIX "d"
#define  EPGMNAME PGMPREFIX "e"

static char *banner="\n\
=============================================\n\
SPMG/JPEG-LS DECOMPRESSOR " JPEGLSVERSION "\n\
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

pixel *pscanline, *cscanline, *pscanl0, *cscanl0;
pixel *c_pscanline[MAX_COMPONENTS], *c_cscanline[MAX_COMPONENTS],
      *c_pscanl0[MAX_COMPONENTS],	*c_cscanl0[MAX_COMPONENTS];

jpeg_ls_header *head_frame, *head_scan[MAX_SCANS];

int columns, rows, components,
    samplingx[MAX_COMPONENTS], samplingy[MAX_COMPONENTS];
int c_columns[MAX_COMPONENTS], c_rows[MAX_COMPONENTS];
int whose_max_size_columns, whose_max_size_rows, number_of_scans;
int	color_mode;
int shift;				/* Shift value for sparse images */
int	got_lse;			/* got an LSE marker */
int got_table;			/* got a mapping table */
int got_restart;		/* got a restart marker indicatino */
int restart_interval;	/* the restart interval */
int multi;          /* if the files are separate */
int	application_header;	/* application bytes in the header */

int lossy;						/* Indicates if in lossy mode or not */
int bpp16;						/* Indicates if 16 bits per pixel mode or not */
int lutmax;						/* lutmax is either 256 or 4501 */




/* reset */
#ifndef FIXRESET
int	RESET;
#endif


/* alphabet size */
#ifndef FIXALPHA
int     alpha,     /* alphabet size */
	ceil_half_alpha; /* ceil(alpha/2) */
#endif

#ifdef POW2
int     highmask;
#endif






/* Write one row of pixel values */
inline void write_one_line(pixel* line, int cols, FILE* outfile)
{

	int i, index;
	unsigned int* maptable;
			
	/* No mapping tables used */
	if(!(head_scan[0]->need_table))
		if (bpp16==FALSE)
		{
			unsigned char* line8;
			line8 = (unsigned char*)safealloc(cols);
	
			for (i=0; i< cols; i++)
				*(line8+i)=ENDIAN8(*(line+i));
		
			fwrite(line8, sizeof(unsigned char), cols, outfile);

			free(line8);
		} else {
			fwrite(line, sizeof(short), cols, outfile);
		}

	/* Mapping tables used */
	else
	{
		if (bpp16==FALSE)
		{
			/* Write one byte per table entry */
			if (head_scan[0]->Wt == 1)
			{
				unsigned char* line8;
				line8 = (unsigned char*)safealloc(cols);	/* If don't have 2, it mallocs over the table? */

				maptable = head_scan[0]->TABLE[head_scan[0]->TID];

				for (i=0; i<cols; i++)
				{
					index = *(line+i);
					*(line8+i) = ENDIAN8(maptable[index]);
				}

				fwrite(line8, sizeof(unsigned char), cols, outfile);

				free(line8);
			}
			/* Write two bytes per table entry */
			else if (head_scan[0]->Wt == 2)
			{
				unsigned short* line16;
				line16 = (unsigned short*)safealloc(cols*2);

				maptable = head_scan[0]->TABLE[head_scan[0]->TID];

				for (i=0; i<cols; i++)
				{
					index = *(line+i);
					*(line16+i) = (unsigned short) maptable[index];
				}

				fwrite(line16, sizeof(short), cols, outfile);

				free(line16);
			}
			/* Write three bytes per table entry */
			else if (head_scan[0]->Wt == 3)
			{
				unsigned char* line8_3;
				line8_3 = (unsigned char*)safealloc(cols*3);

				maptable = head_scan[0]->TABLE[head_scan[0]->TID];

				for (i=0; i<cols; i++)
				{
					index = *(line+i);
					*(line8_3 + (i*3)) =  (unsigned char) (maptable[index] >> 16);
					*(line8_3 + (i*3) + 1) = (unsigned char) (maptable[index] >> 8);
					*(line8_3 + (i*3) + 2) = (unsigned char) (maptable[index]);
				}

				fwrite(line8_3, sizeof(char), cols*3, outfile);

				free(line8_3);
			}

					
		/* Can't do 16 bit index values */
		}
		else
		{
			fprintf(stderr, "Sorry, mapping tables are only supported for 8 bpp images in this implementation.\n");
			exit(0);
		}
	}


}





void initbuffers(int multi, int comp) {

	int	i;

	if (multi) 		/* Output to several files */

	  for (i=0;i<comp;i++) {

	    c_pscanl0[i] = (pixel *)safecalloc((c_columns[i]+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );
	    c_cscanl0[i] = (pixel *)safecalloc((c_columns[i]+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );

	    /* Adjust scan line pointers taking into account the margins,
	       and also the fact that indexing for scan lines starts from 1
	     */
	    c_pscanline[i] = c_pscanl0[i] + (LEFTMARGIN-1);
	    c_cscanline[i] = c_cscanl0[i] + (LEFTMARGIN-1);
	  }

	else {			/* Output to a single file */

	  pscanl0 = (pixel *)safecalloc(components*(columns+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );
	  cscanl0 = (pixel *)safecalloc(components*(columns+LEFTMARGIN+RIGHTMARGIN), sizeof(pixel) );

	  /* Adjust scan line pointers taking into account the margins,
	     and also the fact that indexing for scan lines starts from 1
	     (this will probably have to be changed in the future) 
	   */
	  pscanline = pscanl0 + components*(LEFTMARGIN-1);
	  cscanline = cscanl0 + components*(LEFTMARGIN-1);
	}

    createzeroLUT();

}

swaplines()
{
	pixel *temp;
	temp = pscanl0;
	pscanl0 = cscanl0;
	cscanl0 = temp;
	pscanline = pscanl0 + components*(LEFTMARGIN-1);
	cscanline = cscanl0 + components*(LEFTMARGIN-1);
}

c_swaplines(int i)
{
	pixel *temp;
	temp = c_pscanl0[i];
	c_pscanl0[i] = c_cscanl0[i];
	c_cscanl0[i] = temp;
	c_pscanline[i] = c_pscanl0[i] + (LEFTMARGIN-1);
	c_cscanline[i] = c_cscanl0[i] + (LEFTMARGIN-1);
}

void closebuffers(int multi) {

	int     i;

	fclose(in);
	if (multi==0)
	   fclose(out);
        else
           for (i=0;i<components;i++)
	       fclose(c_out[i]);

        free(pscanl0);
        free(cscanl0);
}




int initialize(int argc, char *argv[]) {
	char line[256],tmp_char[1],   
		*infilename = NULL,
		*outfilename = OUTFILE ".out",
		*c_outfilename[MAX_COMPONENTS],
		*color_mode_string;
	int i, max_samp_columns, max_samp_rows, mk, n_s,
		end_of_seek=0,
		seek_return,
		alpha0,
		gotinf = 0,
		gotoutf = 0,
		out_files=0;
	int pos;   /* position in the file, after the header */

	for (i=0;i<MAX_COMPONENTS;i++) {
		c_outfilename[i]=malloc(strlen(OUTFILE)+20);
		sprintf(c_outfilename[i],"%s%d.out",OUTFILE,i+1);
	}

	multi=1;
	for ( i=1; i<argc; i++ )
		if ( argv[i][0] == '-' )
		{
			switch ( argv[i][1] ) {

			case 'i':
				infilename  = argv[i]+2;
				gotinf = 1;
				break;

			case 'o':
				outfilename = c_outfilename[out_files++] = argv[i]+2;
				gotoutf = 1;
				break;

			case 'P':
				multi=0;
				break;

			case 'v':
				if ( sscanf(argv[i],"-v%d",&verbose) != 1 )
					verbose=2;
				break;

			default:
				usage();
				exit(0);
			}
		}
	    else {
			if ( ! gotinf ) {
				infilename = argv[i];
				gotinf = 1;
			}
			else if ( ! gotoutf )
				outfilename = c_outfilename[out_files++] = argv[i];
		}
			
	if ( verbose < 1 )
	    verbose = 1;  /* at least the banner will show */

	if ((!multi) && (out_files>1)) {
		fprintf(stderr,"\nERROR: Only 1 output file expected with -P option.\nThis option is valid only for line/pixel interleaved and not subsampled.\n");
		exit(10);
	}

	/* Open in file */
	if ( infilename == NULL ) {
		usage();
		exit(0);
	}
	else {
		if ( strcmp(infilename,"-")==0 )
			in = stdin;
		else if ( (in=fopen(infilename,"rb")) == NULL ) {
			perror(infilename);
			exit(10);
		}
	}

	/* Read the compressed image frame header */
	bufiinit(in);

	head_frame = (jpeg_ls_header *) safecalloc(1,sizeof(jpeg_ls_header));

	for (n_s=0;n_s<MAX_SCANS;n_s++) {
		head_scan[n_s] = (jpeg_ls_header *) safecalloc(1,sizeof(jpeg_ls_header));
		head_scan[n_s]->T1=head_scan[n_s]->T2=head_scan[n_s]->T3=0;
		head_scan[n_s]->RES = DEFAULT_RESET;
	}

	/* Read SOI */
	seek_return = seek_marker(in,&mk);
	if (seek_return == EOF) {
		fprintf(stderr,"*** Premature End of File seeking SOI\n");
		exit(10);
	}
	else {
		pos = seek_return;
		if (mk != SOI) {
			fprintf(stderr,"Marker %04x found: first marker must be SOI (%04x) in this implementation\n", mk, SOI);
			exit(10);
		}
	}

	/* Read SOF_LS */
	seek_return = seek_marker(in,&mk);
	if (seek_return == EOF) {
	  fprintf(stderr,"*** Premature End of File seeking SOF_LS\n");
	  exit(10);
	}
	else {
		pos += seek_return; /* Read SOF_LS */
		if (mk != SOF_LS) {
			fprintf(stderr,"Marker %04x found: second marker must be SOF_LS (%04x) in this implementation\n", mk, SOF_LS);
			exit(10);
		}
	}

	/* Read the frame header (SOF) */
	seek_return = read_jpegls_frame(in,head_frame);
	if (seek_return == EOF) {
		fprintf(stderr,"*** Premature End of File reading frame header\n");
		exit(10);
	}
	else
		pos += seek_return;

	head_scan[0]->alp = head_frame->alp;    /* default alpha */


	/* LSE Extension header */
	/* This version supports only 2 extension headers, and 1 set of
	   parameters for all the scans */
	got_lse = 0;
	head_scan[0]->need_table = 0;

	while (!end_of_seek)
	{
		seek_return=seek_marker(in, &mk);
		if (seek_return == EOF) {
			fprintf(stderr,"*** Premature End of File seeking SOS or LSE marker\n");
			exit(10);
		}
		pos +=seek_return;


		switch(mk)
		{
		case LSE:
			seek_return = read_jpegls_extmarker(in, head_scan[0]);
			if (seek_return == EOF) {
				fprintf(stderr,"*** Premature End of File\n");
				exit(10);
			}
			pos += seek_return;
			got_lse = 1;
			break;
		
		case DRI:
			seek_return = read_jpegls_restartmarker(in, head_scan[0]);
			pos += seek_return;
			got_restart = 1;
			restart_interval = head_scan[0]->restart_interval;
			break;
		
		case SOS:
			end_of_seek=1;	
			break;
		}
	}
	/* End of extension header */



	/* Read the scan header*/
	seek_return = read_jpegls_scan(in,head_scan[0]);
	if (seek_return == EOF) {
		fprintf(stderr,"*** Premature End of File reading scan marker segment\n");
		exit(10);
	}
	pos+=seek_return;

	shift=head_scan[0]->shift;
	if (shift!=0) {
		fprintf(stderr,"Got shift = %d != 0 : not implemented.\n",shift);
		exit(10);
	}

	NEAR=head_scan[0]->NEAR;
	color_mode=head_scan[0]->color_mode;
	columns=head_frame->columns;
	rows=head_frame->rows;
	alpha0=head_scan[0]->alp;
	head_frame->alp = alpha0;
	components=head_frame->comp;

	if (color_mode==PLANE_INT) 
		number_of_scans=components;
	else
		number_of_scans=1;

	set_thresholds(head_scan[0]->alp, head_scan[0]->NEAR, &(head_scan[0]->T1), &(head_scan[0]->T2), &(head_scan[0]->T3));
	T1=head_scan[0]->T1;
	T2=head_scan[0]->T2;
	T3=head_scan[0]->T3;

#ifndef FIXRESET
	RESET=head_scan[0]->RES;
#else
	if (head_scan[0]->RES != DEFAULT_RESET) {
		fprintf(stderr,"ERROR: Version compiled for fixed RESET=%d parameter: got %d\n",DEFAULT_RESET,head_scan[0]->RES);
		exit(10);
	}
#endif

	/* Check to see if lossless or lossy */
	if (NEAR == 0)
		lossy=FALSE;
	else
		lossy=TRUE;

	/* Check for 16 or 8 bit mode */
	if (alpha0 <= MAXA16 && alpha0 > MAXA8)
	{
		/* 16 bit */
		bpp16 = TRUE;
		lutmax = LUTMAX16;
	}
	else if (alpha0 <= MAXA8 && alpha0 >= 1)
	{
		/* 8 bit */
		bpp16 = FALSE;
		lutmax = LUTMAX8;
	}
	else { 
		fprintf(stderr,"Got alpha = %d\n",alpha0+1);
		error("Bad value for alpha. Sorry...\n");
	}


	check_compatibility(head_frame,head_scan[0],0);

	for (i=0;i<components;i++) {
		samplingx[i]=head_frame->samplingx[i];
		samplingy[i]=head_frame->samplingy[i];
		if ((!multi) && ((samplingx[i]!=1) || (samplingy[i]!=1)) && (components>1))
		{
			fprintf(stderr,"\nERROR: Cannot use -P (PPM output) with subsampled compressed components\n");
			exit(10);
		}
	}

	if ((!multi) && (color_mode==PLANE_INT))
		if (components>1) {
			fprintf(stderr,"\nERROR: Cannot use -P (PPM output) with plane intereleaved mode\n");
			exit(10);
		}
	else multi=1;

	if ((multi) && (color_mode==PIXEL_INT)) {
		multi = 0;   /* equivalent to specifying -P flag */
	}

	if ((out_files>1) && (color_mode==PIXEL_INT)) {
		fprintf(stderr,"ERROR: Pixel interleaved mode uses only 1 output file\n");
		exit(10);
	}

	if ((multi) && (out_files) && (out_files!=components)) {
		fprintf(stderr,"ERROR: Number of files, %d%, for output must be equal to number of image components, %d\n",out_files,components);
		exit(10);
	}

	/* Compute the image size for the different components */
	if (components==1) {
		c_columns[0]=columns;
		c_rows[0]=rows;
		whose_max_size_rows=0;
		samplingy[0]=1;
	}
	else
	{
		max_samp_columns=0;
		max_samp_rows=0;
		for(i=0;i<components;i++) {
			if (samplingx[i]>max_samp_columns) {
				max_samp_columns=samplingx[i];
				whose_max_size_columns=i;
			}
			if (samplingy[i]>max_samp_rows) {
				max_samp_rows=samplingy[i];
				whose_max_size_rows=i;
			}
		}

		c_columns[whose_max_size_columns]=columns;	
		c_rows[whose_max_size_rows]=rows;

		for(i=0;i<components;i++) {
			if (i!=whose_max_size_columns)
			{
				c_columns[i]=c_columns[whose_max_size_columns]*samplingx[i];
				c_columns[i]/=samplingx[whose_max_size_columns];
			}
			if (i!=whose_max_size_rows) {
				c_rows[i]=c_rows[whose_max_size_rows]*samplingy[i];
				c_rows[i]/=samplingy[whose_max_size_rows];
			}
		}
	}


	/* Open out file */
	if ( outfilename == NULL ) {
		usage();
		exit(0);
	}
	else {
		if ( strcmp(outfilename,"-")==0 ) {
			out = stdout;
			msgfile = stderr;
		}
		else {
			if (multi==0) {
				if ( (out=fopen(outfilename,"wb")) == NULL ) {
					perror(outfilename);
					exit(10);
				}
			}
			else 
				for (i=0;i<components;i++)
					if ( (c_out[i]=fopen(c_outfilename[i],"wb")) == NULL )
					{
						perror(c_outfilename[i]);
						exit(10);
					}
			
		}
	}


	/* check that color mode is valid and pick color mode string */
	switch ( color_mode ) {

	case PLANE_INT:
		color_mode_string = plane_int_string;
		break;

	case LINE_INT:
		color_mode_string = line_int_string;
		break;
	
    case PIXEL_INT:
		color_mode_string = pixel_int_string;
		break;

	default:
		fprintf(stderr,"ERROR: Invalid color mode %d\n",color_mode);
		usage();
		exit(10);
	}

	if ( verbose ) {
	    fprintf(msgfile,"%s\n",banner);
	}

	if ( verbose ) {
		if (!multi) {
			fprintf(msgfile,"Input  file: %s\nOutput file: %s\n",infilename,outfilename);
	    }
	    else {
			fprintf(msgfile,"Input  file: %s\nOutput files: ",infilename);
			for (i=0;i<components;i++)
				fprintf(msgfile," %s ",c_outfilename[i]);
			fprintf(msgfile,"\n");
		}
	}

#ifdef FIXALPHA
	if ( alpha0 != alpha ) {
	    fprintf(stderr, "Sorry, this version has been optimized for alphabet size = %d, got %d\n",alpha,alpha0);
	    exit(10);
	}
#else
	alpha = alpha0;
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

	if (lossy==TRUE)
	{
		/* compute auxiliary parameters for near-lossless (globals) */
		quant = 2*NEAR+1;
		qbeta = (alpha + 2*NEAR + quant-1 )/quant;
		beta = quant*qbeta;
		ceil_half_qbeta = (qbeta+1)/2;
		negNEAR = -NEAR;
		alpha1eps = alpha-1+NEAR;
		fprintf(msgfile,"Near-lossless mode: NEAR = %d  beta = %d  qbeta = %d\n",NEAR,beta,qbeta);
	}

	/* compute bits per sample for input symbols */
	for ( bpp=1; (1L<<bpp)<alpha; bpp++ );

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

	/* print out parameters */
	if ( verbose ) {
	    if (!multi)
		fprintf(msgfile,"Image: cols=%d rows=%d alpha=%d comp=%d mode=%d (%s)\nParameters: Ta=%d Tb=%d Tc=%d RESET=%d limit=%d",
			 columns, rows, alpha0, components, 
			 color_mode, color_mode_string,
			 T1, T2, T3, RESET,limit);
	    else {
			fprintf(msgfile,"Image: cols=");
			for (i=0;i<components;i++)
				fprintf(msgfile," %d",c_columns[i]);
			fprintf(msgfile," rows=");
			for (i=0;i<components;i++)
				fprintf(msgfile," %d",c_rows[i]);
			fprintf(msgfile," alpha=%d comp=%d mode=%d (%s)\nParameters: Ta=%d Tb=%d Tc=%d RESET=%d limit=%d",
				 alpha0, components, 
				color_mode, color_mode_string,
				T1, T2, T3,RESET,limit);
		}
	}

	if ( verbose )
	    fprintf(msgfile,"\n");


	/* Write out the image header for PGM or PPM files */
	/* Must look at if there are Mapping Tables used */

	/* No Mapping Tables used */
	if (!head_scan[0]->need_table)
	{
		if (!multi) {
			if (components==1) fputs("P5\n", out);
			else if (components==3) fputs("P6\n", out);	
			else if (components==4) fputs("P7\n", out);
			else fprintf(out,"P%d\n",10+components);
       	
			fprintf(out,"%d %d\n", columns, rows);
			fprintf(out,"%d\n", alpha - 1);
		}
		else
			for (i=0;i<components;i++) {
				fputs("P5\n", c_out[i]);
				fprintf(c_out[i],"%d %d\n", c_columns[i], c_rows[i]);
				fprintf(c_out[i],"%d\n", alpha - 1);
			}
	}

	/* Mapping Tables used */
	else
	{
		/* only 8 bit indexes supported for mapping tables */
		if (bpp16==TRUE)
		{
			fprintf(stderr, "Sorry, mapping tables are only supported for 8 bpp images in this implementation.\n");
			exit(0);
		}

		/* Mapping Table elements are 1 or 2 bytes */
		if (head_scan[0]->Wt==1 || head_scan[0]->Wt==2)
		{
			int alpha_temp;
			if (head_scan[0]->Wt==1)
				alpha_temp = alpha;
			else
				alpha_temp = alpha*alpha;

			if (!multi) 
			{
				if (components==1) fputs("P5\n", out);
				else if (components==3) fputs("P6\n", out);	
				else if (components==4) fputs("P7\n", out);
				else fprintf(out,"P%d\n",10+components);
       	
				fprintf(out,"%d %d\n", columns, rows);
				fprintf(out,"%d\n", alpha_temp - 1);
			}
			else
				for (i=0;i<components;i++) 
				{
					fputs("P5\n", c_out[i]);
					fprintf(c_out[i],"%d %d\n", c_columns[i], c_rows[i]);
					fprintf(c_out[i],"%d\n", alpha_temp - 1);
				}
		}
		
		/* Mapping Table elements are 3 bytes */
		else if (head_scan[0]->Wt==3)
		{
			if (!multi) 
			{
				if (components==1) fputs("P6\n", out);
				else
				{
					fprintf(stderr,"Error : Cannot have a multi-component image and a mapping table with 3 bytes per element.\n");
					exit(0);
				}

				fprintf(out,"%d %d\n", columns, rows);
				fprintf(out,"%d\n", alpha - 1);
			}
			else
				for (i=0;i<components;i++) 
				{
					fputs("P6\n", c_out[i]);
					fprintf(c_out[i],"%d %d\n", c_columns[i], c_rows[i]);
					fprintf(c_out[i],"%d\n", alpha - 1);
				}
		}

		/* Mapping Table elements aren't 1 to 3 bytes */
		else
		{
			fprintf(stderr, "Sorry, mapping tables elements can only be 1 to 3 bytes in this implementation.\n");
			exit(0);
		}
	}
		

	/* Allocate memory pools. */
	initbuffers(multi, components);


	/* return size of the header, in bytes */
	return pos;

}





/* Main loop for decoding files */

int main (int argc, char *argv[]) {
	int n,n_c,n_r,my_i,n_s,mk,seek_return;
	int found_EOF = 0;
	double t0, t1, get_utime();
	long pos0, pos1,    
		tot_in = 0,
		tot_out = 0;
	pixel *local_scanl0,*local_scanl1,*local_pscanline,*local_cscanline;
	int MCUs_counted;
	
	
	/* Parse the parameters, initialize */
	/* Not yet fully implemented */
	bufiinit();
	pos0 = initialize(argc, argv); 


	/* start timer (must be AFTER initialize()) */
	t0 = get_utime();


	/* Initialize the scanline buffers */
	if (!multi)
		for (n = 0; n <= (columns + 1); ++n)
			pscanline[n] = 0;       
	else
		for (n_c=0;n_c<components;n_c++)
			for (n = 0; n <= (c_columns[n_c] + 1); ++n)
				c_pscanline[n_c][n] = 0;       

	if ((components>1) && (multi==0))
	{
		/* OUTPUT PPM file, allocate auxiliary buffers */
		local_scanl0 = (pixel *)safecalloc(columns+LEFTMARGIN+RIGHTMARGIN,sizeof (pixel) );
		local_scanl1 = (pixel *)safecalloc(columns+LEFTMARGIN+RIGHTMARGIN,sizeof (pixel) );

		local_pscanline = local_scanl0 + LEFTMARGIN-1;
		local_cscanline = local_scanl1 + LEFTMARGIN-1;
	}


	for (n_s=0;n_s<number_of_scans;n_s++)
	{
		/* Repeat prediction/quantization/statistics scanline by scanline,
		   for each scan. */

		/* Reset Restart Markers for every scan */
		MCUs_counted = 0;
		
		/* This implementation supports parameters in 1st scan */
		if (n_s==0)
		{
			/* Prepare the quantization LUTs */
			prepareLUTs();

			if (lossy==TRUE)
				/* prepare div/mul tables for near-lossless quantization */
				prepare_qtables(alpha,NEAR);

		}
		else
		{	/* Read further scan headers */
			seek_return=seek_marker(in,&mk);
			if (seek_return == EOF)
			{
				fprintf(stderr,"*** Premature End of File seeking SOS marker\n");
				exit(10);
			}
			if ( seek_return > 2 )
			{
				fprintf(msgfile,"*** WARNING: %d extra bytes between end of scan and next marker.\n",seek_return-2);
				fprintf(msgfile,"***          Added to marker segment count.\n");
			}
			pos0 +=seek_return;
			if (mk != SOS)
			{
				fprintf(stderr,"Expecting SOS (%04x), got %04x\n",SOS,mk);
				exit(10);
			}
			seek_return = read_jpegls_scan(in,head_scan[n_s]); /* Read the scan header*/
			if (seek_return == EOF)
			{
				fprintf(stderr,"*** Premature End of File reading scan marker segment\n");
				exit(10);
			}
			pos0+=seek_return;
			if (head_scan[n_s]->shift!=0)
			{
				fprintf(stderr,"Got shift = %d != 0 : not implemented.\n",head_scan[n_s]->shift);
				exit(10);
			}
			if (head_scan[n_s]->NEAR != NEAR)
			{
				fprintf(stderr,"Got NEAR=%d after NEAR=%d: cannot change parameters between scans in this implementation\n",head_scan[n_s]->NEAR,NEAR);
				exit(10);
			}
			if ((head_scan[n_s]->color_mode != PLANE_INT) || (head_scan[n_s]->comp != 1) ||
				(head_scan[n_s]->comp_ids[0] != n_s+1))
			{
				fprintf(stderr,"This implementation supports multiple scans only in PLANE INTERLEAVED mode.\n");
				exit(10);
			}
		}

		/* Initializations for each scan */
		bitiinit();

		/* Start from 1st image row */
		n=0;

        /* Initialize stats arrays */
		if (lossy==TRUE)
			init_stats(qbeta);
		else
			init_stats(alpha);

		/* Initialize run processing */
		init_process_run(MAXRUN);

		if (color_mode==LINE_INT) {		/* line int. */
			if (!multi) {
/***********************************************************************/
/*           Line interleaved mode with single file received           */
/***********************************************************************/

				if (lossy==FALSE)
					
					/* LOSSLESS MODE */
					while (++n <= rows)
					{
						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						for (n_c=0;n_c<components;n_c++)
						{
							if (components>1)
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++)
								{
									local_cscanline[-1+my_i]=cscanline[-components+my_i*components+n_c];
									local_pscanline[-1+my_i]=pscanline[-components+my_i*components+n_c];
								}
							else 
							{
								local_cscanline=cscanline;
								local_pscanline=pscanline;
							}

							if ( lossless_undoscanline(local_pscanline, local_cscanline, columns, n_c ) != 0 )
							{
								fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
								found_EOF = 1;
								break;
							}

							if (components>1)
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++)
									cscanline[-components+my_i*components+n_c]=local_cscanline[-1+my_i];
						}

						write_one_line(cscanline + components, components*columns, out);

						tot_out += components*columns;

						/* extend the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of while loop for each file line */

				else

					/* LOSSY MODE */
					while (++n <= rows)
					{
						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						for (n_c=0;n_c<components;n_c++)
						{
							if (components>1)
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++)
								{
									local_cscanline[-1+my_i]=cscanline[-components+my_i*components+n_c];
									local_pscanline[-1+my_i]=pscanline[-components+my_i*components+n_c];
								}
							else 
							{
								local_cscanline=cscanline;
								local_pscanline=pscanline;
							}

							if ( lossy_undoscanline(local_pscanline, local_cscanline, columns, n_c ) != 0 )
							{
								fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
								found_EOF = 1;
								break;
							}

							if (components>1)
								for (my_i=0;my_i<columns+LEFTMARGIN+RIGHTMARGIN;my_i++)
									cscanline[-components+my_i*components+n_c]=local_cscanline[-1+my_i];
						}

						write_one_line(cscanline + components, components*columns, out);

						tot_out += components*columns;

						/* extend the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of while loop for each file line */

			}
			else
			{		/* Multiple files */
			/* color_mode==LINE_INT and multi==1 */
/***********************************************************************/
/*           Line interleaved mode with multiple files received        */
/***********************************************************************/

				n++;

				if (lossy==FALSE)

					/* LOSSLESS MODE */
					while (n <= c_rows[whose_max_size_rows])
					{
						for (n_c=0;n_c<components;n_c++)
						{
							for (n_r=0;n_r<samplingy[n_c];n_r++)
							{

								/* 'extend' the edges */
								c_cscanline[n_c][-1]=c_cscanline[n_c][0]=c_pscanline[n_c][1];

								if ( lossless_undoscanline(c_pscanline[n_c], c_cscanline[n_c], c_columns[n_c], n_c ) != 0 )
								{
									fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
									found_EOF = 1;
									break;
								}

								write_one_line(c_cscanline[n_c] + 1, c_columns[n_c], c_out[n_c]);

								tot_out += c_columns[n_c];

								/* extend the edges */
								c_cscanline[n_c][c_columns[n_c]+1] = c_cscanline[n_c][c_columns[n_c]];

								/* make the current scanline the previous one */
								c_swaplines(n_c);
							}
						}	/* End of for loop for each component */

						n+=samplingy[whose_max_size_rows];

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of while loop for each line */

				else

					/* LOSSY MODE */
					while (n <= c_rows[whose_max_size_rows])
					{
						for (n_c=0;n_c<components;n_c++)
						{
							for (n_r=0;n_r<samplingy[n_c];n_r++)
							{

								/* 'extend' the edges */
								c_cscanline[n_c][-1]=c_cscanline[n_c][0]=c_pscanline[n_c][1];

								if ( lossy_undoscanline(c_pscanline[n_c], c_cscanline[n_c], c_columns[n_c], n_c ) != 0 )
								{
									fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
									found_EOF = 1;
									break;
								}

								write_one_line(c_cscanline[n_c] + 1, c_columns[n_c], c_out[n_c]);

								tot_out += c_columns[n_c];

								/* extend the edges */
								c_cscanline[n_c][c_columns[n_c]+1] = c_cscanline[n_c][c_columns[n_c]];

								/* make the current scanline the previous one */
								c_swaplines(n_c);
							}
						}	/* End of for loop for each component */

						n+=samplingy[whose_max_size_rows];

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of while loop for each line */


			}		/* Closes the else, LINE_INT and multi=1 */

		}		/* End of part for LINE_INT */

		else {		/* Non LINE_INT mode */
			if (color_mode==PIXEL_INT) {
/***********************************************************************/
/*           Pixel interleaved mode with single file received          */
/***********************************************************************/

				if (lossy==FALSE)
				
					/* LOSSLESS MODE */
					while (++n <= rows)
					{
						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						if ( lossless_undoscanline_pixel(pscanline, cscanline, components*columns) != 0 )
						{
							fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows,n-1);
							found_EOF = 1;
							break;
						}

						write_one_line(cscanline+components, components*columns, out);
		
						tot_out += components*columns;

						/* extend the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of line loop for PIXEL_INT */


				else

					/* LOSSY MODE */
					while (++n <= rows)
					{
						/* 'extend' the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[-components+n_c]=cscanline[n_c]=pscanline[components+n_c];

						if ( lossy_undoscanline_pixel(pscanline, cscanline, components*columns) != 0 )
						{
							fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows,n-1);
							found_EOF = 1;
							break;
						}

						write_one_line(cscanline+components, components*columns, out);

						tot_out += components*columns;

						/* extend the edges */
						for (n_c=0;n_c<components;n_c++)
							cscanline[components*(columns+1)+n_c] = cscanline[components*columns+n_c];

						/* make the current scanline the previous one */
						swaplines();

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of line loop for PIXEL_INT */

			}
			else {
/***********************************************************************/
/*           Plane interleaved mode 				       */
/***********************************************************************/

				if (lossy==FALSE)
				
					/* LOSSLESS MODE */
					while (++n <= c_rows[n_s])
					{
						/* 'extend' the edges */
						c_cscanline[n_s][-1]=c_cscanline[n_s][0]=c_pscanline[n_s][1];

						if (lossless_undoscanline(c_pscanline[n_s], c_cscanline[n_s], c_columns[n_s], n_s ) != 0 )
						{
							fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
							found_EOF = 1;
							break;
						}

						write_one_line(c_cscanline[n_s]+1, c_columns[n_s], c_out[n_s]);

						tot_out += c_columns[n_s];

						/* extend the edges */
						c_cscanline[n_s][c_columns[n_s]+1] = c_cscanline[n_s][c_columns[n_s]];

						/* make the current scanline the previous one */
						c_swaplines(n_s);

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of line loop in PLANE_INT */
				
				else

					/* LOSSY MODE */
					while (++n <= c_rows[n_s])
					{
						/* 'extend' the edges */
						c_cscanline[n_s][-1]=c_cscanline[n_s][0]=c_pscanline[n_s][1];

						if (lossy_undoscanline(c_pscanline[n_s], c_cscanline[n_s], c_columns[n_s], n_s ) != 0 )
						{
							fprintf(stderr,"*** Premature EOF: expected %d rows, got %d\n",rows, n-1);
							found_EOF = 1;
							break;
						}

						write_one_line(c_cscanline[n_s]+1, c_columns[n_s], c_out[n_s]);

						tot_out += c_columns[n_s];

						/* extend the edges */
						c_cscanline[n_s][c_columns[n_s]+1] = c_cscanline[n_s][c_columns[n_s]];

						/* make the current scanline the previous one */
						c_swaplines(n_s);

						/* Take out the Restart Markers */
						if (got_restart)
						{
							/* Look for restart markers only after a restart interval */
							if ((MCUs_counted % restart_interval) == 0)
							{
								bitiflush();
								read_n_bytes(in, 2);	/* read the RST marker */
								bitiinit();
							}
							MCUs_counted++;
							
						}

					}	/* End of line loop in PLANE_INT */

			}	/* End of each component for PLANE_INT */

		}	/* End of non LINE_INT */

		bitiflush();

	} /* End of loop for scans */


	mk = 0;

	/* Read EOI */
	seek_return=seek_marker(in,&mk);
	if (seek_return==EOF)
	{
		fprintf(stderr,"Did not get EOI at end of compressed image\n");
		exit(10);
	}
	if ( seek_return > 2 )
	{
	    fprintf(msgfile,"*** WARNING: %d extra bytes between end of scan and next marker.\n",seek_return-2);
	    fprintf(msgfile,"***          Added to marker segment count.\n");
	}

	pos0 += seek_return;
	if (mk != EOI)
	{
	  fprintf(stderr,"In this implementation last marker must be EOI\n");
	  exit(10);
	}

	if (head_scan[0]->need_table)
		fprintf(msgfile,"A mapping table was used which had %i entries of %i bytes each.\n",head_scan[0]->MAXTAB, head_scan[0]->Wt);

	if (got_restart)
		fprintf(msgfile,"Restart markers were found with a restart interval of %i.\n",restart_interval);

	if ( verbose )
		fprintf(msgfile,"Marker segment bytes: %ld\n",pos0);

	/* position in input file */
	pos1 = ftell(in);
	/* tot_in = 8*(pos1-pos0); */

	/* size of compressed file read (bits), incl. headers. */
	tot_in = 8*pos1;

	/* Close down */
	close_process_run();
	closebuffers(multi);


	t1 = get_utime();
	fprintf(msgfile,"Total bits  in: %ld  Symbols out: %ld  %5.3lf bps\n",
		       tot_in,tot_out,tot_in/(double)tot_out);
	fprintf(msgfile,"Time = %1.3lf secs : %1.0lf KSymbols/sec\n",t1-t0,
					(tot_out)/(1024*(t1-t0)));

	if ( found_EOF )
		exit(0);
	else
		return 1;
}




usage()
{
	fprintf(stderr,"Usage: %s [flags] [infile] [outfile1 [outfile2, ...]]\n\
DEFAULTS:\n\
infile   = %s.\n\
outfile1 = %s for color image in a single (PPM) output file.\n\
outfile1 = %s for monochrome image in a single (PGM) output file.\n\
outfile[1,2,...] = %s for multiple (PGM) output files \n\
	   in plane or line interleaved modes.\n",
	  "locod", "specified JLS file", OUTFILE ".out", 
	  OUTFILE "1.out",
	  OUTFILE "[1,2,...].out");
fprintf(stderr,"FLAGS:\n\
outfile2, ... : Multiple output specification for plane or line int. mode.\n\
-i<infile>    : Alternate input specification, use -i- for stdin.\n\
-o<outfile>   : Alternate output specification, use -o- for stdout.\n\
-P            : Generate single (.ppm) output file for sample/line int. mode.\n\
");
    fprintf(stderr,"\
-h            : Print this help.\n\
*** No spaces allowed between a flag and its argument.\n\
");
	
}


bad_flag(char *s)
{
    fprintf(stderr,"Bad flag %s\n",s);
    usage();
    exit(10);
}

