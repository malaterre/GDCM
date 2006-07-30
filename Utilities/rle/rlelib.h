#ifndef __rlelib_h
#define __rlelib_h

#define RLE_LIB_VERSION 0.0

struct rle_error_mgr
{
  void (*error_exit) (rle_common_ptr cinfo);
  void (*output_message) (rle_common_ptr cinfo);

};

struct rle_common_struct
{
  struct rle_error_mgr * err;
};

typedef struct rle_common_struct * rle_common_ptr;
typedef struct rle_compress_struct * rle_compress_ptr;
typedef struct rle_decompress_struct * rle_decompress_ptr;

struct rle_decompress_struct
{
  struct rle_error_mgr * err;
};

/* Destruction of JPEG compression objects */
void rle_destroy_compress (rle_compress_ptr cinfo);
void rle_destroy_decompress (rle_decompress_ptr cinfo);

#endif /* __rlelib_h */
