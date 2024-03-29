/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
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
 * -p : print
 * -r : recursive (enter subdir of main directory)
 *
 * TODO:
 * --bench...
 */

#include "gdcmScanner2.h"
#include "gdcmStrictScanner2.h"
#include "gdcmTrace.h"
#include "gdcmVersion.h"
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"

#include <string>
#include <iostream>
#include <iterator>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

static void PrintVersion()
{
  std::cout << "gdcmscanner: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

static void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmscanner [OPTION] -d directory -t tag(s)" << std::endl;
  std::cout << "Scan a directory containing DICOM files.\n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -d --dir                  DICOM directory" << std::endl;
  std::cout << "  -t --tag %d,%d            DICOM tag(s) to look for" << std::endl;
  std::cout << "  -k --keyword %s           DICOM keyword(s) to look for" << std::endl;
  std::cout << "  -P --private-tag %d,%d,%s DICOM private tag(s) to look for" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -p --print      Print output." << std::endl;
  std::cout << "  -r --recursive  Recursively descend directory." << std::endl;
  std::cout << "     --strict     Use strict parser (faster but less tolerant with bogus DICOM files)." << std::endl;
  std::cout << "     --table      Use Table output." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose    more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning    print warning info." << std::endl;
  std::cout << "  -D --debug      print debug info." << std::endl;
  std::cout << "  -E --error      print error info." << std::endl;
  std::cout << "  -h --help       print help." << std::endl;
  std::cout << "  -v --version    print version." << std::endl;
}

typedef std::vector<gdcm::Tag> VectorTags;
typedef std::vector<gdcm::PrivateTag> VectorPrivateTags;
template < typename TScanner >
static int DoIt(
  gdcm::Directory const & d,
  bool const & print , int table,
    VectorTags const & tags,
  VectorPrivateTags const & privatetags, bool header)
{
  gdcm::SmartPointer<TScanner> ps = new TScanner;
  TScanner &s = *ps;
  //gdcm::SimpleSubjectWatcher watcher(ps, "Scanner");
  for( VectorTags::const_iterator it = tags.begin(); it != tags.end(); ++it)
    {
    if(!s.AddPublicTag( *it ))
      {
      std::cerr << "Failure to add public tag: " << *it << std::endl;
      return 1;
      }
    }
  for( VectorPrivateTags::const_iterator it = privatetags.begin(); it != privatetags.end(); ++it)
    {
    if(!s.AddPrivateTag( *it ))
      {
      std::cerr << "Failure to add private tag: " << *it << std::endl;
      return 1;
      }
    }
  bool b = s.Scan( d.GetFilenames() );
  if( !b )
    {
    std::cerr << "Scanner failed" << std::endl;
    return 1;
    }
  if (print)
    {
    if(table)
      s.PrintTable( std::cout, header );
    else
      s.Print( std::cout );
    }

  return 0;
}


int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  bool print = false;
  bool recursive = false;
  std::string dirname;
  VectorTags tags;
  VectorPrivateTags privatetags;
  gdcm::Tag tag;
  gdcm::PrivateTag privatetag;
  static const gdcm::Global &g = gdcm::Global::GetInstance();
  static const gdcm::Dicts &dicts = g.GetDicts();
  static const gdcm::Dict &pubdict = dicts.GetPublicDict();

  int strict = 0;
  int table = 0;
  int header = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;

  while (true) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"dir", required_argument, nullptr, 'd'},
        {"tag", required_argument, nullptr, 't'},
        {"recursive", no_argument, nullptr, 'r'},
        {"print", no_argument, nullptr, 'p'},
        {"private-tag", required_argument, nullptr, 'P'},
        {"keyword", required_argument, nullptr, 'k'},
        {"strict", no_argument, &strict, 1},
        {"table", no_argument, &table, 1},
        {"header", no_argument, &header, 1},

// General options !
        {"verbose", no_argument, nullptr, 'V'},
        {"warning", no_argument, nullptr, 'W'},
        {"debug", no_argument, nullptr, 'D'},
        {"error", no_argument, nullptr, 'E'},
        {"help", no_argument, nullptr, 'H'},
        {"version", no_argument, nullptr, 'v'},

        {nullptr, 0, nullptr, 0}
    };

    c = getopt_long (argc, argv, "d:t:rpP:k:VWDEhv",
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
      if (optarg)
        {
        const char *s = long_options[option_index].name; (void)s;
        assert(0);
        }
      break;

    case 'd':
      dirname = optarg;
      break;

    case 't':
      tag.ReadFromCommaSeparatedString(optarg);
      tags.push_back( tag );
      //std::cerr << optarg << std::endl;
      break;

    case 'k':
      {
      const char * keyword = optarg;
      /*const gdcm::DictEntry &dictentry =*/ pubdict.GetDictEntryByKeyword(keyword, tag);
      if( tag != gdcm::Tag(0xffff,0xffff) )
        tags.push_back( tag );
      else
        {
        std::cerr << "Invalid keyword: " << keyword << std::endl;
        return 1;
        }
      }
      break;

    case 'P':
      privatetag.ReadFromCommaSeparatedString(optarg);
      privatetags.push_back( privatetag );
      //std::cerr << optarg << std::endl;
      break;

    case 'r':
      recursive = true;
      break;

    case 'p':
      print = true;
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

  if( dirname.empty() )
    {
    //std::cerr << "Need dir (-d)\n";
    PrintHelp();
    return 1;
    }
  if( tags.empty() && privatetags.empty() )
    {
    //std::cerr << "Need tags (-t)\n";
    PrintHelp();
    return 1;
    }
  // Debug is a little too verbose
  gdcm::Trace::SetDebug( (debug  > 0 ? true : false));
  gdcm::Trace::SetWarning(  (warning  > 0 ? true : false));
  gdcm::Trace::SetError(  (error  > 0 ? true : false));
  // when verbose is true, make sure warning+error are turned on:
  if( verbose )
    {
    gdcm::Trace::SetWarning( (verbose  > 0 ? true : false) );
    gdcm::Trace::SetError( (verbose  > 0 ? true : false) );
    }

  if( verbose )
    {
    std::cout << "Will parse: " << dirname << std::endl;
    std::cout << "Looking for tags: \n";
    std::copy(tags.begin(), tags.end(),
      std::ostream_iterator<gdcm::Tag>( std::cout, "\n"));
    std::copy(privatetags.begin(), privatetags.end(),
      std::ostream_iterator<gdcm::PrivateTag>( std::cout, "\n"));
    //std::cout << std::endl;
    }

  gdcm::Directory d;
  unsigned int nfiles = d.Load( dirname, recursive );
  if( !nfiles )
    {
    std::cerr << "No files found in: " << dirname << std::endl;
    return 1;
    }
  if( verbose ) d.Print( std::cout );
  if( !table )
    std::cout << "done retrieving file list " << nfiles << " files found." <<  std::endl;

  if( strict )
    return DoIt<gdcm::StrictScanner2>(d,print,table,tags,privatetags,header>0);
  return DoIt<gdcm::Scanner2>(d,print,table,tags,privatetags,header > 0);
}
