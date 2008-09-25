/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * TODO: Merging (burnin) of overlay would be nice (merge 0x60xx overlay into PixelData)
 * TODO: --add-thumbnail / --remove-thumbnail
 * convert: -thumbnail geometry  create a thumbnail of the image
 * convert: -crop geometry       cut out a rectangular region of the image
 * -floodfill geometry color
 *                               floodfill the image with color
 * 1. Create a DICOM file from a 'raw' input:
 * 2. Create a blob (jpeg,pgm/pnm,j2k,rle) from input
 * - binary blob(s) (grayscale / RGB) input
 * - jpeg(s)
 * - j2k(s)
 *
 *   Mapping is:
 *
 *   DICOM RAW  <->  pnm/pgm
 *   DICOM jpg  <->  jpg
 *   DICOM ljpg <->  ljpg
 *   DICOM jpls <->  jpls
 *   DICOM j2k  <->  j2k
 *   DICOM rle  <->  Utah RLE ??
 *
 * ??:
 *   DICOM avi  <->  avi
 *   DICOM wav  <->  wav
 *   DICOM pdf  <->  pdf
 * Todo: check compat API with jhead 
 */
#include "gdcmFilename.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSystem.h"
#include "gdcmReader.h"
#include "gdcmImageWriter.h"
#include "gdcmImageReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmPNMCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmVersion.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

bool readsize(const char *str, unsigned int * size)
{
  int n = sscanf( str, "%i,%i", size, size+1);
  return n == 2;
}

bool readgeometry(const char *geometry, unsigned int * region)
{
  int n = sscanf( geometry, "%i,%i,%i,%i,%i,%i", region, region+1, region+2, region+3, region+4, region+5);
  return true;
}

template <typename T>
void FillRegionWithColor(char *cp, const unsigned int *dims, const unsigned int * region, unsigned int color, unsigned int nsamples)
{
    T * p = (T*)cp;
    unsigned int xmin = region[0];
    unsigned int xmax = region[1];
    unsigned int ymin = region[2];
    unsigned int ymax = region[3];
    unsigned int zmin = region[4];
    unsigned int zmax = region[5];

    for( unsigned int x = xmin; x <= xmax; ++x)
      {
      for( unsigned int y = ymin; y <= ymax; ++y)
        {
        for( unsigned int z = zmin; z <= zmax; ++z)
          {
          for( unsigned int sample = 0; sample < nsamples; ++sample)
            {
            p[x*nsamples+y*dims[0]*nsamples+z*dims[0]*dims[1]*nsamples+sample] = color;
            }
          }
        }
      }
}

void PrintVersion()
{
  std::cout << "gdcmimg: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmimg [OPTION]... FILE..." << std::endl;
  std::cout << "Manipulate DICOM file" << std::endl;
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     Input filename" << std::endl;
  std::cout << "  -o --output    Output filename" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -d --depth      Depth." << std::endl;
  std::cout << "  -s --size %d,%d Size." << std::endl;
  std::cout << "  -R --region     Region." << std::endl;
  std::cout << "  -F --fill       Fill." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
}

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  gdcm::Filename filename;
  gdcm::Filename outfilename;
  unsigned int region[6] = {}; // Rows & Columns are VR=US anyway...
  unsigned int color = 0;
  bool b;
  int bregion = 0;
  int fill = 0;
  unsigned int size[2] = {};

  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;

  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        // provide convert-like command line args:
        {"depth", 1, 0, 0},
        {"size", 1, 0, 0},
        {"region", 1, &bregion, 1},
        {"fill", 1, &fill, 1},

