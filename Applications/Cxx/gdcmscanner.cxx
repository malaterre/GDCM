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
 * a Scanner application
 * Usage:
 *
 * $ gdcmscanner -d /images/ -t 0020,000d -t 0020,000e
 *
 * Options:
 * -d : directory
 * -t : tag (can be specified multiple times)
 * -v : verbose
 * -r : recursive (enter subdir of main directory)
 */

#include "gdcmScanner.h"
#include "gdcmTrace.h"

#include <string>
#include <iostream>
#include <iterator>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>


int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  bool verbose = false;
  bool recursive = false;
  std::string dirname;
  typedef std::vector<gdcm::Tag> VectorTags;
  VectorTags tags;
  gdcm::Tag tag;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"dir", 1, 0, 0},
        {"tag", 1, 0, 0},
        {"recursive", 1, 0, 0},
        {"verbose", 1, 0, 0},
        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "d:t:rv",
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
            }
          printf (" with arg %s", optarg);
          }
        printf ("\n");
        }
      break;

    case 'd':
      printf ("option d with value '%s'\n", optarg);
      dirname = optarg;
      break;

    case 't':
      printf ("option t with value '%s'\n", optarg);
      tag.ReadFromCommaSeparatedString(optarg);
      tags.push_back( tag );
      //std::cerr << optarg << std::endl;
      break;

    case 'r':
      printf ("option r with value '%s'\n", optarg);
      recursive = true;
      break;

    case 'v':
      printf ("option v with value '%s'\n", optarg);
      verbose = true;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      {
      printf ("%s ", argv[optind++]);
      }
    printf ("\n");
    }

  if( dirname.empty() )
    {
    std::cerr << "Need dir (-d)\n";
    return 1;
    }
  if( tags.empty() )
    {
    std::cerr << "Need tags (-t)\n";
    return 1;
    }
  // else
  //std::cout << "Filename: " << filename << std::endl;
  std::cout << "Will parse: " << dirname << std::endl;
  std::cout << "Looking for tags: \n";
  std::copy(tags.begin(), tags.end(), 
    std::ostream_iterator<gdcm::Tag>( std::cout, "\n"));
  //std::cout << std::endl;
  gdcm::Trace::WarningOff();

  gdcm::Directory d;
  unsigned int nfiles = d.Load( dirname.c_str(), recursive );
  if( verbose ) d.Print( std::cout );
  std::cout << "done retrieving file list " << nfiles << " files found." <<  std::endl;

  gdcm::Scanner s;
  for( VectorTags::const_iterator it = tags.begin(); it != tags.end(); ++it)
    {
    s.AddTag( *it );
    }
  bool b = s.Scan( d.GetFilenames() );
  if( !b )
    {
    std::cerr << "Scanner failed" << std::endl;
    return 1;
    }
  if (verbose) s.Print( std::cout );

  return 0;
}

