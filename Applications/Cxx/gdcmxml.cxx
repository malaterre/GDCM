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
 * Command line tool to convert a DICOM file into XML format (in Native DICOM format).
   
   Author - Nakull Gupta
 
 
 */

#include "gdcmReader.h"
#include "gdcmVersion.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmCSAHeader.h"
#include "gdcmPDBHeader.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmASN1.h"
#include "gdcmFile.h"

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

void PrintVersion()
{
  std::cout << "gdcmdump: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmxml [OPTION]... FILE..." << std::endl;
  std::cout << "Convert a DICOM file into an XML file \n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     DICOM filename" << std::endl;
  std::cout << "  -o --output    XML filename" << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -B --loadBulkData   loads all bulk data like Pixel Data (by default UUID are written)." << std::endl;
  std::cout << "  -V --verbose        more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning        print warning info." << std::endl;
  std::cout << "  -D --debug          print debug info." << std::endl;
  std::cout << "  -E --error          print error info." << std::endl;
  std::cout << "  -h --help           print help." << std::endl;
  std::cout << "  -v --version        print version." << std::endl;
}

int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string DICOMfile;
  std::string XMLfile;
  int loadBulkData = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  while (1) {
    
    int option_index = 0;

    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"loadBulkData", 0, &loadBulkData, 1},
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:o:BVWDEhv";
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
        
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( DICOMfile.empty() );
            DICOMfile = optarg;
            }
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( DICOMfile.empty() );
      DICOMfile = optarg;
      break;
    
    case 'B':
      loadBulkData = 1;
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
    int v = argc - optind;
    if( v == 2 )
      {
      DICOMfile = argv[optind];
      XMLfile = argv[optind+1];
      }
    else
      {
      PrintHelp();
      return 1;
      }
    }
    
  if( DICOMfile.empty() )
    {
    PrintHelp();
    return 1;
    }

  if( version )
    {    
    PrintVersion();
    return 0;
    }

  if( help )
    {    
    PrintHelp();
    return 0;
    }
    
    
    
    gdcm::Reader reader;
    reader.SetFileName( filename.c_str() );
    bool success = reader.Read();
    if( !success && !ignoreerrors )
    {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
    }

    const File *F;    
    F = &reader.GetFile();
    const DataSet &ds = F->GetDataSet();

    if( XMLfile.empty() )
    {
    ds.WriteXML(std::out);
    }
    else
    {
    std::filebuf fb;
    fb.open (XMLfile,std::ios::out);
    std::ostream os(&fb);
    ds.WriteXML(os);
    }
    

}  