// General options !
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0}
    };

    // i -> input file
    // I -> input directory
    // o -> output file
    // O -> output directory
    c = getopt_long (argc, argv, "i:o:I:O:d:s:R:F:VWDEhv",
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
        {
        const char *s = long_options[option_index].name;
        printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.IsEmpty() );
            filename = optarg;
            }
          else if( option_index == 3 ) /* size */
            {
            assert( strcmp(s, "size") == 0 );
            readsize(optarg, size);
            }
          else if( option_index == 4 ) /* region */
            {
            assert( strcmp(s, "region") == 0 );
            readgeometry(optarg, region);
            }
          else if( option_index == 5 ) /* fill */
            {
            assert( strcmp(s, "fill") == 0 );
            color = atoi(optarg);
            }
          printf (" with arg %s", optarg);
          }
        printf ("\n");
        }
      break;

    case 'i':
      printf ("option i with value '%s'\n", optarg);
      assert( filename.IsEmpty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      assert( outfilename.IsEmpty() );
      outfilename = optarg;
      break;

    case 'd': // depth
      printf ("option d with value '%s'\n", optarg);
      break;

    case 's': // size
      printf ("option s with value '%s'\n", optarg);
      readsize(optarg, size);
      break;

    case 'R': // region
      printf ("option R with value '%s'\n", optarg);
      //outfilename = optarg;
      readgeometry(optarg, region);
      break;

    case 'F': // fill
      printf ("option F with value '%s'\n", optarg);
      color = atoi( optarg );
      fill = 1;
      break;

    case 'V':
      verbose = 1;
      break;

    case 'W':
      warning = 1;
      break;

    case 'D':
      debug = 1;
      break;

    case 'E':
      error = 1;
      break;

    case 'h':
      help = 1;
      break;

    case 'v':
      version = 1;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  // For now only support one input / one output
  if (optind < argc)
    {
/*
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      {
      printf ("%s ", argv[optind++]);
      }
    printf ("\n");
*/
    PrintHelp();
    return 1;
    }

  if( version )
    {
    //std::cout << "version" << std::endl;
    PrintVersion();
    return 0;
    }

  if( help )
    {
    //std::cout << "help" << std::endl;
    PrintHelp();
    return 0;
    }

  if( filename.IsEmpty() )
    {
    //std::cerr << "Need input file (-i)\n";
    PrintHelp();
    return 1;
    }
  if( outfilename.IsEmpty() )
    {
    //std::cerr << "Need output file (-o)\n";
    PrintHelp();
    return 1;
    }

  // Debug is a little too verbose
  gdcm::Trace::SetDebug( debug );
  gdcm::Trace::SetWarning( warning );
  gdcm::Trace::SetError( error );
  // when verbose is true, make sure warning+error are turned on:
  if( verbose )
    {
    gdcm::Trace::SetWarning( verbose );
    gdcm::Trace::SetError( verbose);
    }
 
  const char *inputextension = filename.GetExtension();
  const char *outputextension = outfilename.GetExtension();
  //if( !inputextension || !outputextension ) return 1;
  if( inputextension )
    {
    if(  gdcm::System::StrCaseCmp(inputextension,".raw") == 0 )
      {
      if( !size[0] || !size[1] )
        {
        std::cerr << "need to specify size of image stored in RAW file" << std::endl;
        return 1;
        }
      size_t len = gdcm::System::FileSize(filename);
      std::ifstream is(filename);

      char * buf = new char[len];
      is.read(buf, len);

      gdcm::ImageWriter writer;
      gdcm::Image &image = writer.GetImage();
      image.SetNumberOfDimensions( 2 );
      unsigned int dims[3] = {};
      dims[0] = size[0];
      dims[1] = size[1];
      image.SetDimensions( size );
      gdcm::PixelFormat pf = gdcm::PixelFormat::UINT16;
      image.SetPixelFormat( pf );
      gdcm::PhotometricInterpretation pi = gdcm::PhotometricInterpretation::MONOCHROME2;
      image.SetPhotometricInterpretation( pi );
      //image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      image.SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRBigEndianPrivateGE ); // PGM are big endian

      gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
      pixeldata.SetByteValue( buf, len );
      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      if( !writer.Write() )
        {
        return 1;
        }
      delete[] buf;

      return 0;
      }

    if(  gdcm::System::StrCaseCmp(inputextension,".rle") == 0 )
      {
      if( !size[0] || !size[1] )
        {
        std::cerr << "need to specify size of image stored in RLE file" << std::endl;
        return 1;
        }
      size_t len = gdcm::System::FileSize(filename);
      std::ifstream is(filename);

      char * buf = new char[len];
      is.read(buf, len);

      gdcm::ImageWriter writer;
      gdcm::Image &image = writer.GetImage();
      image.SetNumberOfDimensions( 2 );
      unsigned int dims[3] = {};
      dims[0] = size[0];
      dims[1] = size[1];
      image.SetDimensions( size );
      gdcm::PixelFormat pf = gdcm::PixelFormat::UINT16;
      image.SetPixelFormat( pf );
      gdcm::PhotometricInterpretation pi = gdcm::PhotometricInterpretation::MONOCHROME2;
      image.SetPhotometricInterpretation( pi );
      image.SetTransferSyntax( gdcm::TransferSyntax::RLELossless );

      gdcm::DataElement pixeldata;

      gdcm::SmartPointer<gdcm::SequenceOfFragments> sq = new gdcm::SequenceOfFragments;

      gdcm::Fragment frag;
      frag.SetByteValue( buf, len );
      delete[] buf;
      sq->AddFragment( frag );
      pixeldata.SetValue( *sq );

      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      if( !writer.Write() )
        {
        return 1;
        }

      return 0;
      }

    if(  gdcm::System::StrCaseCmp(inputextension,".pgm") == 0 
      || gdcm::System::StrCaseCmp(inputextension,".pnm") == 0 
      || gdcm::System::StrCaseCmp(inputextension,".ppm") == 0 )
      {
      size_t len = gdcm::System::FileSize(filename);
      std::ifstream is(filename);
      std::string type, str;
      std::getline(is,type);
      gdcm::PhotometricInterpretation pi;
      if( type == "P5" )
        pi = gdcm::PhotometricInterpretation::MONOCHROME2;
      else if( type == "P6" )
        pi = gdcm::PhotometricInterpretation::RGB;
      else 
        {
        std::cerr << "Unhandled PGM type: " << type << std::endl;
        return 1;
        }

      // skip comments:
      while( is.peek() == '#' )
        {
        std::getline(is, str);
        //std::cout << str << std::endl;
        }
      unsigned int dims[3] = {};
      is >> dims[0]; is >> dims[1];
      unsigned int maxval;
      is >> maxval;
      // some kind of empty line...
      while( is.peek() == '\n' )
        {
        is.get();
        }
      std::streampos pos = is.tellg();
      size_t m = (len - pos ) / ( dims[0]*dims[1] );
      if( m * dims[0] * dims[1] != len - pos )
        {
        std::cerr << "Problem computing length" << std::endl;
        return 1;
        }
      gdcm::PixelFormat pf;
      switch(maxval)
        {
      case 255:
        pf = gdcm::PixelFormat::UINT8;
        break;
      case 65535:
        pf = gdcm::PixelFormat::UINT16;
        break;
      default:
        std::cerr << "Unhandled max val: " << maxval << std::endl;
        return 1;
        }
      if( pi == gdcm::PhotometricInterpretation::RGB )
        {
        pf.SetSamplesPerPixel( 3 );
        }
      //if ( maxval * 8 != bpp ) return 1;

      gdcm::ImageWriter writer;
      gdcm::Image &image = writer.GetImage();
      image.SetNumberOfDimensions( 2 );
      image.SetDimensions( dims );
      image.SetPixelFormat( pf );
      image.SetPhotometricInterpretation( pi );
      //image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRBigEndian ); // PGM are big endian
      //image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian ); // PGM are big endian
      image.SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRBigEndianPrivateGE ); // PGM are big endian

      size_t pdlen = image.GetBufferLength();
      char * buf = new char[pdlen];
      // is should be at right offset, just read!
      is.read(buf, len);
      if( !is.eof() ) return 1;

      gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
      pixeldata.SetByteValue( buf, pdlen );
      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      if( !writer.Write() )
        {
        return 1;
        }
      delete[] buf;

      return 0;
      }

    if(  gdcm::System::StrCaseCmp(inputextension,".jp2") == 0 
      || gdcm::System::StrCaseCmp(inputextension,".j2k") == 0
      || gdcm::System::StrCaseCmp(inputextension,".jpc") == 0 )
      {
      /*
       * FIXME: Same problem as in classic JPEG: JP2 is NOT a J2K byte stream
       * need to chop off all extra header information...
       */
      gdcm::JPEG2000Codec jpeg;

      std::ifstream is(filename);
      gdcm::PixelFormat pf ( gdcm::PixelFormat::UINT8 ); // usual guess...
      jpeg.SetPixelFormat( pf );
      gdcm::TransferSyntax ts;
      bool b = jpeg.GetHeaderInfo( is, ts );
      if( !b )
        {
        return 1;
        }

      gdcm::ImageWriter writer;
      gdcm::Image &image = writer.GetImage();
      image.SetNumberOfDimensions( 2 );
      image.SetDimensions( jpeg.GetDimensions() );
      image.SetPixelFormat( jpeg.GetPixelFormat() );
      image.SetPhotometricInterpretation( jpeg.GetPhotometricInterpretation() );
      image.SetTransferSyntax( ts );

      size_t len = gdcm::System::FileSize(filename);

      char * buf = new char[len];
      is.seekg(0, std::ios::beg );// rewind !
      is.read(buf, len);
      gdcm::DataElement pixeldata;

      gdcm::SmartPointer<gdcm::SequenceOfFragments> sq = new gdcm::SequenceOfFragments;

      gdcm::Fragment frag;
      frag.SetByteValue( buf, len );
      delete[] buf;
      sq->AddFragment( frag );
      pixeldata.SetValue( *sq );

      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      if( !writer.Write() )
        {
        return 1;
        }

      return 0;

      }

    if(  gdcm::System::StrCaseCmp(inputextension,".jpg") == 0 
      || gdcm::System::StrCaseCmp(inputextension,".jpeg") == 0
      || gdcm::System::StrCaseCmp(inputextension,".ljpg") == 0
      || gdcm::System::StrCaseCmp(inputextension,".ljpeg") == 0 )
      {
      /*
       * FIXME: when JPEG contains JFIF marker, we should only read them
       * during header parsing but discard them when copying the JPG byte stream into 
       * the encapsulated Pixel Data Element...
       */
      gdcm::JPEGCodec jpeg;
      std::ifstream is(filename);
      gdcm::PixelFormat pf ( gdcm::PixelFormat::UINT8 ); // usual guess...
      jpeg.SetPixelFormat( pf );
      gdcm::TransferSyntax ts;
      bool b = jpeg.GetHeaderInfo( is, ts );
      if( !b )
        {
        return 1;
        }

      gdcm::ImageWriter writer;
      gdcm::Image &image = writer.GetImage();
      image.SetNumberOfDimensions( 2 );
      image.SetDimensions( jpeg.GetDimensions() );
      image.SetPixelFormat( jpeg.GetPixelFormat() );
      image.SetPhotometricInterpretation( jpeg.GetPhotometricInterpretation() );
      image.SetTransferSyntax( ts );

      size_t len = gdcm::System::FileSize(filename);

      char * buf = new char[len];
      is.seekg(0, std::ios::beg );// rewind !
      is.read(buf, len);
      gdcm::DataElement pixeldata;

      gdcm::SmartPointer<gdcm::SequenceOfFragments> sq = new gdcm::SequenceOfFragments;

      gdcm::Fragment frag;
      frag.SetByteValue( buf, len );
      delete[] buf;
      sq->AddFragment( frag );
      pixeldata.SetValue( *sq );

      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      if( !writer.Write() )
        {
        return 1;
        }

      return 0;
      }
    }
