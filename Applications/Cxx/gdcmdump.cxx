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
#include "gdcmVersion.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"
#include "gdcmPrinter.h"
#include "gdcmDumper.h"
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmCSAHeader.h"

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
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  TPrinter printer;
  printer.SetFile ( reader.GetFile() );
  printer.Print( std::cout );

  return 0;
}

int PrintCSA(const std::string & filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::CSAHeader csa;
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
  std::cout << t1 << std::endl;
  const gdcm::PrivateTag &t2 = csa.GetCSASeriesHeaderInfoTag();

  //if( pde.GetTag().GetElement() != 0xffff /*ds.FindDataElement( t0 )*/ )
    {
    //const gdcm::ByteValue *bv = pde.GetByteValue(); //ds.GetDataElement( t0 ).GetByteValue();
    //if( strncmp( bv->GetPointer(), csaheader, strlen(csaheader) ) ==  0 )
      {
      //gdcm::Tag t3(0x0029,0x1120); ???
      //std::cerr << "Working on: " << filename << std::endl;
	      bool found = false;
      if( ds.FindDataElement( t1 ) )
        {
        csa.Print( ds.GetDataElement( t1 ) );
	found = true;
	//const gdcm::CSAElement &csael = csa.GetCSAElementByName( "Columns" );
	//std::cout << "Looking for Columns:" << std::endl;
	//std::cout << csael << std::endl;
        }
      if( ds.FindDataElement( t2 ) )
        {
        csa.Print( ds.GetDataElement( t2 ) );
	found = true;
        }
      if( !found )
      {
	      std::cout << "no csa tag found" << std::endl;
      }
      if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
        {
        gdcm::Printer p;
        gdcm::File f;
        f.SetDataSet( csa.GetDataSet() );
        p.SetFile( f );
        p.Print( std::cout );
        }
      }
    }

  return 0;
}



void PrintVersion()
{
  std::cout << "gdcmdump: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmdump [OPTION]... [FILE]..." << std::endl;
  std::cout << "by default gdcmdump, only dumps a DICOM file, that is the minimal operations required to\n"
   " display information reader need to see the structure of a DICOM file and some value in its fields" << std::endl;
  std::cout << "Parameter:" << std::endl;
  std::cout << "  -i --input     DICOM filename or directory" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -x --xml-dict  generate the XML dict (only private elements for now)." << std::endl;
  std::cout << "  -r --recursive recursive." << std::endl;
  std::cout << "  -d --dump      dump value (limited use)." << std::endl;
  std::cout << "  -p --print     print value instead of simply dumping (default)." << std::endl;
  std::cout << "  -c --color     print in color." << std::endl;
  std::cout << "  -C --csa       print SIEMENS CSA Header typically (0029,xx10)." << std::endl;
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

  std::string filename;
  int printdict = 0;
  int dump = 0;
  int print = 0;
  int color = 0;
  int printcsa = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  int recursive = 0;
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
        {"xml-dict", 0, &printdict, 1},
        {"recursive", 0, &recursive, 1},
        {"print", 0, &print, 1},
        {"dump", 0, &dump, 1},
        {"color", 0, &color, 1},
        {"csa", 0, &printcsa, 1},
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:xrpdcVWDEhv";
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
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'x':
      //printf ("option d with value '%s'\n", optarg);
      printdict = 1;
      break;

    case 'r':
      recursive = 1;
      break;

    case 'p':
      //printf ("option p with value '%s'\n", optarg);
      print = 1;
      break;

    case 'd':
      dump = 1;
      break;

    case 'c':
      color = 1;
      break;

    case 'C':
      printcsa = 1;
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

  if (optind < argc)
    {
    //printf ("non-option ARGV-elements: %d", optind );
    //while (optind < argc)
    //  {
    //  printf ("%s\n", argv[optind++]);
    //  }
    //printf ("\n");
    // Ok there is only one arg, easy, it's the filename:
    int v = argc - optind;
    if( v == 1 )
      {
      filename = argv[optind];
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
    //std::cerr << "Need input file (-i)\n";
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
   

  // else
  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename, recursive);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      if( printdict )
        {
        res += DoOperation<gdcm::DictPrinter>(*it);
        }
      else if( printcsa )
        {
        res += PrintCSA(*it);
        }
      else if( dump )
        {
        res += DoOperation<gdcm::Dumper>(*it);
        }
      else
        {
        res += DoOperation<gdcm::Printer>(*it);
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
    else if( printcsa )
      {
      res += PrintCSA(filename);
      }
    else if( dump )
      {
      res += DoOperation<gdcm::Dumper>(filename);
      }
    else
      {
      res += DoOperation<gdcm::Printer>(filename);
      }
    // ...
    if ( verbose )
      std::cerr << "Filename: " << filename << std::endl;
    }

  return res;
}

