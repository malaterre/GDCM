//#include "gdcmOStream.h"
#include "gdcmJPEGCodec.h"

#include "gdcmJPEGDataSrc.cxx"

#include <setjmp.h>

namespace gdcm
{
struct my_error_mgr {
   struct jpeg_error_mgr pub; /* "public" fields */
   jmp_buf setjmp_buffer;     /* for return to caller */
};
typedef struct my_error_mgr* my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */
extern "C" {
METHODDEF(void) my_error_exit (j_common_ptr cinfo) {
   /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
   my_error_ptr myerr = (my_error_ptr) cinfo->err;

   /* Always display the message. */
   /* We could postpone this until after returning, if we chose. */
   (*cinfo->err->output_message) (cinfo);

   /* Return control to the setjmp point */
   longjmp(myerr->setjmp_buffer, 1);
}
}

bool JPEGCodec::DECODE_BITSAMPLE(IStream &is, OStream &os)
{
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  jpeg_decompress_struct &cinfo = Internals->cinfo;

  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  my_error_mgr &jerr = Internals->jerr;
  /* More stuff */
  //FILE * infile;		/* source file */
  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  //if( !is /*|| !is.good()*/ )
  //  {
  //  abort();
  //  return false;
  //  }

  // Step 1: allocate and initialize JPEG decompression object
  //
  // We set up the normal JPEG error routines, then override error_exit.
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  // Establish the setjmp return context for my_error_exit to use.
  if (setjmp(jerr.setjmp_buffer))
    {
    // If we get here, the JPEG code has signaled an error.
    // We need to clean up the JPEG object, close the input file, and return.
    jpeg_destroy_decompress(&cinfo);
    //fclose(infile);
    return false;
  }

  if( Internals->StateSuspension == 0 )
    {
    // Now we can initialize the JPEG decompression object.
    jpeg_create_decompress(&cinfo);

    // Step 2: specify data source (eg, a file)
    jpeg_stdio_src(&cinfo, is, true);
    }
  else
    {
    jpeg_stdio_src(&cinfo, is, false);
    }

  /* Step 3: read file parameters with jpeg_read_header() */

  if ( Internals->StateSuspension < 2 )
    {
    if( jpeg_read_header(&cinfo, TRUE) == JPEG_SUSPENDED )
      {
      Internals->StateSuspension = 2;
      }

    /* Step 4: set parameters for decompression */
    /* prevent the library from performing any color space conversion */
    if ( cinfo.process == JPROC_LOSSLESS )
      {
      cinfo.jpeg_color_space = JCS_UNKNOWN;
      cinfo.out_color_space = JCS_UNKNOWN;
      }
    }

  /* Step 5: Start decompressor */

  if (Internals->StateSuspension < 3 )
    {
    if ( jpeg_start_decompress(&cinfo) == FALSE )
      {
      /* Suspension: jpeg_start_decompress */
      Internals->StateSuspension = 3;
      }

    /* We may need to do some setup of our own at this point before reading
     * the data.  After jpeg_start_decompress() we have the correct scaled
     * output image dimensions available, as well as the output colormap
     * if we asked for color quantization.
     * In this example, we need to make an output work buffer of the right size.
     */ 
    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    row_stride *= sizeof(JSAMPLE);
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
      ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    /* Save the buffer in case of suspension to be able to reuse it later: */
    Internals->SampBuffer = buffer;
    }
  else
    {
    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    row_stride *= sizeof(JSAMPLE);

    /* Suspension: re-use the buffer: */
    buffer = (JSAMPARRAY)Internals->SampBuffer;
    }

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    if( jpeg_read_scanlines(&cinfo, buffer, 1) == 0 )
      {
      /* Suspension in jpeg_read_scanlines */
      Internals->StateSuspension = 3;
      return true;
      }
    //memcpy(buffer[0], row_stride);
    os.Write((char*)buffer[0], row_stride);
  }

  /* Step 7: Finish decompression */

  if( jpeg_finish_decompress(&cinfo) == FALSE )
    {
    /* Suspension: jpeg_finish_decompress */
    Internals->StateSuspension = 4;
    }

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  /* After finish_decompress, we can close the input file.
   * Here we postpone it until after no more JPEG errors are possible,
   * so as to simplify the setjmp error logic above.  (Actually, I don't
   * think that jpeg_destroy can do an error exit, but why assume anything...)
   */
  //fclose(infile);

  /* At this point you may want to check to see whether any corrupt-data
   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
   */

  /* And we're done! */
  return true;
}

} // end namespace gdcm

#undef DECODE_BITSAMPLE