// else safely assume that if no inputextension matched then it is a DICOM file

  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  const gdcm::Image &imageori = reader.GetImage();
  const gdcm::File &file = reader.GetFile();

  if ( outputextension )
    {
    if(  gdcm::System::StrCaseCmp(outputextension,".pgm") == 0 
      || gdcm::System::StrCaseCmp(outputextension,".pnm") == 0 
      || gdcm::System::StrCaseCmp(outputextension,".ppm") == 0 )
      {
      gdcm::PNMCodec pnm;
      pnm.SetDimensions( imageori.GetDimensions() );
      pnm.SetPixelFormat( imageori.GetPixelFormat() );
      const gdcm::DataElement& in = imageori.GetDataElement();
      bool b = pnm.Write( outfilename, in );
      if( !b )
        {
        std::cerr << "Problem writing PNM file" << std::endl;
        return 1;
        }

      return 0;
      }
    }

// else safely assume that if no outputextension matched then it is a DICOM file

  gdcm::ImageWriter writer;
  writer.SetFile( file );
  writer.SetImage( imageori );
  writer.SetFileName( outfilename );

  gdcm::DataSet &ds = writer.GetFile().GetDataSet();
  if( fill )
    {
    const gdcm::PixelFormat &pixeltype = imageori.GetPixelFormat();
    assert( imageori.GetNumberOfDimensions() == 2 || imageori.GetNumberOfDimensions() == 3 );
    unsigned long len = imageori.GetBufferLength();
    gdcm::Image image;
    image.SetNumberOfDimensions( 2 ); // good default
    const unsigned int *dims = imageori.GetDimensions();
    if ( region[0] > region[1] 
      || region[2] > region[3]
      || region[4] > region[5]
      || region[1] > dims[0]
      || region[3] > dims[1]
      || (imageori.GetNumberOfDimensions() > 2 && region[5] > dims[2]) )
      {
      if( imageori.GetNumberOfDimensions() == 2 )
        {
        std::cerr << "bogus region. Should be at most: (" << dims[0] << "," << dims[1] << "," 
          /*<< dims[2]*/ << ")" << std::endl;
        }
      else
        {
        std::cerr << "bogus region. Should be at most: (" << dims[0] << "," << dims[1] << "," 
          << dims[2] << ")" << std::endl;
        }
      return 1;
      }
    image.SetDimension(0, dims[0] );
    image.SetDimension(1, dims[1] );
    if( imageori.GetNumberOfDimensions() == 3 )
      {
      image.SetNumberOfDimensions( 3 );
      image.SetDimension(2, dims[2] );
      }
    image.SetPhotometricInterpretation( imageori.GetPhotometricInterpretation() );
    image.SetPixelFormat( imageori.GetPixelFormat() );
    gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
    gdcm::ByteValue *bv = new gdcm::ByteValue();
    bv->SetLength( len );
    //memcpy( bv->GetPointer(), imageori
    imageori.GetBuffer( (char*)bv->GetPointer() );
    // Rub out pixels:
    char *p = (char*)bv->GetPointer();
    switch(pixeltype)
      {
    case gdcm::PixelFormat::UINT8:
      FillRegionWithColor<uint8_t> (p, dims, region, color, pixeltype.GetSamplesPerPixel());
      break;
    case gdcm::PixelFormat::INT8:
      FillRegionWithColor<int8_t>  (p, dims, region, color, pixeltype.GetSamplesPerPixel());
      break;
    case gdcm::PixelFormat::UINT16:
      FillRegionWithColor<uint16_t>(p, dims, region, color, pixeltype.GetSamplesPerPixel());
      break;
    case gdcm::PixelFormat::INT16:
      FillRegionWithColor<int16_t> (p, dims, region, color, pixeltype.GetSamplesPerPixel());
      break;
    default:
      std::cerr << "not implemented" << std::endl;
      return 1;
      }

    pixeldata.SetValue( *bv );
    image.SetDataElement( pixeldata );
    image.SetSpacing( imageori.GetSpacing() );
    image.SetSpacing(2, imageori.GetSpacing()[2] );
    const gdcm::TransferSyntax &ts = imageori.GetTransferSyntax();
    // FIXME: for now we do not know how to recompress the image...
    if( ts.IsExplicit() )
      {
      image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      }
    else 
      {
      assert( ts.IsImplicit() );
      image.SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );
      }
    //imageori.Print( std::cout );
    //image.Print( std::cout );

    // Set our filled image instead:
    writer.SetImage( image );
