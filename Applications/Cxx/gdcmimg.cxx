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
 *   DICOM jpgl <->  jpgl
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
#include "gdcmReader.h"
#include "gdcmImageWriter.h"
#include "gdcmImageReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

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
        {0, 0, 0, 0}
    };

    // i -> input file
    // I -> input directory
    // o -> output file
    // O -> output directory
    c = getopt_long (argc, argv, "i:o:I:O:d:s:R:F:",
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
      outfilename = optarg;
      break;

    case 's': // size
      printf ("option s with value '%s'\n", optarg);
      outfilename = optarg;
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

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  // For now only support one input / one output
  if (optind < argc)
    {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      {
      printf ("%s ", argv[optind++]);
      }
    printf ("\n");
    return 1;
    }

  if( filename.IsEmpty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
  if( outfilename.IsEmpty() )
    {
    std::cerr << "Need output file (-o)\n";
    return 1;
    }

  const char *inputextension = filename.GetExtension();
  const char *outputextension = outfilename.GetExtension();

  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  const gdcm::Image &imageori = reader.GetImage();
  const gdcm::File &file = reader.GetFile();
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

