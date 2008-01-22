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
 */
#include "gdcmFilename.h"
#include "gdcmReader.h"
#include "gdcmImageWriter.h"
#include "gdcmImageReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  gdcm::Filename filename;
  gdcm::Filename outfilename;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        // provide convert-like command line args:
        {"depth", 1, 0, 0},
        {"size", 1, 0, 0},
        {0, 0, 0, 0}
    };

    // i -> input file
    // I -> input directory
    // o -> output file
    // O -> output directory
    c = getopt_long (argc, argv, "i:o:I:O:d:s:",
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
      printf ("option d with value '%s'\n", optarg);
      outfilename = optarg;
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

  gdcm::ImageWriter writer;
  writer.SetFileName( outfilename );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  return 0;
}