#if 0
    // <entry group="0028" element="0301" vr="CS" vm="1" name="Burned In Annotation"/>
    gdcm::Attribute<0x0028,0x0301> at;
    at.SetValue( "NO" ); // 'YES'
    ds.Replace( at.GetAsDataElement() );
    // (0008,2111) ST [MedCom Resample v]                      #  18, 1 DerivationDescriptio
    gdcm::Attribute<0x0008,0x2111> at2;
    std::ostringstream os;
    os << "Fill Region [" 
      << region[0] << "," << region[1] << ","
      << region[2] << "," << region[3] << ","
      << region[4] << "," << region[5] << "] with color value=" << std::hex << (int)color;
    at2.SetValue( os.str() );
    ds.Replace( at2.GetAsDataElement() );
#else
#endif
/*
> 1. Replace Value #1 of Image Type by 'DERIVED'

Don't do that ... leave Image Type alone (unless you are changing
the UID ... vide infra). 
*/
#if 0
    // (0008,0008) CS [ORIGINAL\SECONDARY]                     #  18, 2 ImageType
    gdcm::Attribute<0x0008,0x0008> at3;
    static const gdcm::CSComp values[] = {"DERIVED","SECONDARY"}; 
    at3.SetValues( values, 2, true ); // true => copy data !
    if( ds.FindDataElement( at3.GetTag() ) )
      {
      const gdcm::DataElement &de = ds.GetDataElement( at3.GetTag() );
      at3.SetFromDataElement( de );
      // Make sure that value #1 is at least 'DERIVED', so override in all cases:
      at3.SetValue( 0, values[0] );
      }
    ds.Replace( at3.GetAsDataElement() );
#endif
    // Make sure to recompute Planar Configuration:
    ds.Remove( gdcm::Tag(0x0028, 0x0004) );
    }
  //  ds.Remove( gdcm::Tag(0x0,0x0) ); // FIXME

  // Ok so we are about to write a DICOM file, do not forget to stamp it GDCM !
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmimg" );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  return 0;
}

