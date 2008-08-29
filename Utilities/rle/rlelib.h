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
  rle_header *header;
} rle_decompress_struct;

void rle_stdio_src(rle_decompress_struct *cinfo, FILE *infile)
{
  int i;
  //is.read((char*)(&Header), sizeof(uint32_t)*16);
  size_t len = fread(cinfo->header, sizeof(uint32_t), 16, infile);
  if( cinfo->header->num_segments > 16 )
    {
    // Need to throw something here
    }
  if( cinfo->header->offset[0] != 64 )
    {
    // Need to throw something here
    }
  for(i=1; i < 16; ++i)
    {
    if( cinfo->header->offset[i-1] > cinfo->header->offset[i] )
      {
      // Need to throw something here
      }
    }
}

int rle_start_decompress(rle_decompress_struct *cinfo)
{
  return 1;
}

void rle_create_decompress(rle_decompress_struct *cinfo)
{
  int i;
  cinfo->output_scanline = 0;
  cinfo->output_height = 0;
  cinfo->header = (rle_header*)malloc(sizeof(rle_header));
  cinfo->header->num_segments = 0;
  for(i = 0; i < 16; ++i)
    cinfo->header->offset[i] = 0;
}

int rle_read_scanlines(rle_decompress_struct *cinfo, char *buffer, int f)
{
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

