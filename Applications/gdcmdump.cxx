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

#include "gdcmReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrinter.h"
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmDumper.h"

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
  bool printdict = false;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"dict", 1, 0, 0},
        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:d:",
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
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      break;

    case 'd':
      //printf ("option d with value '%s'\n", optarg);
      printdict = true;
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

  if( filename.empty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
  // else
  std::cerr << "Filename: " << filename << std::endl;
//  for(int i=0; i <100; i++)
//{
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
//}

#if 0
  gdcm::Validate vali;
  vali.SetFile( reader.GetFile() );
  //vali.Validation();

  gdcm::Printer *p = 0;
  gdcm::Printer     printer;
  //std::cerr << "PRINTDICT:" << printdict << std::endl;
  if( printdict )
  {
	  //	  FIXME: need virtual mechanism
//	  p = &dictprinter;
  gdcm::DictPrinter dictprinter;
  dictprinter.SetFile ( reader.GetFile() );
  dictprinter.Print( std::cout );
  return 0;
  }
  else
  {
	  p = &printer;
  }
  // TODO:

  p->SetFile( reader.GetFile() );
  //p->SetFile( vali.GetValidatedFile() );
  //const gdcm::FileMetaInformation &h = reader.GetHeader();
  ////std::cout << h << std::endl;
  //if(!h.IsEmpty())
  //{
  ////printer.SetDataSet( h );
  ////printer.Print( std::cout );
  //}

 //const gdcm::DataSet &ds = reader.GetDataSet();
  ////std::cout << ds << std::endl;
  //printer.SetDataSet( reader.GetDataSet() );
  p->Print( std::cout );
  //std::cout << reader.GetFile() << std::endl;

//  std::ofstream of;
//  of.open( "/tmp/valii.dcm", std::ios::out | std::ios::binary );
//  const char line[] = "coucou mathieu";
//  //of.write( line, strlen(line) );
//  of << line;
//  of.close();
  gdcm::Writer writer;
  writer.SetFileName( "vali2.dcm" );
  writer.SetFile( reader.GetFile() );
  //writer.SetFile( vali.GetValidatedFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: "  << std::endl;
    return 1;
    }
#endif

  if( printdict )
    {
    gdcm::DictPrinter dictprinter;
    dictprinter.SetFile ( reader.GetFile() );
    dictprinter.Print( std::cout );
    }
  else
    {
    gdcm::Dumper dumper;
    dumper.SetFile( reader.GetFile() );
    dumper.Print( std::cout );
    }


  return 0;
}

