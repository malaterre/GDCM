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

#include "gdcmReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrinter.h"
#include "gdcmDumper.h"
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

template <typename TPrinter>
int DoOperation(const std::string & filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  try
    {
    if( !reader.Read() )
      {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
      }
    }
  catch( ... )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  TPrinter printer;
  printer.SetFile ( reader.GetFile() );
  printer.Print( std::cout );

  return 0;
}



void PrintVersion()
{
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmdump [OPTION]... [FILE]..." << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -v --verbose   more verbose." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -V --version   print version." << std::endl;
}

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  int printdict = 0;
  int print = 0;
  int verbose = 0;
  int help = 0;
  int version = 0;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
/*
   struct option {
              const char *name;
              int has_arg;
              int *flag;
              int val;
          };
*/
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"dict", 0, &printdict, 1},
        {"print", 0, &print, 1},
        {"verbose", 0, &verbose, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:o:dpvhV";
    c = getopt_long (argc, argv, short_options,
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
    case '-':
        {
        const char *s = long_options[option_index].name;
        //printf ("option %s", s);
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
        //printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      break;

    case 'd':
      //printf ("option d with value '%s'\n", optarg);
      printdict = 1;
      break;

    case 'p':
      //printf ("option p with value '%s'\n", optarg);
      print = 1;
      break;

    case 'v':
      //printf ("option d with value '%s'\n", optarg);
      verbose = 1;
      break;

    case 'V':
      //printf ("option d with value '%s'\n", optarg);
      version = 1;
      break;

    case 'h':
      help = 1;
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

  // check if d or p are passed, only one at a time
  if( print || printdict )
    {
    if ( print && printdict )
      {
      std::cerr << "d or p" << std::endl;
      return 1;
      }
    }
  if( filename.empty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
  // Debug is a little too verbose
  //gdcm::Trace::SetDebug( verbose );
  gdcm::Trace::SetWarning( verbose );
  gdcm::Trace::SetError( verbose );
   

  // else
  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      if( printdict )
        {
        res += DoOperation<gdcm::DictPrinter>(*it);
        }
      else if( print )
        {
        res += DoOperation<gdcm::Printer>(*it);
        }
      else
        {
        assert( print == false && printdict == false );
        res += DoOperation<gdcm::Dumper>(*it);
        }
      if( verbose ) std::cerr << *it << std::endl;
      }
    if( verbose ) std::cerr << "Total: " << filenames.size() << " files were processed" << std::endl;
    }
  else
    {
    assert( gdcm::System::FileExists(filename.c_str()) );
    if( printdict )
      {
      res += DoOperation<gdcm::DictPrinter>(filename);
      }
    else if( print )
      {
      res += DoOperation<gdcm::Printer>(filename);
      }
    else
      {
      res += DoOperation<gdcm::Dumper>(filename);
      }
    // ...
    if ( verbose )
      std::cerr << "Filename: " << filename << std::endl;
    }

  return res;
}

