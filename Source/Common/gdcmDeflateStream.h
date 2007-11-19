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

#ifndef __gdcmDeflateStream_h
#define __gdcmDeflateStream_h

#include <algorithm>
#include <cstdlib>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <streambuf>
#include <vector>

#include <zlib.h>
#include <iostream>

/*
 * Implementation found at:
 * http://forum.idg.pl/index.php?showtopic=72330
 * Apparently comments seems to be coming from:
 * http://www.isotton.com/devel/libs/bz2stream/
 */

extern "C" {
   typedef void* (*zalloc_ptr)(void* opaque, uint n,uint m);
   typedef void (*zfree_ptr)(void* opaque, void* p);
}

namespace gdcm
{
  class gzoutbuf : public std::streambuf {
  protected:
    std::streambuf* dest;
    std::vector<char> buffer;
    std::vector<char> out_buffer;
    z_stream cstream;

    bool process_block() {
      int num = pptr() - pbase();
      cstream.next_in = (Bytef*)pbase();
      cstream.avail_in = num;

      while (cstream.avail_in) {
        // set the pointers to the output buffer
        cstream.next_out = (Bytef*)&out_buffer[0];
        cstream.avail_out = out_buffer.size();

        // compress the data;
        // TODO: check Z_NO_FLUSH is the right thing to do...
        deflate(&cstream, Z_NO_FLUSH);

        // write the data to the underlying stream buffer
        int out_size = out_buffer.size() - cstream.avail_out;
        if (dest->sputn(&out_buffer[0], out_size) != out_size)
          return false;
      }

      pbump(-num);
      return true;
    }

    bool flush() {
      bool flushed = false;
      cstream.next_in = NULL;
      cstream.avail_in = 0;

      do {
        // set the pointers to the output buffer
        cstream.next_out = (Bytef*)&out_buffer[0];
        cstream.avail_out = out_buffer.size();

        // here no errors should happen, too
        flushed = deflate(&cstream, Z_FULL_FLUSH) == Z_OK;

        // write the data to the underlying stream buffer
        int out_size = out_buffer.size() - cstream.avail_out;
        if (dest->sputn(&out_buffer[0], out_size) != out_size)
          return false;
      } while (!flushed);

      return true;
    }

    bool finish() {
      bool finished = false;
      cstream.next_in = NULL;
      cstream.avail_in = 0;

      do {
        // set the pointers to the output buffer
        cstream.next_out = (Bytef*)&out_buffer[0];
        cstream.avail_out = out_buffer.size();

        // here no errors should happen, too
        finished = deflate(&cstream, Z_FINISH) == Z_STREAM_END;

        // write the data to the underlying stream buffer
        int out_size = out_buffer.size() - cstream.avail_out;
        if (dest->sputn(&out_buffer[0], out_size) != out_size)
          return false;
      } while (!finished);

      return true;
    }

    virtual int_type overflow(int_type c) {
      if (!traits_type::eq_int_type(c, traits_type::eof())) {
        // put this character in the last position
        // (this function is called when pptr() == eptr() but we
        // have reserved one byte more in the constructor, thus
        // *epptr() and now *pptr() point to valid positions)
        *pptr() = c;
        pbump(1);
      }

      return process_block() ? traits_type::not_eof(c) : traits_type::eof();
    }

    virtual int sync() {
      return process_block() && flush() ? 0 : -1;
    }

    virtual std::streamsize xsputn(const char* p, std::streamsize num) {
      // the number of chars copied
      std::streamsize done = 0;

      // loop until no data is left
      while (done < num) {
        // get the number of chars to write in this iteration
        // (we've got one more char than epptr thinks)
        int block_size = std::min(num - done, epptr() - pptr() + 1);

        // write them
        // memcpy vs std::copy ??
        std::memcpy(pptr(), p + done, block_size);

        // update the write pointer
        pbump(block_size);

        // process_block if necessary
        if (pptr() >= epptr()) {
          if (!process_block())
            break;
        }

        // update the yet-to-do count
        done += block_size;
      }

      return done;
    }
  public:
    gzoutbuf(std::streambuf* _dest, 
      zalloc_ptr zalloc = NULL, zfree_ptr zfree = NULL,
      void* opaque = NULL, size_t stream_buffer_size = 2048,
      size_t out_buffer_size = 2048)
      : dest(_dest)
      {
      // check the parameters
      if (stream_buffer_size < 1)
        throw std::range_error("Stream buffer size must be positive.");
      if (out_buffer_size < 1)
        throw std::range_error("Output buffer size must be positive.");

      // allocate the buffer (we don't do that in the initializer
      // because if one of the parameters is out of range it isn't
      // necessary to allocate at all)
      buffer.resize(stream_buffer_size);

      // allocate memory for the output buffer
      out_buffer.resize(out_buffer_size);

      // set the buffer pointers; use one character less for the
      // stream buffer than the really available one
      setp(&buffer[0], &*--buffer.end());

      // initialize the compressor stream
      memset(&cstream, 0, sizeof(cstream));
      cstream.zalloc = zalloc;
      cstream.zfree = zfree;
      cstream.opaque = opaque;

      // create a gzip compressor stream
      int ret = deflateInit(&cstream,Z_BEST_SPEED);
      switch (ret) {
      case Z_OK:
        break;
      case Z_MEM_ERROR:
        throw std::bad_alloc();
      default:
        throw std::runtime_error("Unknown error creating gzip compressor "
          "stream buffer.");
      }
      }

    virtual ~gzoutbuf() {
      // finish compression
      process_block();
      finish();

      // delete the compressor stream
      deflateEnd(&cstream);
    }
  };

