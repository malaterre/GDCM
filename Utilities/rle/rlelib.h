#ifndef __rlelib_h
#define __rlelib_h

#define RLE_LIB_VERSION 0.0

typedef struct
{
  unsigned long num_segments;
  unsigned long offset[15];
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

void rle_stdio_src(rle_decompressed_frame * frame, FILE *infile)
{
}

#endif /* __rlelib_h */
