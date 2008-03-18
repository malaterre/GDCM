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

int PrintCSA(const std::string & filename)
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

  gdcm::CSAHeader csa;
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  gdcm::Tag t0(0x0029,0x0010); // LO 
  if( ds.FindDataElement( t0 ) )
    {
    const gdcm::ByteValue *bv = ds.GetDataElement( t0 ).GetByteValue();
    const char csaheader[] = "SIEMENS CSA HEADER";
    if( strncmp( bv->GetPointer(), csaheader, strlen(csaheader) ) ==  0 )
      {
      gdcm::Tag t1(0x0029,0x1010);
      gdcm::Tag t2(0x0029,0x1020);
      //gdcm::Tag t3(0x0029,0x1120); ???
      std::cerr << "Working on: " << filename << std::endl;
      if( ds.FindDataElement( t1 ) )
        {
        csa.Print( ds.GetDataElement( t1 ) );
        }
      if( ds.FindDataElement( t2 ) )
        {
        csa.Print( ds.GetDataElement( t2 ) );
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
  std::cout << "gdcmdump: gdcm " << GDCM_VERSION << " ";
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
  std::cout << "  -x --xml-dict      generate the XML dict (only private elements for now)." << std::endl;
  std::cout << "  -r --recursive recursive." << std::endl;
  std::cout << "  -p --print     print value instead of simply dumping." << std::endl;
  std::cout << "  -v --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -w --warning   print warning info." << std::endl;
  std::cout << "  -d --debug     print debug info." << std::endl;
  std::cout << "  -e --error     print error info." << std::endl;
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
        {"print-csa", 0, &printcsa, 1},
        {"xml-dict", 0, &printdict, 1},
        {"recursive", 0, &recursive, 1},
        {"print", 0, &print, 1},
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:xrpvwdehV";
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

    case 'e':
      error = 1;
      break;

    case 'w':
      warning = 1;
      break;

    case 'd':
      debug = 1;
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
    std::cerr << "Need input file (-i)\n";
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
    else if( printcsa )
      {
      res += PrintCSA(filename);
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

