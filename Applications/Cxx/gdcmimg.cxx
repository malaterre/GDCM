/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
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
#include "gdcmMediaStorage.h"
#include "gdcmSmartPointer.h"
#include "gdcmUIDGenerator.h"
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
#include "gdcmJPEGLSCodec.h"
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
  std::cout << "     --endian %s       Endianess (LSB/MSB)." << std::endl;
  std::cout << "  -d --depth %d        Depth (8/16/32)." << std::endl;
  std::cout << "     --sign %s         Pixel sign (0/1)." << std::endl;
  std::cout << "  -s --size %d,%d      Size." << std::endl;
  std::cout << "  -R --region %d,%d    Region." << std::endl;
  std::cout << "  -F --fill %d         Fill with pixel value specified." << std::endl;
  std::cout << "  -C --sop-class-uid   SOP Class UID (name or value)." << std::endl;
  std::cout << "  -T --study-uid       Study UID." << std::endl;
  std::cout << "  -S --series-uid      Series UID." << std::endl;
  std::cout << "     --root-uid        Root UID." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
  std::cout << "Env var:" << std::endl;
  std::cout << "  GDCM_ROOT_UID Root UID" << std::endl;
/* 
 * Default behavior for root UID is:
 * By default the GDCM one is used
 * If GDCM_ROOT_UID is set, then use this one instead
 * If --root-uid is explicitly set on the command line, it will override any other defined behavior
 */
}

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string root;
  int rootuid = 0;
  gdcm::Filename filename;
  gdcm::Filename outfilename;
  unsigned int region[6] = {}; // Rows & Columns are VR=US anyway...
  unsigned int color = 0;
  bool b;
  int bregion = 0;
  int fill = 0;
  int sign = 0;
  int studyuid = 0;
  int seriesuid = 0;
  unsigned int size[2] = {};
  int depth = 0;
  int endian = 0;
  int bpp = 0;
  int pixelsign = 0;
  std::string sopclass;
  std::string lsb_msb;
  int sopclassuid = 0;

  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;

  gdcm::UIDGenerator uid;
  std::string series_uid = uid.Generate();
  std::string study_uid = uid.Generate();
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        // provide convert-like command line args:
        {"depth", 1, &depth, 1},
        {"size", 1, 0, 0},
        {"region", 1, &bregion, 1},
        {"fill", 1, &fill, 1},
        {"study-uid", 1, &studyuid, 1},
        {"series-uid", 1, &seriesuid, 1},
        {"root-uid", 1, &rootuid, 1}, // specific Root (not GDCM)
        {"sop-class-uid", 1, &sopclassuid, 1}, // specific SOP Class UID
        {"endian", 1, &endian, 1}, // 
        {"sign", 1, &sign, 1}, // 

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
    c = getopt_long (argc, argv, "i:o:I:O:d:s:R:C:F:VWDEhv",
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
        //printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.IsEmpty() );
            filename = optarg;
            }
          else if( option_index == 2 ) /* depth */
            {
            assert( strcmp(s, "depth") == 0 );
            bpp = atoi(optarg);
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
          else if( option_index == 6 ) /* study-uid */
            {
            assert( strcmp(s, "study-uid") == 0 );
            study_uid = optarg;
            }
          else if( option_index == 7 ) /* series-uid */
            {
            assert( strcmp(s, "series-uid") == 0 );
            series_uid = optarg;
            }
          else if( option_index == 8 ) /* root-uid */
            {
            assert( strcmp(s, "root-uid") == 0 );
            root = optarg;
            }
          else if( option_index == 9 ) /* sop-class-uid */
            {
            assert( strcmp(s, "sop-class-uid") == 0 );
            sopclass = optarg;
            }
          else if( option_index == 10 ) /* endian */
            {
            assert( strcmp(s, "endian") == 0 );
            lsb_msb = optarg;
            }
          else if( option_index == 11 ) /* sign */
            {
            assert( strcmp(s, "sign") == 0 );
            pixelsign = atoi(optarg);
            }
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.IsEmpty() );
      filename = optarg;
      break;

    case 'o':
      //printf ("option o with value '%s'\n", optarg);
      assert( outfilename.IsEmpty() );
      outfilename = optarg;
      break;

    case 'd': // depth
      bpp = atoi(optarg);
      depth = 1;
      break;

    case 's': // size
      readsize(optarg, size);
      break;

    case 'C':
      sopclassuid = 1;
      sopclass = optarg;
      break;

    case 'R': // region
      //outfilename = optarg;
      readgeometry(optarg, region);
      break;

    case 'F': // fill
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
    //printf ("non-option ARGV-elements: ");
    std::vector<std::string> files;
    while (optind < argc)
      {
      //printf ("%s\n", argv[optind++]);
      files.push_back( argv[optind++] );
      }
    //printf ("\n");
    if( files.size() == 2 
      && filename.IsEmpty()
      && outfilename.IsEmpty() 
    )
      {
      filename = files[0].c_str();
      outfilename = files[1].c_str();
      }
    else
      {
      PrintHelp();
      return 1;
      }
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

  if( !gdcm::UIDGenerator::IsValid( study_uid.c_str() ) )
    {
    std::cerr << "Invalid UID for Study UID: " << study_uid << std::endl;
    return 1;
    }

  if( !gdcm::UIDGenerator::IsValid( series_uid.c_str() ) )
    {
    std::cerr << "Invalid UID for Series UID: " << series_uid << std::endl;
    return 1;
    }

  // Ok so we are about to write a DICOM file, do not forget to stamp it GDCM !
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmimg" );
  if( !rootuid )
    {
    // only read the env var is no explicit cmd line option
    // maybe there is an env var defined... let's check
    const char *rootuid_env = getenv("GDCM_ROOT_UID");
    if( rootuid_env )
      {
      rootuid = 1;
      root = rootuid_env;
      }
    }
  if( rootuid )
    {
    if( !gdcm::UIDGenerator::IsValid( root.c_str() ) )
      {
      std::cerr << "specified Root UID is not valid: " << root << std::endl;
      return 1;
      }
    gdcm::UIDGenerator::SetRoot( root.c_str() );
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

  if( depth )
    {
    if( bpp != 8 && bpp != 16 && bpp != 32 ) return 1;
    }
  if( sign )
    {
    if( pixelsign != 0 && pixelsign != 1 ) return 1;
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
      gdcm::PixelFormat pf = gdcm::PixelFormat::UINT8; // default
      if( depth )
        {
        switch(bpp)
          {
        case 8:
          pf = gdcm::PixelFormat::UINT8;
          break;
        case 16:
          pf = gdcm::PixelFormat::UINT16;
          break;
        case 32:
          pf = gdcm::PixelFormat::UINT32;
          break;
        default:
          std::cerr << "Invalid depth: << " << bpp << std::endl;
          return 1;
          }
        }
      if( sign )
        {
        pf.SetPixelRepresentation( pixelsign );
        }
      image.SetPixelFormat( pf );
      gdcm::PhotometricInterpretation pi = gdcm::PhotometricInterpretation::MONOCHROME2;
      image.SetPhotometricInterpretation( pi );
      image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      if( endian )
        {
        if( lsb_msb == "LSB" || lsb_msb == "MSB" )
          {
          if( lsb_msb == "MSB" )
            {
            image.SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRBigEndianPrivateGE );
            }
          }
        else
          {
          std::cerr << "Unrecognized endian: " << lsb_msb << std::endl;
          return 1;
          }
        }

      gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
      pixeldata.SetByteValue( buf, len );
      image.SetDataElement( pixeldata );

      writer.SetFileName( outfilename );
      gdcm::DataSet &ds = writer.GetFile().GetDataSet();

        {
        gdcm::DataElement de( gdcm::Tag(0x0020,0x000d) ); // Study
        de.SetByteValue( study_uid.c_str(), study_uid.size() );
        de.SetVR( gdcm::Attribute<0x0020, 0x000d>::GetVR() );
        ds.Insert( de );
        }

        {
        gdcm::DataElement de( gdcm::Tag(0x0020,0x000e) ); // Series
        de.SetByteValue( series_uid.c_str(), series_uid.size() );
        de.SetVR( gdcm::Attribute<0x0020, 0x000e>::GetVR() );
        ds.Insert( de );
        }

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

    if(  gdcm::System::StrCaseCmp(inputextension,".jls") == 0 )
      {
      gdcm::JPEGLSCodec jpeg;

      std::ifstream is(filename);
      gdcm::PixelFormat pf ( gdcm::PixelFormat::UINT8 ); // usual guess...
      jpeg.SetPixelFormat( pf );
      gdcm::TransferSyntax ts;
      bool b = jpeg.GetHeaderInfo( is, ts );
      if( !b )
        {
        std::cerr << "Error: could not parse JPEG-LS header" << std::endl;
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
        std::cerr << "Error: could not parse J2K header" << std::endl;
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

      if( sopclassuid )
        {
        gdcm::DataSet &ds = writer.GetFile().GetDataSet();
        // Is it by value or by name ?
        gdcm::MediaStorage ms = gdcm::MediaStorage::MS_END;
        if( gdcm::UIDGenerator::IsValid( sopclass.c_str() ) )
          {
          ms = gdcm::MediaStorage::GetMSType( sopclass.c_str() );
          }
        else
          {
          std::cerr << "not implemented" << std::endl;
          }
        if( !gdcm::MediaStorage::IsImage(ms) )
          {
          std::cerr << "invalid media storage (no pixel data): " << sopclass << std::endl;
          return 1;
          }

        const char* msstr = gdcm::MediaStorage::GetMSString(ms);
        if( !msstr )
          {
          std::cerr << "problem with media storage: " << sopclass << std::endl;
          return 1;
          }
        gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016 ) );
        de.SetByteValue( msstr, strlen(msstr) );
        de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
        ds.Insert( de );
        }

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

      if( sopclassuid )
        {
        gdcm::DataSet &ds = writer.GetFile().GetDataSet();
        // Is it by value or by name ?
        gdcm::MediaStorage ms = gdcm::MediaStorage::MS_END;
        if( gdcm::UIDGenerator::IsValid( sopclass.c_str() ) )
          {
          ms = gdcm::MediaStorage::GetMSType( sopclass.c_str() );
          }
        else
          {
          std::cerr << "not implemented" << std::endl;
          }
        if( !gdcm::MediaStorage::IsImage(ms) )
          {
          std::cerr << "invalid media storage (no pixel data): " << sopclass << std::endl;
          return 1;
          }

        const char* msstr = gdcm::MediaStorage::GetMSString(ms);
        if( !msstr )
          {
          std::cerr << "problem with media storage: " << sopclass << std::endl;
          return 1;
          }
        gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016 ) );
        de.SetByteValue( msstr, strlen(msstr) );
        de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
        ds.Insert( de );
        }


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
      pnm.SetPhotometricInterpretation( imageori.GetPhotometricInterpretation() );
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
    gdcm::SmartPointer<gdcm::Image> image = new gdcm::Image;
    image->SetNumberOfDimensions( 2 ); // good default
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
    image->SetDimension(0, dims[0] );
    image->SetDimension(1, dims[1] );
    if( imageori.GetNumberOfDimensions() == 3 )
      {
      image->SetNumberOfDimensions( 3 );
      image->SetDimension(2, dims[2] );
      }
    image->SetPhotometricInterpretation( imageori.GetPhotometricInterpretation() );
    image->SetPixelFormat( imageori.GetPixelFormat() );
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
    image->SetDataElement( pixeldata );
    image->SetSpacing( imageori.GetSpacing() );
    image->SetSpacing(2, imageori.GetSpacing()[2] );
    const gdcm::TransferSyntax &ts = imageori.GetTransferSyntax();
    // FIXME: for now we do not know how to recompress the image...
    if( ts.IsExplicit() )
      {
      image->SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      }
    else 
      {
      assert( ts.IsImplicit() );
      image->SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );
      }
    //imageori.Print( std::cout );
    //image.Print( std::cout );

    // Set our filled image instead:
    writer.SetImage( *image );
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

  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  return 0;
}

