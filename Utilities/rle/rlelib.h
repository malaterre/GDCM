/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __rlelib_h
#define __rlelib_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RLE_LIB_VERSION 0.0.1

typedef struct
{
  uint32_t num_segments;
  uint32_t offset[15];
  void (*print_header) (void);
} rle_header;

typedef struct
{
  rle_header * header;
} rle_compressed_frame;

typedef struct
{
  rle_header * header;
} rle_decompressed_frame;

typedef struct
{
  int (*fill_input_buffer) (rle_decompressed_frame*);
} source_mgr;

typedef struct
{
  int output_scanline;
  int output_height;
  //int bits_allocated; // 8 or 16, when 16 need to do padded composite
  int row;
  int col;
  FILE *stream;
  int current_segment;
  rle_header *header;
} rle_decompress_struct;

void rle_stdio_src(rle_decompress_struct *cinfo, FILE *infile, int *dims)
{
  int i;
  //is.read((char*)(&Header), sizeof(uint32_t)*16);
  size_t len = fread(cinfo->header, sizeof(uint32_t), 16, infile);
  cinfo->row = dims[0];
  cinfo->col = dims[1];
  if( cinfo->header->num_segments > 16 || cinfo->header->num_segments < 1 )
    {
    // Need to throw something here
      abort();
    }
  if( cinfo->header->offset[0] != 64 )
    {
    // Need to throw something here
      abort();
    }
  for(i=1; i < cinfo->header->num_segments; ++i)
    {
    if( cinfo->header->offset[i-1] > cinfo->header->offset[i] )
      {
      // Need to throw something here
      abort();
      }
    }
  for(i=cinfo->header->num_segments; i < 16; ++i)
    {
    if( cinfo->header->offset[i] != 0 )
      {
      // Need to throw something here
      abort();
      }
    }
  cinfo->stream = infile;
}

/* 
 * G.3.2 The RLE decoder
 * Pseudo code for the RLE decoder is shown below:
 * Loop until the number of output bytes equals the uncompressed segment size
 * Read the next source byte into n
 * If n> =0 and n <= 127 then
 * output the next n+1 bytes literally
 * Elseif n <= - 1 and n >= -127 then
 * output the next byte -n+1 times
 * Elseif n = - 128 then
 * output nothing
 * Endif
 * Endloop
 */

int rle_start_decompress(rle_decompress_struct *cinfo)
{
  fseek(cinfo->stream, cinfo->header->offset[0], SEEK_SET );
  return 1;
}

void rle_create_decompress(rle_decompress_struct *cinfo)
{
  int i;
  cinfo->output_scanline = 0;
  cinfo->output_height = 0;
  cinfo->current_segment = 0;
  cinfo->header = (rle_header*)malloc(sizeof(rle_header));
  cinfo->header->num_segments = 0;
  for(i = 0; i < 16; ++i)
    cinfo->header->offset[i] = 0;
}

int rle_read_scanlines(rle_decompress_struct *cinfo, char *buffer, int f)
{
  signed char byte;
  return 1;
}

int rle_finish_decompress(rle_decompress_struct *cinfo)
{
  return 1;
}

void rle_destroy_decompress(rle_decompress_struct *cinfo)
{
  cinfo->output_scanline = 0; // why not
  cinfo->output_height = 0; // why not
  free(cinfo->header);
}

#endif /* __rlelib_h */

