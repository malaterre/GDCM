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
 * tar is a UNIX program for archiving.
 * Two types of operations are possible: concatenate / extract
 * Thus the name of 'gdcmtar' to concatenate a list of 2D slices into a multi frames
 * and the other way around: extract 2D slices from a multi frames image
 * It also support the fake multi frame image (CSA MOSAIC)
 */

#include "gdcmReader.h"
#include "gdcmVersion.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmSplitMosaicFilter.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

void PrintVersion()
{
  std::cout << "gdcmtar: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmtar [OPTION] [FILE]" << std::endl;
  std::cout << "Concatenate/Extract DICOM files.\n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     DICOM filename" << std::endl;
  std::cout << "  -o --output    DICOM filename" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -M --mosaic     Split SIEMENS Mosaic image into multiple frames." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose    more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning    print warning info." << std::endl;
  std::cout << "  -D --debug      print debug info." << std::endl;
  std::cout << "  -E --error      print error info." << std::endl;
  std::cout << "  -h --help       print help." << std::endl;
  std::cout << "  -v --version    print version." << std::endl;
}


int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  std::string outfilename;
  std::string root;
  int mosaic = 0;

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
        {"mosaic", 0, &mosaic, 1}, // split siemens mosaic into multiple frames

// General options !
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},

        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:M:",
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
          printf (" with arg %s, index = %d", optarg, option_index);
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
      assert( outfilename.empty() );
      outfilename = optarg;
      break;

    case 'M':
      //assert( outfilename.empty() );
      //outfilename = optarg;
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
    //while (optind < argc)
    //  {
    //  printf ("%s ", argv[optind++]);
    //  }
    //printf ("\n");
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

  if( filename.empty() )
    {
    //std::cerr << "Need input file (-i)\n";
    PrintHelp();
    return 1;
    }
  if( outfilename.empty() )
    {
    //std::cerr << "Need output file (-o)\n";
    PrintHelp();
    return 1;
    }
  
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmtar" );

  if( mosaic )
    {
    gdcm::ImageReader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() )
      {
      std::cerr << "could not read: " << filename << std::endl;
      return 1;
      }

    gdcm::SplitMosaicFilter filter;
    filter.SetImage( reader.GetImage() );
    filter.SetFile( reader.GetFile() );
    bool b = filter.Split();
    if( !b )
      {
      std::cerr << "Could not split << " << filename << std::endl;
      return 1;
      }

    gdcm::ImageWriter writer;
    writer.SetFileName( outfilename.c_str() );
    writer.SetFile( filter.GetFile() );
    writer.SetImage( filter.GetImage() );
    if( !writer.Write() )
      {
      std::cerr << "Failed to write: " << outfilename << std::endl;
      return 1;
      }
    
    return 0;
    }


  return 0;
}

