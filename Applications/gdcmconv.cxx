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
/*
 * HISTORY:
 * In GDCM 1.X the prefered terms was 'ReWrite', however one author of GDCM dislike
 * the term ReWrite since it is associated with the highly associated with the Rewrite
 * notion in software programming where using reinvent the wheel and rewrite from scratch code
 * the term convert was prefered
 *
 * Tools to conv. Goals being to 'purify' a DICOM file.
 * For now it will do the minimum:
 * - If Group Length is present, the length is garantee to be correct
 * - If Element with Group Tag 0x1, 0x3, 0x5 or 0x7 are present they are
 *   simply discarded (not written).
 * - Elements are written in alphabetical order
 * - 32bits VR have the residue bytes sets to 0x0,0x0
 * - Same goes from Item Length end delimitor, sets to 0x0,0x0
 * - All buggy files (wrong length: GE, 13 and Siemens Leonardo) are fixed
 * - All size are even (no odd length from gdcm 1.x)
 *
 * // \todo:
 * // --preamble: clean preamble
 * // --meta: clean meta (meta info version...)
 * // --dicomV3 (use TS unless not supported)
 * // --recompute group-length
 * // --undefined sq
 * // --explicit sq *
 * \todo in a close future:
 * - Set appropriate VR from DICOM dict
 * - Rewrite PMS SQ into DICOM SQ
 * - Rewrite Implicit SQ with defined length as undefined length
 * - PixelData with `overlay` in unused bits should be cleanup
 * - Any broken JPEG file (wrong bits) should be fixed
 * - DicomObject bug should be fixed
 * - Meta and Dataset should have a matching UID (more generally File Meta
 *   should be correct (Explicit!) and consistant with DataSet)
 * - User should be able to specify he wants Group Length (or remove them)
 * - Media SOP should be correct (deduct from something else or set to
 *   SOP Secondary if all else fail).
 * - Padding character should be correct
 *
 * \todo distant future:
 * - Later on, it should run through a Validator
 *   which will make sure all field 1, 1C are present and those only
 * - In a perfect world I should remove private tags and transform them into
 *   public fields.
 * - DA should be correct, PN should be correct (no space!)
 * - Enumerated Value should be correct
 */
#include "gdcmReader.h"
#include "gdcmWriter.h"
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

  std::string filename;
  std::string outfilename;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"group-length", 1, 0, 0}, // valid / create / remove
        {"preamble", 1, 0, 0}, // valid / create / remove
        {"padding", 1, 0, 0}, // valid (\0 -> space) / optimize (at most 1 byte of padding)
        {"vr", 1, 0, 0}, // valid
        {"sop", 1, 0, 0}, // default to SC...
        {"iod", 1, 0, 0}, // valid
        {"pixeldata", 1, 0, 0}, // valid
        {"meta", 1, 0, 0}, // valid / create / remove
        {"dataset", 1, 0, 0}, // valid / create / remove?
        {"sequence", 1, 0, 0}, // defined / undefined 
        {"raw", 1, 0, 0}, // default (implicit VR, LE) / Explicit LE / Explicit BE
        {"jpeg", 1, 0, 0}, // JPEG lossy
        {"jpegll", 1, 0, 0}, // JPEG lossless
        {"jpegls", 1, 0, 0}, // JPEG-LS: lossy / lossless
        {"j2k", 1, 0, 0}, // J2K: lossy / lossless
        {"deflate", 1, 0, 0}, // 1 - 9 / best = 9 / fast = 1
        {"rle", 1, 0, 0}, // lossless !
        {"mpeg2", 1, 0, 0}, // lossless !
        {"jpip", 1, 0, 0}, // ??
        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:",
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
            assert( filename.empty() );
            filename = optarg;
            }
          printf (" with arg %s", optarg);
          }
        printf ("\n");
        }
      break;

    case 'i':
      printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      assert( outfilename.empty() );
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

  if( filename.empty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
  if( outfilename.empty() )
    {
    std::cerr << "Need output file (-o)\n";
    return 1;
    }

  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  return 0;
}

