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

        // compress the data; we don't need to check for errors
        // here because there is no possibility that they can
        // happen here; it is explained in the libbzip2 docs.
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
    gzoutbuf(std::streambuf* _dest, unsigned int block_size_100K = 9,
      unsigned int verbosity = 0, unsigned int work_factor = 0,
      zalloc_ptr zalloc = NULL, zfree_ptr zfree = NULL,
      void* opaque = NULL, size_t stream_buffer_size = 2048,
      size_t out_buffer_size = 2048)
      : dest(_dest)
      {
      // check the parameters
      if (block_size_100K > 9)
        throw std::range_error("Block size out of range.");
      if (verbosity > 4)
        throw std::range_error("Verbosity level out of range.");
      if (work_factor > 250)
        throw std::range_error("Work factor out of range.");
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

      // create a bz2 compressor stream
      int ret = deflateInit(&cstream,Z_BEST_SPEED);
      // BZ_PARAM_ERROR won't happen here because we checked before
      switch (ret) {
      case Z_OK:
        break;
        //case BZ_CONFIG_ERROR:
        //  throw std::runtime_error("libbz2 was not compiled correctly.");
      case Z_MEM_ERROR:
        throw std::bad_alloc();
      default:
        throw std::runtime_error("Unknown error creating bz2 compressor "
          "stream buffer.");
      }
      }

    /// Flush the buffer and destroy the object.  Notice that there is
    /// no way for the destructor to report a failure to write to the
    /// underlying stream buffer.  Thus you might want to check the
    /// underlying stream buffer for errors \em after the bz2outbuf
    /// object has been destroyed.
    virtual ~gzoutbuf() {
      // finish compression
      process_block();
      finish();

      // delete the compressor stream
      deflateEnd(&cstream);
    }
  };

  /// \brief An output stream compressing all data with the bz2
  /// algorithm.
  ///
  /// As the actual compression is achieved in the underlying
  /// ::bz2outbuf stream buffer, you should read its documentation
  /// before using this class.
  ///
  /// A bz2ostream object writes the output data to a stream buffer you
  /// specify in the constructor; it can thus be used to write to any
  /// stream buffer you want.
  class gzostream : public std::ostream {
  protected:
    gzoutbuf buf;
  public:
    /// \brief Creates a new bz2ostream object.  See
    /// bz2outbuf::bz2outbuf for an explanation of the parameters.
    gzostream(std::streambuf* dest, unsigned int block_size_100K = 9,
      unsigned int verbosity = 0, unsigned int work_factor = 0,
      zalloc_ptr zalloc = NULL, zfree_ptr zfree = NULL,
      void* opaque = NULL, size_t buffer_size = 1024,
      size_t out_buffer_size = 1024)
      : std::ostream(&buf),
      buf(dest, block_size_100K, verbosity, work_factor, zalloc, zfree,
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
  /// \brief A stream buffer reading from another stream buffer and
  /// decompressing the read data using the bz2 algorithm.
  ///
  /// You specify the underlying "source" stream buffer in the
  /// constructor.
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

      // shovel data into the bzip stream until there is something
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
          //case BZ_DATA_ERROR_MAGIC:
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
    /// \brief Creates a new bz2inbuf object, using _source as
    /// underlying stream buffer.
    ///
    /// @param _source The stream buffer this object should read
    /// from.  Notice that this stream buffer must be in binary and
    /// not in text mode, because transformation of newlines and/or
    /// other characters would invariably lead to data corruption.
    ///
    /// @param verbosity The verbosity of the libbzip2.  Ranges from 0
    /// (quiet) to 4 (very verbose).  Messages are printed to stderr.
    ///
    /// @param small_but_slow If false, use default algorithm.  If
    /// true, use a less memory intensive but slower algorithm.  Not
    /// recommended.
    ///
    /// @param bzalloc A pointer to a custom memory allocation
    /// function.  If NULL, malloc() is used. See also ::bzalloc_ptr.
    ///
    /// @param bzfree A pointer to a custom memory deallocation
    /// function.  If NULL, free() is used.  See also ::bzfree_ptr.
    ///
    /// @param opaque A pointer to be passed to the custom memory
    /// allocation and deallocation functions.  See also ::bzalloc_ptr
    /// and ::bzfree_ptr.
    ///
    /// @param stream_buffer_size The size of the buffer of this
    /// stream buffer.  Leave it alone if you don't know what you're
    /// doing.  Must be greater than zero.  Bigger buffers are not
    /// always faster.
    ///
    /// @param in_buffer_size The size of the input buffer.
    /// Definitely leave it alone if you don't know what you're
    /// doing.  Must be greater than zero, and \e should not be
    /// greater than stream_buffer_size.
    ///
    /// @param max_putback_size The maximum size of the stream's
    /// putback area.  Ranges from 0 to stream_buffer_size - 1. Leave
    /// it alone if you don't know what you're doing.
    ///
    /// Currently, this constructor throws any of the following
    /// exceptions:
    ///
    /// - std::range_error if one of the arguments is out of range.
    /// - std::bad_alloc if it runs out of memory.
    /// - std::runtime_error for any other error.
    ///
    /// All thrown exceptions except std::bad_alloc include a
    /// description of the encountered problem which you can access
    /// using the what() member function.
    ///
    /// For future compatibility, expect this constructor to throw any
    /// std::exception derived exception.
    gzinbuf(std::streambuf* _source, unsigned int verbosity = 0,
      bool small_but_slow = false, zalloc_ptr zalloc = NULL,
      zfree_ptr zfree = NULL, void* opaque = NULL,
      size_t stream_buffer_size = 1024, size_t in_buffer_size = 1024,
      size_t max_putback_size = 64)
      : source(_source)
      {
      // check the parameters
      if (verbosity > 4)
        throw std::range_error("Verbosity level out of range.");
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

      // init a decompressor stream
      //int ret = inflateInit(&dstream);
      int ret = inflateInit2(&dstream, -MAX_WBITS);
      // we don't need to handle BZ_PARAM_ERROR because we've
      // already checked the parameters
      switch (ret) {
      case Z_OK:
        break;
        //case BZ_CONFIG_ERROR:
        //  throw std::runtime_error("libbz2 was not compiled correctly.");
      case Z_MEM_ERROR:
        throw std::bad_alloc();
      default:
        throw std::runtime_error("Unknow error creating bz2 decompressor "
          "stream buffer.");
      }
      }

    /// \brief Destroys the bz2inbuf object.
    ~gzinbuf() {
      // uninit the bz2 stream
      inflateEnd(&dstream);
    }
  };

  /// \brief An input stream decompressing data compressed with the bz2
  /// algorithm.
  ///
  /// The actual decompression is achieved in the underlying ::bz2inbuf
  /// stream buffer; you should read its documentation before using this
  /// class.
  ///
  /// The data is read from a supplied stream buffer.
  class gzistream : public std::istream {
  protected:
    gzinbuf buf;
  public:
    /// \brief Creates a new bz2istream, using source as the stream
    /// buffer to read data from.
    ///
    /// See bz2inbuf::bz2inbuf for an explanation of the parameters.
    gzistream(std::streambuf* source, unsigned int verbosity = 0,
      bool small_but_slow = false, zalloc_ptr zalloc = NULL,
      zfree_ptr zfree = NULL, void* opaque = NULL,
      size_t buffer_size = 1024, size_t in_buffer_size = 1024,
      size_t max_putback_size = 64)
      : std::istream(&buf),
      buf(source, verbosity, small_but_slow, zalloc, zfree, opaque,
        buffer_size, in_buffer_size, max_putback_size)
    {}
  };
} // end namespace gdcm
#endif  // __gdcmDeflateStream_h

