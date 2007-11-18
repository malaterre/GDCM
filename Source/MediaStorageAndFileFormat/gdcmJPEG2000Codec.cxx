/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmJPEG2000Codec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmTrace.h"

#include "gdcm_openjpeg.h"

namespace gdcm
{

/**
sample error callback expecting a FILE* client object
*/
void error_callback(const char *msg, void *) {
  gdcmErrorMacro( "Error in gdcmopenjpeg" << msg );
}
/**
sample warning callback expecting a FILE* client object
*/
void warning_callback(const char *msg, void *) {
  gdcmWarningMacro( "Warning in gdcmopenjpeg" << msg );
}
/**
sample debug callback expecting no client object
*/
void info_callback(const char *msg, void *) {
  gdcmDebugMacro( "Info in gdcmopenjpeg" << msg );
}

#define J2K_CFMT 0
#define JP2_CFMT 1
#define JPT_CFMT 2
#define MJ2_CFMT 3
#define PXM_DFMT 0
#define PGX_DFMT 1
#define BMP_DFMT 2
#define YUV_DFMT 3

/*
 * Divide an integer by a power of 2 and round upwards.
 *
 * a divided by 2^b
 */
inline int int_ceildivpow2(int a, int b) {
  return (a + (1 << b) - 1) >> b;
}

class JPEG2000Internals
{
public:
};

JPEG2000Codec::JPEG2000Codec()
{
  Internals = new JPEG2000Internals;
}

JPEG2000Codec::~JPEG2000Codec()
{
  delete Internals;
}

bool JPEG2000Codec::CanDecode(TransferSyntax const &ts)
{
  return ts == TransferSyntax::JPEG2000Lossless 
	  || ts == TransferSyntax::JPEG2000;
}

bool JPEG2000Codec::Decode(std::istream &is, std::ostream &os)
{
  opj_dparameters_t parameters;  /* decompression parameters */
  opj_event_mgr_t event_mgr;    /* event manager */
  opj_image_t *image;
  opj_dinfo_t* dinfo;  /* handle to a decompressor */
  opj_cio_t *cio;
  // FIXME: Do some stupid work:
  is.seekg( 0, std::ios::end);
  std::streampos buf_size = is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(0, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  unsigned char *src = (unsigned char*)dummy_buffer;
  int file_length = buf_size;
  char *raw = NULL;

  /* configure the event callbacks (not required) */
  memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
  event_mgr.error_handler = error_callback;
  event_mgr.warning_handler = warning_callback;
  event_mgr.info_handler = info_callback;

  /* set decoding parameters to default values */
  opj_set_default_decoder_parameters(&parameters);
 
   // default blindly copied
   parameters.cp_layer=0;
   parameters.cp_reduce=0;
//   parameters.decod_format=-1;
//   parameters.cod_format=-1;

      /* JPEG-2000 codestream */
    parameters.decod_format = J2K_CFMT;
    assert(parameters.decod_format == J2K_CFMT);
  parameters.cod_format = PGX_DFMT;
  assert(parameters.cod_format == PGX_DFMT);

      /* get a decoder handle */
      dinfo = opj_create_decompress(CODEC_J2K);
      
      /* catch events using our callbacks and give a local context */
      opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, NULL);      

      /* setup the decoder decoding parameters using user parameters */
      opj_setup_decoder(dinfo, &parameters);

      /* open a byte stream */
      cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

      /* decode the stream and fill the image structure */
      image = opj_decode(dinfo, cio);
      if(!image) {
        opj_destroy_decompress(dinfo);
        opj_cio_close(cio);
        return 1;
      }
      
      /* close the byte stream */
      opj_cio_close(cio);

   //raw = (char*)src;
   // Copy buffer
      for (int compno = 0; compno < image->numcomps; compno++)
        {
        opj_image_comp_t *comp = &image->comps[compno];

        int w = image->comps[compno].w;
        int wr = int_ceildivpow2(image->comps[compno].w, image->comps[compno].factor);

        //int h = image.comps[compno].h;
        int hr = int_ceildivpow2(image->comps[compno].h, image->comps[compno].factor);

        if (comp->prec <= 8)
          {
          raw = new char[wr * hr];
          uint8_t *data8 = (uint8_t*)raw;
          for (int i = 0; i < wr * hr; i++) 
            {
            int v = image->comps[compno].data[i / wr * w + i % wr];
            *data8++ = (uint8_t)v;
            }
          os.write(raw, wr * hr * 1);
          }
        else if (comp->prec <= 16)
          {
          raw = new char[wr * hr * 2];
          uint16_t *data16 = (uint16_t*)raw;
          for (int i = 0; i < wr * hr; i++) 
            {
            int v = image->comps[compno].data[i / wr * w + i % wr];
            *data16++ = (uint16_t)v;
            }
          os.write(raw, wr * hr * 2);
          }
        else
          {
          raw = new char[wr * hr * 4];
          uint32_t *data32 = (uint32_t*)raw;
          for (int i = 0; i < wr * hr; i++) 
            {
            int v = image->comps[compno].data[i / wr * w + i % wr];
            *data32++ = (uint32_t)v;
            }
          os.write(raw, wr * hr * 4);
          }
        delete[] raw;
        //free(image.comps[compno].data);
        }
  /* free the memory containing the code-stream */
  delete[] src;  //FIXME

 

  /* free remaining structures */
  if(dinfo) {
    opj_destroy_decompress(dinfo);
  }

  /* free image data structure */
  opj_image_destroy(image);

  return true;
}

} // end namespace gdcm