  class gzostream : public std::ostream {
  protected:
    gzoutbuf buf;
  public:
    gzostream(std::streambuf* dest, 
      zalloc_ptr zalloc = NULL, zfree_ptr zfree = NULL,
      void* opaque = NULL, size_t buffer_size = 1024,
      size_t out_buffer_size = 1024)
      : std::ostream(&buf),
      buf(dest, zalloc, zfree,
        opaque, buffer_size, out_buffer_size)
    {}
  };

  void zerr(int ret)
    {
    fputs("zpipe: ", stderr);
    switch (ret) {
      case Z_ERRNO:
        if (ferror(stdin))
          fputs("error reading stdin\n", stderr);
        if (ferror(stdout))
          fputs("error writing stdout\n", stderr);
        break;
      case Z_STREAM_ERROR:
        fputs("invalid compression level\n", stderr);
        break;
      case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
      case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
      case Z_VERSION_ERROR:
        fputs("zlib version mismatch!\n", stderr);
      }
    }

  class gzinbuf : public std::streambuf {
  protected:
    std::streambuf* source;
    std::vector<char> buffer;
    char* putback_end;
    std::vector<char> in_buffer;
    char* in_begin;
    char* in_end;
    z_stream dstream;

    virtual int_type underflow() {
      // calculate the new size of the putback area
      int new_putback_num = std::min(gptr() - eback(),
        putback_end - &buffer[0]);

      // copy the new putback data into the putback area
      std::memcpy(putback_end - new_putback_num,
        gptr() - new_putback_num, new_putback_num);

      // shovel data into the gzip stream until there is something
      // in the output buffer
      do {
        // refill the input buffer if necessary
        if (in_begin == in_end) {
          std::streamsize read_num = source->sgetn(&in_buffer[0],
            in_buffer.size());
          if (read_num == 0) {
            // we can't read anymore
            return traits_type::eof();
          }
          in_begin = &in_buffer[0];
          in_end = in_begin + read_num;
        }

        // decompress the data
        dstream.next_in = (Byte*)in_begin;
        dstream.avail_in = in_end - in_begin;
        dstream.next_out = (Byte*)putback_end;
        dstream.avail_out = &*buffer.end() - putback_end;
        int ret = inflate(&dstream,Z_NO_FLUSH);
        switch (ret) {
        case Z_OK:
          break;
        case Z_STREAM_END:
          // Z_STREAM_END if the end of the compressed data has been reached
          // and all uncompressed output has been produced
          if (&*buffer.end() - putback_end == (int) dstream.avail_out)
            return traits_type::eof();
          break;
        case Z_DATA_ERROR:
          abort();
        case Z_MEM_ERROR:
          abort();
        default:
          abort();
          // TODO: handle these errors separately
          return traits_type::eof();
        }

        // update the input buffer pointers
        in_begin = in_end - dstream.avail_in;

      } while (dstream.avail_out + putback_end == &*buffer.end());

      // update the stream buffer pointers
      setg(putback_end - new_putback_num,
        putback_end,
        &*buffer.end() - dstream.avail_out);

      // return the next character
      return traits_type::to_int_type(*gptr());
    }

  public:
    gzinbuf(std::streambuf* _source, 
      zalloc_ptr zalloc = NULL,
      zfree_ptr zfree = NULL, void* opaque = NULL,
      size_t stream_buffer_size = 1024, size_t in_buffer_size = 1024,
      size_t max_putback_size = 64)
      : source(_source)
      {
      // check the parameters
      if (stream_buffer_size < 1)
        throw std::range_error("Stream buffer size must be positive.");
      if (in_buffer_size < 1)
        throw std::range_error("Input buffer size must be positive.");
      if (max_putback_size >= stream_buffer_size)
        throw std::range_error("The maximum size of the putback area must "
          "be less than the stream size.");

      // allocate the buffers
      buffer.resize(stream_buffer_size);
      in_buffer.resize(in_buffer_size);
      in_begin = in_end = &in_buffer[0];

      // set the get pointers (we force an underflow on the first
      // read)
      putback_end = &buffer[0] + max_putback_size;
      setg(putback_end, putback_end, putback_end);

      // set up a decompressor stream
      std::memset(&dstream, 0, sizeof(dstream));
      dstream.zalloc = zalloc;
      dstream.zfree = zfree;
      dstream.opaque = opaque;
      dstream.avail_in = 0;
      dstream.next_in = Z_NULL;

      // call inflateInit2 since we do not have a header in DICOM
      // well hopefully if private implementation do respect standard.
      // I think it should not be too hard to support
      // but right now I haven't seen any so let's keep it that way
      //
      //int ret = inflateInit(&dstream);
      int ret = inflateInit2(&dstream, -MAX_WBITS);
      switch (ret) 
        {
        case Z_OK:
          break;
        case Z_MEM_ERROR:
          throw std::bad_alloc();
        default:
          throw std::runtime_error("Unknow error");
        }
      }

    ~gzinbuf() {
      inflateEnd(&dstream);
    }
  };

  class gzistream : public std::istream {
  protected:
    gzinbuf buf;
  public:
    gzistream(std::streambuf* source,
      zalloc_ptr zalloc = NULL,
      zfree_ptr zfree = NULL, void* opaque = NULL,
      size_t buffer_size = 1024, size_t in_buffer_size = 1024,
      size_t max_putback_size = 64)
      : std::istream(&buf),
      buf(source, zalloc, zfree, opaque,
        buffer_size, in_buffer_size, max_putback_size)
    {}
  };

} // end namespace gdcm

#endif  // __gdcmDeflateStream_h

