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
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmDumper.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmOverlay.h"

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

  gdcm::Tag overlay(0x6000,0x0000);
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
  bool finished = false;
  unsigned int numoverlays = 0;
  while( !finished )
    {
    const gdcm::DataElement &de = ds.GetNextDataElement( overlay );
    if( de.GetTag().GetGroup() > 0x60FF ) // last possible curve
      {
      finished = true;
      }
    else
      {
      // Yeah this is an overlay element
      ++numoverlays;
      gdcm::Overlay ov;
      overlay = de.GetTag();
      uint16_t currentoverlay = overlay.GetGroup();
      assert( !(currentoverlay % 2) ); // 0x6001 is not an overlay...
      // Now loop on all element from this current group:
      gdcm::DataElement de2 = de;
      while( de2.GetTag().GetGroup() == currentoverlay )
        {
        ov.Update(de2);
        overlay.SetElement( de2.GetTag().GetElement() + 1 );
        de2 = ds.GetNextDataElement( overlay );
        // Next element:
        //overlay.SetElement( overlay.GetElement() + 1 );
        }
      // If we exit the loop we have pass the current overlay and potentially point to the next one:
      //overlay.SetElement( overlay.GetElement() + 1 );
      ov.Print( std::cout );

      // Let's decode it:
      std::ostringstream unpack;
      ov.Decompress( unpack );
      std::string s = unpack.str();
      size_t l = s.size();
      // The following line will fail with images like XA_GE_JPEG_02_with_Overlays.dcm
      // since the overlays are stored in the unused bit of the PixelData
      if( !ov.IsEmpty() )
        {
        assert( unpack.str().size() == ov.GetRows() * ov.GetColumns() );
        }
      else
        {
        std::cerr << "This image does not contains Overlay in the 0x60xx tags. "
                  << "Instead the overlay is stored in the unused bit of the Pixel Data. "
                  << "This is not supported right now"
                  << std::endl;
        }
      }
    }
  std::cout << "Num of Overlays: " << numoverlays << std::endl;

  return 0;
}



int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  bool printdict = false;
  bool verbose = false;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"dict", 1, 0, 0},
        {"verbose", 1, 0, 0},
        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:dv",
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

    case 'v':
      //printf ("option d with value '%s'\n", optarg);
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

  if( filename.empty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
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
      else
        {
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

